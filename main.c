#include <stdio.h>
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

void rotate_piece(uint8_t * piece){
    int tmp[5] = {0, 0, 0, 0, 0};
    int j, i;

    for (j = 0; j < 5; j++)
        for (i = 0; i < 5; i++) {
            tmp[j] |= (!!(piece[i] & _BV(j)) << (4-i));
        }
}

void symmetrize_piece(uint8_t * piece) {
    int tmp, i;
    for (i = 0; i < 5; i++) {
        tmp = (piece[i] & S4) >> 4;
        tmp |= (piece[i] & S3) >> 2;
        tmp |= (piece[i] & S2);
        tmp |= (piece[i] & S1) << 2;
        tmp |= (piece[i] & S0) << 4;
        piece[i] = tmp;
    }
}

int next(uint8_t * table, int pos, uint8_t * rot) {
    int x, y;
    if (pos == 12) { // FOUND A SOLUTION !!!!
        printf("Found a solution!!!!!\n");

        return 0;
    } else {
        for (x = 0; x < 8; x++)
            for (y = 0; y < 8; y++) {
                // Now insert the pos-th piece in the grid
                // but first make shure there is enough vertical space
                

                if (pos == 0) { // Cross, no simmetry!

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
