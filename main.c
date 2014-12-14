#include <stdio.h> // for printf
#include <string.h> // for memcpy
#include <stdint.h> // for uint8_t

#define _BV(x) (1 << (x))
#define S0 1
#define S1 2
#define S2 4
#define S3 8
#define S4 16

/*
    piece id 0; X piece
        +---+
        |   |
    +---+   +---+
    |           |
    +---+   +---+
        |   |
        +---+

    piece id: 1; I piece
    +-------------------+
    |                   |
    +-------------------+

    piece id 2; Z piece
    +-------+
    |       |
    +---+   |
        |   |
        |   +---+
        |       |
        +-------+

    piece id: 3; T piece
    +-----------+
    |           |
    +---+   +---+
        |   |
        |   |
        |   |
        +---+

    piece id: ; F piece
        +-------+
        |       |
    +---+   +---+
    |       |
    +---+   |
        |   |
        +---+

    piece id 2; L piece
*/

// Piece table

const uint8_t piece_table[12][5] = { { 0*S4 | 0*S3 | 0*S2 | 0*S1 | 0*S0,
                                       0*S4 | 0*S3 | 1*S2 | 0*S1 | 0*S0,
                                       0*S4 | 1*S3 | 1*S2 | 1*S1 | 0*S0,
                                       0*S4 | 0*S3 | 1*S2 | 0*S1 | 0*S0,
                                       0*S4 | 0*S3 | 0*S2 | 0*S1 | 0*S0, },

                                     { 0*S4 | 0*S3 | 0*S2 | 0*S1 | 0*S0,
                                       0*S4 | 0*S3 | 0*S2 | 0*S1 | 0*S0,
                                       1*S4 | 1*S3 | 1*S2 | 1*S1 | 1*S0,
                                       0*S4 | 0*S3 | 0*S2 | 0*S1 | 0*S0,
                                       0*S4 | 0*S3 | 0*S2 | 0*S1 | 0*S0, },

                                     { 0*S4 | 0*S3 | 0*S2 | 0*S1 | 0*S0,
                                       0*S4 | 1*S3 | 1*S2 | 0*S1 | 0*S0,
                                       0*S4 | 0*S3 | 1*S2 | 0*S1 | 0*S0,
                                       0*S4 | 0*S3 | 1*S2 | 1*S1 | 0*S0,
                                       0*S4 | 0*S3 | 0*S2 | 0*S1 | 0*S0, },

                                    { 0*S4 | 0*S3 | 0*S2 | 0*S1 | 0*S0,
                                      0*S4 | 1*S3 | 1*S2 | 1*S1 | 0*S0,
                                      0*S4 | 0*S3 | 1*S2 | 0*S1 | 0*S0,
                                      0*S4 | 0*S3 | 1*S2 | 0*S1 | 0*S0,
                                      0*S4 | 0*S3 | 0*S2 | 0*S1 | 0*S0, },

                                    };
// Each piece in the table has the center piece at 1, this way the software maake shure
// to insert at least one little square in the grid

void rotate_piece(const uint8_t * piece, uint8_t *dest){
    int tmp;
    int j, i;

    for (j = 0; j < 5; j++) {
        tmp = 0;
        for (i = 0; i < 5; i++) {
            tmp |= (!!(piece[i] & _BV(j)) << (4-i));
        }
        dest[j] = tmp;
    }
}

void symmetrize_piece(const uint8_t * piece, uint8_t *dest) {
    int tmp, i;
    for (i = 0; i < 5; i++) {
        tmp = (piece[i] & S4) >> 4;
        tmp |= (piece[i] & S3) >> 2;
        tmp |= (piece[i] & S2);
        tmp |= (piece[i] & S1) << 2;
        tmp |= (piece[i] & S0) << 4;
        dest[i] = tmp;
    }
}

int enough_space(int x, int y, uint8_t *piece) {
    // check if there is enough vertical space
    if (piece[1] && y < 1)
        return 0;
    if (piece[0] && y < 2)
        return 0; // there is something in the first line, but not enough space
    if (piece[4] && y > 5)
        return 0;
    if (piece[3] && y > 6)
        return 0;

    // checks for horiziontal space
    if (x < 2) // There must be nothing in the left bits
        if ((piece[0] & S4) | (piece[1] & S4) | (piece[2] & S4) | (piece[3] & S4) | (piece[4] & S4))
            return 0;
    if (x < 1)
        if ((piece[0] & S3) | (piece[1] & S3) | (piece[2] & S3) | (piece[3] & S3) | (piece[4] & S3))
            return 0;
    if (x > 5) // there must be nothing in the right bits
        if ((piece[0] & S0) | (piece[1] & S0) | (piece[2] & S0) | (piece[3] & S0) | (piece[4] & S0))
            return 0;
    if (x > 6)
        if ((piece[0] & S1) | (piece[1] & S1) | (piece[2] & S1) | (piece[3] & S1) | (piece[4] & S1))
            return 0;

    return 1;
}

int next(uint8_t * table, int pos, uint8_t * rot) {
    int x, y, i, j;
    uint8_t tpos[5]; // temporany pentamino, rotated
    if (pos == 12) { // FOUND A SOLUTION !!!!
        printf("Found a solution!!!!!\n");
        // Print the solution
        return 0;
    } else {
        for (x = 0; x < 8; x++)
            for (y = 0; y < 8; y++) {
            memcpy(tpos, piece_table[pos], 5*sizeof*tpos); // copies the data in a temporany mem space
                if (pos == 0) { // Cross, does not have to compute rotations and symmetries
                    // Now insert the pos-th piece in the grid
                    // but first make shure there is enough vertical space
                    if (!enoug_space(x, y, tpos))
                        continue; // skip if there is not enough space
                    if (tpos[2] & table[x])
                }
            }
        return 0;
    }
}

int main(int argc, char * argv[]) {
    uint8_t tab[8];
    uint8_t rot[12]; // there are 12 pieces
    int x;

    for (x = 0; x < 8; x++)
        tab[x] = 0; // initialize table

    next(tab, 0, rot);

    return 0;
}
