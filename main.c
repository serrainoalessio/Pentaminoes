#include <stdio.h>
#include <stdint.h> // for uint8_t

#define S0 0x01
#define S1 0x02
#define S2 0x04
#define S3 0x08
#define S4 0x10

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
                                       0*S4 | 0*S) | 0*S2 | 0*S1 | 0*S0, },

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

void rotate_piece(uint8_t * piece){
    int tmp[5] = {0, 0, 0, 0, 0};

    int j, i;

    for (j = 0; j < 5; j++)
        for (i = 0; i < 5; i++) {
            tmp[j] |= (!!(piece[i] & _BV(i)) << (4-i));
        }

    tmp[0] |= (!!(piece[0] & S0) << 4);
    tmp[0] |= (!!(piece[1] & S0) << 3);
    tmp[0] |= (!!(piece[2] & S0) << 2);
    tmp[0] |= (!!(piece[3] & S0) << 1);
    tmp[0] |= (!!(piece[4] & S0) << 0);

    tmp[1] |= (!!(piece[0] & S1) << 4);
    tmp[1] |= (!!(piece[1] & S1) << 3);
    tmp[1] |= (!!(piece[2] & S1) << 2);

}

void symmetrize_piece(uint8_t * piece) {
    int tmp, i
    for (i = 0; i < 5; i++) {
        tmp = (piece[i] & S4) >> 4;
        tmp |= (piece[i] & S3) >> 2;
        tmp |= (piece[i] & S2);
        tmp |= (piece[i] & S1) << 2;
        tmp |= (piece[i] & S0) << 4;
        piece[i] = tmp;
    }
}

int next(uint8_t table, int pos, uint8_t * rot) {
    int x, y;
    if (pos == 12) { // FOUND A SOLUTION !!!!
        printf("Found a solution!!!!!\n");

        return 0;
    } else {
        for (x = 0; x < 8; x++)
            for (y = 0; y < 8; y++) {
                rot[pos] = 0; // rotation = 0;
                // now make shuere in the teble there is enough space for piece

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
