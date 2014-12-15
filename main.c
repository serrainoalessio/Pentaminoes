#include <stdio.h> // for printf
#include <string.h> // for memcpy
#include <stdint.h> // for uint8_t

#define _BV(x) (1 << (x))
#define S0 1
#define S1 2
#define S2 4
#define S3 8
#define S4 16

// Graphical rendering
#define COLOR_RESET  "\033[39;49m"
#define COLOR_1      "\033[48;5;154m"
#define COLOR_2      "\033[48;5;220m"
#define COLOR_3      "\033[48;5;028m"
#define COLOR_4      "\033[48;5;020m"
#define COLOR_5      "\033[48;5;124m"
#define COLOR_6      "\033[48;5;208m"
#define COLOR_7      "\033[48;5;054m"
#define COLOR_8      "\033[48;5;198m"
#define COLOR_9      "\033[48;5;136m"
#define COLOR_10     "\033[48;5;069m"
#define COLOR_11     "\033[48;5;052m"
#define COLOR_12     "\033[48;5;123m"
#define COLOR_13     "\033[48;5;232m"
#define COLOR_14     "\033[48;5;232m"

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

const char * piecename[] = {"X", "I", "Z", "T", "U", "V", "W", "F", "N", "L", "P", "Y"};
// Piece table
const uint8_t piece_table[12][5] = {  // X piece   0
                                      { 0*S4 | 0*S3 | 0*S2 | 0*S1 | 0*S0,
                                        0*S4 | 0*S3 | 1*S2 | 0*S1 | 0*S0,
                                        0*S4 | 1*S3 | 1*S2 | 1*S1 | 0*S0,
                                        0*S4 | 0*S3 | 1*S2 | 0*S1 | 0*S0,
                                        0*S4 | 0*S3 | 0*S2 | 0*S1 | 0*S0, },
                                      // I piece   1
                                      { 0*S4 | 0*S3 | 0*S2 | 0*S1 | 0*S0,
                                        0*S4 | 0*S3 | 0*S2 | 0*S1 | 0*S0,
                                        1*S4 | 1*S3 | 1*S2 | 1*S1 | 1*S0,
                                        0*S4 | 0*S3 | 0*S2 | 0*S1 | 0*S0,
                                        0*S4 | 0*S3 | 0*S2 | 0*S1 | 0*S0, },
                                      // Z piece   2
                                      { 0*S4 | 0*S3 | 0*S2 | 0*S1 | 0*S0,
                                        0*S4 | 1*S3 | 1*S2 | 0*S1 | 0*S0,
                                        0*S4 | 0*S3 | 1*S2 | 0*S1 | 0*S0,
                                        0*S4 | 0*S3 | 1*S2 | 1*S1 | 0*S0,
                                        0*S4 | 0*S3 | 0*S2 | 0*S1 | 0*S0, },
                                      // T piece   3
                                      { 0*S4 | 0*S3 | 0*S2 | 0*S1 | 0*S0,
                                        0*S4 | 1*S3 | 1*S2 | 1*S1 | 0*S0,
                                        0*S4 | 0*S3 | 1*S2 | 0*S1 | 0*S0,
                                        0*S4 | 0*S3 | 1*S2 | 0*S1 | 0*S0,
                                        0*S4 | 0*S3 | 0*S2 | 0*S1 | 0*S0, },
                                      // U piece   4
                                      { 0*S4 | 0*S3 | 0*S2 | 0*S1 | 0*S0,
                                        0*S4 | 1*S3 | 0*S2 | 1*S1 | 0*S0,
                                        0*S4 | 1*S3 | 1*S2 | 1*S1 | 0*S0,
                                        0*S4 | 0*S3 | 0*S2 | 0*S1 | 0*S0,
                                        0*S4 | 0*S3 | 0*S2 | 0*S1 | 0*S0, },
                                      // V piece   5
                                      { 0*S4 | 0*S3 | 1*S2 | 0*S1 | 0*S0,
                                        0*S4 | 0*S3 | 1*S2 | 0*S1 | 0*S0,
                                        0*S4 | 0*S3 | 1*S2 | 1*S1 | 1*S0,
                                        0*S4 | 0*S3 | 0*S2 | 0*S1 | 0*S0,
                                        0*S4 | 0*S3 | 0*S2 | 0*S1 | 0*S0, },
                                      // W piece   6
                                      { 0*S4 | 0*S3 | 0*S2 | 0*S1 | 0*S0,
                                        0*S4 | 1*S3 | 0*S2 | 0*S1 | 0*S0,
                                        0*S4 | 1*S3 | 1*S2 | 0*S1 | 0*S0,
                                        0*S4 | 0*S3 | 1*S2 | 1*S1 | 0*S0,
                                        0*S4 | 0*S3 | 0*S2 | 0*S1 | 0*S0, },
                                      // F piece   7
                                      { 0*S4 | 0*S3 | 0*S2 | 0*S1 | 0*S0,
                                        0*S4 | 0*S3 | 1*S2 | 1*S1 | 0*S0,
                                        0*S4 | 1*S3 | 1*S2 | 0*S1 | 0*S0,
                                        0*S4 | 0*S3 | 1*S2 | 0*S1 | 0*S0,
                                        0*S4 | 0*S3 | 0*S2 | 0*S1 | 0*S0, },
                                      // N piece   8
                                      { 0*S4 | 0*S3 | 0*S2 | 0*S1 | 0*S0,
                                        0*S4 | 1*S3 | 0*S2 | 0*S1 | 0*S0,
                                        0*S4 | 1*S3 | 1*S2 | 0*S1 | 0*S0,
                                        0*S4 | 0*S3 | 1*S2 | 0*S1 | 0*S0,
                                        0*S4 | 0*S3 | 1*S2 | 0*S1 | 0*S0, },
                                      // L piece  9
                                      { 0*S4 | 0*S3 | 0*S2 | 0*S1 | 0*S0,
                                        0*S4 | 0*S3 | 0*S2 | 0*S1 | 0*S0,
                                        1*S4 | 1*S3 | 1*S2 | 1*S1 | 0*S0,
                                        0*S4 | 0*S3 | 0*S2 | 1*S1 | 0*S0,
                                        0*S4 | 0*S3 | 0*S2 | 0*S1 | 0*S0, },
                                      // P piece  10
                                      { 0*S4 | 0*S3 | 0*S2 | 0*S1 | 0*S0,
                                        0*S4 | 0*S3 | 1*S2 | 0*S1 | 0*S0,
                                        0*S4 | 1*S3 | 1*S2 | 0*S1 | 0*S0,
                                        0*S4 | 1*S3 | 1*S2 | 0*S1 | 0*S0,
                                        0*S4 | 0*S3 | 0*S2 | 0*S1 | 0*S0, },
                                      // Y piece  11
                                      { 0*S4 | 0*S3 | 0*S2 | 0*S1 | 0*S0,
                                        0*S4 | 0*S3 | 1*S2 | 0*S1 | 0*S0,
                                        1*S4 | 1*S3 | 1*S2 | 1*S1 | 0*S0,
                                        0*S4 | 0*S3 | 0*S2 | 0*S1 | 0*S0,
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
    if (piece[1] && (y < 1))
        return 0;
    if (piece[0] && (y < 2))
        return 0; // there is something in the first line, but not enough space
    if (piece[4] && (y > 5))
        return 0;
    if (piece[3] && (y > 6))
        return 0;
    // checks for horiziontal space
    if (x > 5) // There must be nothing in the left bits
        if ((piece[0] & S4) | (piece[1] & S4) | (piece[2] & S4) | (piece[3] & S4) | (piece[4] & S4))
            return 0;
    if (x > 6)
        if ((piece[0] & S3) | (piece[1] & S3) | (piece[2] & S3) | (piece[3] & S3) | (piece[4] & S3))
            return 0;
    if (x < 2) // there must be nothing in the right bits
        if ((piece[0] & S0) | (piece[1] & S0) | (piece[2] & S0) | (piece[3] & S0) | (piece[4] & S0))
            return 0;
    if (x < 1)
        if ((piece[0] & S1) | (piece[1] & S1) | (piece[2] & S1) | (piece[3] & S1) | (piece[4] & S1))
            return 0;
    return 1;
}

int insert_piece(uint8_t* table, int x, int y, uint8_t* piece) {
    if (y == 0) { // have to check only for piece[2], 3 and 4
        if (x == 0) {
            if ( ((piece[2] >> 2) & table[0]) ||
                 ((piece[3] >> 2) & table[1]) ||
                 ((piece[4] >> 2) & table[2])
                ) {
                return 0; // piece overlaps
            } else { // The piece does not overlap
                table[0] |= (piece[2] >> 2);
                table[1] |= (piece[3] >> 2);
                table[2] |= (piece[4] >> 2);
                return 1;
            }
        } else if (x == 1) {
            if ( ((piece[2] >> 1) & table[0]) ||
                 ((piece[3] >> 1) & table[1]) ||
                 ((piece[4] >> 1) & table[2])
                ) {
                return 0; // piece overlaps
            } else {
                table[0] |= (piece[2] >> 1);
                table[1] |= (piece[3] >> 1);
                table[2] |= (piece[4] >> 1);
                return 1;
            }
        } else {
            if ( ((piece[2] << (x-2)) & table[0]) ||
                 ((piece[3] << (x-2)) & table[1]) ||
                 ((piece[4] << (x-2)) & table[2])
                ) {
                return 0; // piece overlaps
            } else {
                table[0] |= (piece[2] << (x-2));
                table[1] |= (piece[3] << (x-2));
                table[2] |= (piece[4] << (x-2));
                return 1;
            }
        }
    } else if (y == 1) { // checks piece[1], 2, 3, and 4
        if (x == 0) {
            if ( ((piece[1] >> 2) & table[0]) ||
                 ((piece[2] >> 2) & table[1]) ||
                 ((piece[3] >> 2) & table[2]) ||
                 ((piece[4] >> 2) & table[3])
                ) {
                return 0; // piece overlaps
            } else {
                 table[0] |= (piece[1] >> 2);
                 table[1] |= (piece[2] >> 2);
                 table[2] |= (piece[3] >> 2);
                 table[3] |= (piece[4] >> 2);
                 return 1;
            }
        } else if (x == 1) {
            if ( ((piece[1] >> 1) & table[0]) ||
                 ((piece[2] >> 1) & table[1]) ||
                 ((piece[3] >> 1) & table[2]) ||
                 ((piece[4] >> 1) & table[3])
                ) {
                return 0; // piece overlaps
            } else {
                 table[0] |= (piece[1] >> 1);
                 table[1] |= (piece[2] >> 1);
                 table[2] |= (piece[3] >> 1);
                 table[3] |= (piece[4] >> 1);
                 return 1;
            }
        } else {
            if ( ((piece[1] << (x-2)) & table[0]) ||
                 ((piece[2] << (x-2)) & table[1]) ||
                 ((piece[3] << (x-2)) & table[2]) ||
                 ((piece[4] << (x-2)) & table[3])
                ) {
                return 0; // piece overlaps
            } else {
                 table[0] |= (piece[1] << (x-2));
                 table[1] |= (piece[2] << (x-2));
                 table[2] |= (piece[3] << (x-2));
                 table[3] |= (piece[4] << (x-2));
                 return 1;
            }
        }
    } else if (y == 6) { // Checks for pieces 0, 1, 2, and 3
        if (x == 0) {
            if ( ((piece[0] >> 2) & table[4]) ||
                 ((piece[1] >> 2) & table[5]) ||
                 ((piece[2] >> 2) & table[6]) ||
                 ((piece[3] >> 2) & table[7])
                ) {
                return 0; // piece overlaps
            } else {
                 table[4] |= (piece[0] >> 2);
                 table[5] |= (piece[1] >> 2);
                 table[6] |= (piece[2] >> 2);
                 table[7] |= (piece[3] >> 2);
                 return 1;
            }
        } else if (x == 1) {
            if ( ((piece[0] >> 1) & table[4]) ||
                 ((piece[1] >> 1) & table[5]) ||
                 ((piece[2] >> 1) & table[6]) ||
                 ((piece[3] >> 1) & table[7])
                ) {
                return 0; // piece overlaps
            } else {
                table[4] |= (piece[0] >> 1);
                table[5] |= (piece[1] >> 1);
                table[6] |= (piece[2] >> 1);
                table[7] |= (piece[3] >> 1);
                return 1;
            }
        } else {
            if ( ((piece[0] << (x-2)) & table[4]) ||
                 ((piece[1] << (x-2)) & table[5]) ||
                 ((piece[2] << (x-2)) & table[6]) ||
                 ((piece[3] << (x-2)) & table[7])
                ) {
                return 0; // piece overlaps
            } else {
                table[4] |= (piece[0] << (x-2));
                table[5] |= (piece[1] << (x-2));
                table[6] |= (piece[2] << (x-2));
                table[7] |= (piece[3] << (x-2));
                return 1;
            }
        }
    } else if (y == 7) {
        if (x == 0) {
            if ( ((piece[0] >> 2) & table[5]) ||
                 ((piece[1] >> 2) & table[6]) ||
                 ((piece[2] >> 2) & table[7])
                ) {
                return 0; // piece overlaps
            } else {
                table[5] |= (piece[0] >> 2);
                table[6] |= (piece[1] >> 2);
                table[7] |= (piece[2] >> 2);
                return 1;
            }
        } else if (x == 1) {
            if ( ((piece[0] >> 1) & table[5]) ||
                 ((piece[1] >> 1) & table[6]) ||
                 ((piece[2] >> 1) & table[7])
                ) {
                return 0; // piece overlaps
            } else {
                table[5] |= (piece[0] >> 1);
                table[6] |= (piece[1] >> 1);
                table[7] |= (piece[2] >> 1);
                return 1;
            }
        } else {
            if ( ((piece[0] << (x-2)) & table[5]) ||
                 ((piece[1] << (x-2)) & table[6]) ||
                 ((piece[2] << (x-2)) & table[7])
                ) {
                return 0; // piece overlaps
            } else {
                table[5] |= (piece[0] << (x-2));
                table[6] |= (piece[1] << (x-2));
                table[7] |= (piece[2] << (x-2));
                return 1;
            }
        }
    } else { // Normal case
        if (x == 0) {
            if ( ((piece[0] >> 2) & table[y-2]) ||
                 ((piece[1] >> 2) & table[y-1]) ||
                 ((piece[2] >> 2) & table[y  ]) ||
                 ((piece[3] >> 2) & table[y+1]) ||
                 ((piece[4] >> 2) & table[y+2])
                ) {
                return 0; // piece overlaps
            } else {
                table[y-2] |= (piece[0] >> 2);
                table[y-1] |= (piece[1] >> 2);
                table[y  ] |= (piece[2] >> 2);
                table[y+1] |= (piece[3] >> 2);
                table[y+2] |= (piece[4] >> 2);
                return 1;
            }
        } else if (x == 1) {
            if ( ((piece[0] >> 1) & table[y-2]) ||
                 ((piece[1] >> 1) & table[y-1]) ||
                 ((piece[2] >> 1) & table[y  ]) ||
                 ((piece[3] >> 1) & table[y+1]) ||
                 ((piece[4] >> 1) & table[y+2])
                ) {
                return 0; // piece overlaps
            } else {
                table[y-2] |= (piece[0] >> 1);
                table[y-1] |= (piece[1] >> 1);
                table[y  ] |= (piece[2] >> 1);
                table[y+1] |= (piece[3] >> 1);
                table[y+2] |= (piece[4] >> 1);
                return 1;
            }
        } else { // General case:
            if ( ((piece[0] << (x-2)) & table[y-2]) ||
                 ((piece[1] << (x-2)) & table[y-1]) ||
                 ((piece[2] << (x-2)) & table[y  ]) ||
                 ((piece[3] << (x-2)) & table[y+1]) ||
                 ((piece[4] << (x-2)) & table[y+2])
                ) {
                return 0; // piece overlaps
            } else {
                table[y-2] |= (piece[0] << (x-2));
                table[y-1] |= (piece[1] << (x-2));
                table[y  ] |= (piece[2] << (x-2));
                table[y+1] |= (piece[3] << (x-2));
                table[y+2] |= (piece[4] << (x-2));
                return 1;
            }
        }
    }
}

int insert_wrap(uint8_t* table, int x, int y, uint8_t* piece) {
    if (!enough_space(x, y, piece))
        return 0; // skip if there is not enough space
    if (!insert_piece(table, x, y, piece))
        return 0;
    return 1;
}

void rotate_piece_ncp(uint8_t * piece){ // non copy
    uint8_t swap[5];
    rotate_piece(piece, swap);
    memcpy(piece, swap, 5*sizeof*piece); // copies the data in a temporany mem space
}

void symmetrize_piece_ncp(uint8_t * piece) {
    symmetrize_piece(piece, piece);
}

void printtable(uint8_t * table) {
    int i, j;
    for (i = 0; i < 8; i++) {
        for (j = 7; j >= 0; j--) {
            printf("%d ", !!(table[i] & _BV(j)));
        }
        printf("\n");
    }
}

int holes(const uint8_t * table) {
    int x, y;
    for (x = 0; x < 8; x++) {
        for (y = 0; y < 8; y++) {
            if (!(table[y] & _BV(x))) { // found a whitespace, now if boundaries are 1 returns 0
                if (y == 0) { // do not checks y - 1
                    if (x == 0) { // Checks everything but x -1
                        if ((table[y+1] & _BV(x)) &&
                            (table[y] & _BV(x+1)) ) // found a hole
                            return 1;
                    } else if (x == 7) { // checks everything but x+1
                        if ((table[y+1] & _BV(x)) &&
                            (table[y] & _BV(x-1)) ) // found a hole
                            return 1;
                    } else { // normal case
                        if ((table[y+1] & _BV(x)) &&
                            (table[y] & _BV(x-1)) && (table[y] & _BV(x+1)) ) // found a hole
                            return 1;
                    }
                } else if (y == 7) { // Do not check y + 1
                    if (x == 0) { // Checks everything but x -1
                        if ((table[y-1] & _BV(x)) &&
                            (table[y] & _BV(x+1)) ) // found a hole
                            return 1;
                    } else if (x == 7) { // checks everything but x+1
                        if ((table[y-1] & _BV(x)) &&
                            (table[y] & _BV(x-1)) ) // found a hole
                            return 1;
                    } else { // normal case
                        if ((table[y-1] & _BV(x)) &&
                            (table[y] & _BV(x-1)) && (table[y] & _BV(x+1)) ) // found a hole
                            return 1;
                    }
                } else {
                    if (x == 0) { // Checks everything but x -1
                        if ((table[y-1] & _BV(x)) && (table[y+1] & _BV(x)) &&
                            (table[y] & _BV(x+1)) ) // found a hole
                            return 1;
                    } else if (x == 7) { // checks everything but x+1
                        if ((table[y-1] & _BV(x)) && (table[y+1] & _BV(x)) &&
                            (table[y] & _BV(x-1)) ) // found a hole
                            return 1;
                    } else { // normal case
                        if ((table[y-1] & _BV(x)) && (table[y+1] & _BV(x)) &&
                            (table[y] & _BV(x-1)) && (table[y] & _BV(x+1)) ) // found a hole
                            return 1;
                    }
                }
            }
        }
    }
    return 0;
}

void print_color(int id) {
    if (id == 0)
        printf(COLOR_RESET);
    else if (id == 1 )
        printf(COLOR_1);
    else if (id == 2 )
        printf(COLOR_2);
    else if (id == 3 )
        printf(COLOR_3);
    else if (id == 4 )
        printf(COLOR_4);
    else if (id == 5 )
        printf(COLOR_5);
    else if (id == 6 )
        printf(COLOR_6);
    else if (id == 7 )
        printf(COLOR_7);
    else if (id == 8 )
        printf(COLOR_8);
    else if (id == 9 )
        printf(COLOR_9);
    else if (id == 10)
        printf(COLOR_10);
    else if (id == 11)
        printf(COLOR_11);
    else if (id == 12)
        printf(COLOR_12);
    else if (id == -1)
        printf(COLOR_14);
    else
        printf(COLOR_13);
}

int get_bit(const uint8_t * table, int x, int y) {
    return !!(table[y] & _BV(x));
}

#define COLORED_OUTPUT_BACKGROUND

#define CELL_WIDTH  3
#define CELL_HEIGHT 1
#define CENTERS         " "
#define HBAR            "-"
#define HNBAR           " "
#define VBAR            "|"
#define VNBAR           " "
#define CROSS_DOWNLEFT  "."
#define CROSS_DOWNRIGHT "."
#define CROSS_UPLEFT    "\'"
#define CROSS_UPRIGHT   "\'"
#define CROSS_UPDOWN    "|"
#define CROSS_LEFTRIGHT "-"
#define CROSS_UPDOWNLEFT "+"
#define CROSS_UPDOWNRIGHT "+"
#define CROSS_LEFTRIGHTUP  "+"
#define CROSS_LEFTRIGHTDOWN "+"
#define CROSS_UDLR      "+" // up, down, left and right
#define CROSS_NONE      " " // No cross !

#ifdef COLORED_OUTPUT_BACKGROUND
    #define CENTER_PRINT_COLOR(i)  print_color(i+1)
    #define CENTER_CLEAR_COLOR()   print_color(0)
    #define HBAR_PRINT_COLOR(i, j)  print_color(-1)
    #define HBAR_CLEAR_COLOR()      print_color(0)
    #define VBAR_PRINT_COLOR(i, j)  print_color(-1)
    #define VBAR_CLEAR_COLOR()      print_color(0)
    #define HNBAR_PRINT_COLOR(i)  print_color(i+1)
    #define HNBAR_CLEAR_COLOR()   print_color(0)
    #define VNBAR_PRINT_COLOR(i)  print_color(i+1)
    #define VNBAR_CLEAR_COLOR()   print_color(0)
    #define CROSS_PRINT_COLOR(i, j, k, l)  if ( ((i) == (j)) && ((j) == (k)) && \
                                                ((k) == (l))                 )  \
                                                print_color(i+1);               \
                                            else                                \
                                                print_color(-1)
    #define CROSS_CLEAR_COLOR()      print_color(0)
    #define NCROSS_PRINT_COLOR(i)    print_color(i+1)
    #define NCROSS_CLEAR_COLOR()     print_color(0)
#else
    #define CENTER_PRINT_COLOR(i)  // Do nothing
    #define CENTER_CLEAR_COLOR()   // Do nothing
    #define HBAR_PRINT_COLOR(i, j)  // Do nothing
    #define HBAR_CLEAR_COLOR()      // Do nothing
    #define VBAR_PRINT_COLOR(i, j)  // Do nothing
    #define VBAR_CLEAR_COLOR()      // Do nothing
    #define HNBAR_PRINT_COLOR(i)  // Do nothing
    #define HNBAR_CLEAR_COLOR()   // Do nothing
    #define VNBAR_PRINT_COLOR(i)  // Do nothing
    #define VNBAR_CLEAR_COLOR()   // Do nothing
    #define CROSS_PRINT_COLOR(i, j, k, l)  // Do nothing
    #define CROSS_CLEAR_COLOR()      // Do nothing
    #define NCROSS_PRINT_COLOR(i)    // Do nothing
    #define NCROSS_CLEAR_COLOR()     // Do nothing
#endif

int print_solution(const uint8_t * rot, const uint8_t * coord) {
    int x, y, y1, i, j, k, l;
    uint8_t ptable[12*8];
    uint8_t temp_table[5];
    static int idsolution = 0;

    printf("Solution number: %d\n", idsolution++);
    // Print the solution
    for (i = 0; i < 12; i++) {
        memcpy(temp_table, piece_table[i], 5*sizeof*temp_table);

        // resets table
        for (x = 0; x < 8; x++)
            ptable[i*8+x] = 0;

        if (rot[i] == 1) {
            rotate_piece_ncp(temp_table);
        } else if (rot[i] == 2) {
            rotate_piece_ncp(temp_table);
            rotate_piece_ncp(temp_table);
        } else if (rot[i] == 3) {
            rotate_piece_ncp(temp_table);
            rotate_piece_ncp(temp_table);
            rotate_piece_ncp(temp_table);
        } else if (rot[i] == 4) {
            symmetrize_piece_ncp(temp_table);
        } else if (rot[i] == 5) {
            rotate_piece_ncp(temp_table);
            symmetrize_piece_ncp(temp_table);
        } else if (rot[i] == 6) {
            symmetrize_piece_ncp(temp_table);
            rotate_piece_ncp(temp_table);
            rotate_piece_ncp(temp_table);
        } else if (rot[i] == 7) {
            symmetrize_piece_ncp(temp_table);
            rotate_piece_ncp(temp_table);
        }
        //printf("x: %d, y: %d, rot: %d\n", coord[i] >> 4, coord[i] & 15, rot[i]);
        insert_wrap(ptable + i*8, coord[i] >> 4, coord[i] & 15, temp_table);
        //printtable(ptable + i*8);
        //printf("\n");
    }

    // Now have to search for bounds
    for (i = 0; i < 12; i++) {
        if (get_bit(ptable+i*8, 7, 0))
            break;
    }
    CROSS_PRINT_COLOR(-1, -1, -1, i);
    printf(CROSS_DOWNRIGHT);
    CROSS_CLEAR_COLOR();
    for (j = 0; j < CELL_WIDTH; j++) {
        HBAR_PRINT_COLOR(-1, i);
        printf(HBAR);
        HBAR_CLEAR_COLOR();
    }
    for (x = 7; x > 0; x--) {
        for (j = 0; j < 12; j++) {
            if (get_bit(ptable+j*8, (x-1), 0))
                break;
        }

        if (i != j) { // Different pieces, so there is a node
            CROSS_PRINT_COLOR(-1, -1, i, j);
            printf(CROSS_LEFTRIGHTDOWN);
            CROSS_CLEAR_COLOR();
        } else {
            CROSS_PRINT_COLOR(-1, -1, i, j);
            printf(CROSS_LEFTRIGHT);
            CROSS_CLEAR_COLOR();
        }
        i = j; // Sets old color to the new color

        for (j = 0; j < CELL_WIDTH; j++) {
            HBAR_PRINT_COLOR(-1, i);
            printf(HBAR);
            HBAR_CLEAR_COLOR();
        }
    }
    CROSS_PRINT_COLOR(-1, -1, i, -1);
    printf(CROSS_DOWNLEFT);
    CROSS_CLEAR_COLOR();
    printf("\n");
    for (y = 0; y < 8; y++) {
        for (y1 = 0; y1 < CELL_HEIGHT; y1++) {
            for (i = 0; i < 12; i++) {
                if (get_bit(ptable+i*8, 7, y))
                    break;
            }
            VBAR_PRINT_COLOR(-1, i);
            printf(VBAR);
            VBAR_CLEAR_COLOR();
            for (j = 0; j < CELL_WIDTH; j++) { // Printing the center
                CENTER_PRINT_COLOR(i);
                printf(CENTERS);
                CENTER_CLEAR_COLOR();
            }
            for (x = 7; x > 0; x--){
                for (j = 0; j < 12; j++) { // Search for color
                    if (get_bit(ptable+j*8, x-1, y))
                        break;
                }
                if (i != j) { // Different colors, prints the vertical bar
                    VBAR_PRINT_COLOR(i, j);
                    printf(VBAR);
                    VBAR_CLEAR_COLOR();
                } else { // Same colors, does not print the bar
                    VNBAR_PRINT_COLOR(i);
                    printf(VNBAR);
                    VNBAR_CLEAR_COLOR();
                }
                i = j;
                // Now prints the cell center
                for (j = 0; j < CELL_WIDTH; j++) { // Printing the center
                    CENTER_PRINT_COLOR(i);
                    printf(CENTERS);
                    CENTER_CLEAR_COLOR();
                }
            }
            VBAR_PRINT_COLOR(i, -1);
            printf(VBAR);
            VBAR_CLEAR_COLOR();
            printf("\n");
        }
        if (y != 7) { // now prints the horizontal lines, if y != 7
            for (i = 0; i < 12; i++) {
                if (get_bit(ptable+i*8, 7, y))
                    break;
            }
            for (k = 0; k < 12; k++) {
                if (get_bit(ptable+k*8, 7, y+1))
                    break;
            }
            // Prints the left border
            if (i == k) {
                CROSS_PRINT_COLOR(-1, i, -1, k);
                printf(CROSS_UPDOWN);
                CROSS_CLEAR_COLOR();
                for (j = 0; j < CELL_WIDTH; j++) {
                    HNBAR_PRINT_COLOR(i);
                    printf(HNBAR); // Piece above and below are equals, does not print hbar
                    HNBAR_CLEAR_COLOR();
                }
            } else {
                CROSS_PRINT_COLOR(-1, i, -1, k);
                printf(CROSS_UPDOWNRIGHT);
                CROSS_CLEAR_COLOR();
                for (j = 0; j < CELL_WIDTH; j++) {
                    HBAR_PRINT_COLOR(i, k);
                    printf(HBAR); // Piece above and below are equals, prints hbar
                    HBAR_CLEAR_COLOR();
                }
            }

            for (x = 7; x > 0; x--) {
                for (j = 0; j < 12; j++) {
                    if (get_bit(ptable+j*8, (x-1), y))
                        break;
                }
                for (l = 0; l < 12; l++) {
                    if (get_bit(ptable+l*8, (x-1), y+1))
                        break;
                }

                y1 = 0;
                if (k != i) y1 |= 0x1;
                if (i != j) y1 |= 0x2;
                if (j != l) y1 |= 0x4;
                if (l != k) y1 |= 0x8;

                CROSS_PRINT_COLOR(i, j, k, l);
                switch (y1) {
                    case 0: // k = i = j = l
                        // it is like a center piece
                        printf(CROSS_NONE);
                        break;
                    case 0x2 | 0x8:
                        printf(CROSS_UPDOWN);
                        break;
                    case 0x1 | 0x4:
                        printf(CROSS_LEFTRIGHT);
                        break;
                    case 0x1 | 0x2 | 0x4:
                        printf(CROSS_LEFTRIGHTUP);
                        break;
                    case 0x1 | 0x2 | 0x8:
                        printf(CROSS_UPDOWNLEFT);
                        break;
                    case 0x1 | 0x4 | 0x8:
                        printf(CROSS_LEFTRIGHTDOWN);
                        break;
                    case 0x2 | 0x4 | 0x8:
                        printf(CROSS_UPDOWNRIGHT);
                        break;
                    case 0x1 | 0x2:
                        printf(CROSS_UPLEFT);
                        break;
                    case 0x2 | 0x4:
                        printf(CROSS_UPRIGHT);
                        break;
                    case 0x4 | 0x8:
                        printf(CROSS_DOWNRIGHT);
                        break;
                    case 0x8 | 0x1:
                        printf(CROSS_DOWNLEFT);
                        break;
                    default: // case 0xF, all different
                        printf(CROSS_UDLR);
                }
                CROSS_CLEAR_COLOR();

                i = j; // Sets old color to the new color
                k = l;

                for (j = 0; j < CELL_WIDTH; j++) {
                    if (i == k) {
                        HNBAR_PRINT_COLOR(i);
                        printf(HNBAR); // Piece above and below are equals, does not print hbar
                        HNBAR_CLEAR_COLOR();
                    } else {
                        HBAR_PRINT_COLOR(k, i);
                        printf(HBAR); // Piece above and below are equals, prints hbar
                        HBAR_CLEAR_COLOR();
                    }
                }
            }

            if (i == k) {
                CROSS_PRINT_COLOR(i, -1, k, -1);
                printf(CROSS_UPDOWN);
                CROSS_CLEAR_COLOR();
            } else {
                CROSS_PRINT_COLOR(i, -1, k, -1);
                printf(CROSS_UPDOWNLEFT);
                CROSS_CLEAR_COLOR();
            }

            printf("\n");
        } else { // y == 7, prints the horiziontal bottom line
            for (i = 0; i < 12; i++) {
                if (get_bit(ptable+i*8, 7, 7))
                    break;
            }
            CROSS_PRINT_COLOR(-1, i, -1, -1);
            printf(CROSS_UPRIGHT);
            CROSS_CLEAR_COLOR();
            for (j = 0; j < CELL_WIDTH; j++) {
                HBAR_PRINT_COLOR(i, -1);
                printf(HBAR);
                HBAR_CLEAR_COLOR();
            }
            for (x = 7; x > 0; x--) {
                for (j = 0; j < 12; j++) {
                    if (get_bit(ptable+j*8, (x-1), 7))
                        break;
                }

                if (i != j) { // Different pieces, so there is a node
                    CROSS_PRINT_COLOR(i, j, -1, -1);
                    printf(CROSS_LEFTRIGHTUP);
                    CROSS_CLEAR_COLOR();
                } else {
                    CROSS_PRINT_COLOR(i, j, -1, -1);
                    printf(CROSS_LEFTRIGHT);
                    CROSS_CLEAR_COLOR();
                }
                i = j; // Sets old color to the new color

                for (j = 0; j < CELL_WIDTH; j++) {
                    HBAR_PRINT_COLOR(i, -1);
                    printf(HBAR);
                    HBAR_CLEAR_COLOR();
                }
            }
            CROSS_PRINT_COLOR(i, -1, -1, -1);
            printf(CROSS_UPLEFT);
            CROSS_CLEAR_COLOR();
            printf("\n");
        }
    }
    /*
    for (y = 0; y < 8; y++) {
        for (x = 7; x >= 0; x--) {
            for (i = 0; i < 12; i++) {
                if (get_bit(ptable+i*8, x, y))
                    break;
            }
            i++;
            print_color(i);
            printf("  ");
            print_color(0); // resets color
        }
        printf("\n");
    }
    */
    return 0;
}

int next(const uint8_t * table, int pos, uint8_t * rot, uint8_t * coord) {
    int x, y, solutions = 0;
    uint8_t exec_table[8]; // dynamic table where process the data
    uint8_t tpos[5]; // temporany pentamino, rotated

    if (pos == 12) { // FOUND A SOLUTION !!!!
        print_solution(rot, coord);
        printf("\n");
        return 1;
    } else {
        if (holes(table)) // impossible case to solve
            return 0;
        for (x = 0; x < 8; x++)
        for (y = 0; y < 8; y++) {
            memcpy(tpos, piece_table[pos], 5*sizeof*tpos); // copies the data in a temporany mem space
            memcpy(exec_table, table, 8*sizeof*exec_table); // resets data
            coord[pos] = (x << 4) | (y);
            if (pos == 0) { // Cross, does not have to compute rotations and symmetries
                if ((x > 4) || (y > 4))
                    continue; // All other cases can be reached by rotation
                if (insert_wrap(exec_table, x, y, tpos)) {
                    rot[pos] = 0; // no rotations
                    solutions += next(exec_table, pos+1, rot, coord); // recursive call
                }
            } else if (pos == 1) { // trying to insert the horizontal bar, two cases
                if (insert_wrap(exec_table, x, y, tpos)) {
                    rot[pos] = 0; // no rotations
                    solutions += next(exec_table, pos+1, rot, coord); // recursive call
                    memcpy(exec_table, table, 8*sizeof*exec_table); // resets data
                }
                rotate_piece_ncp(tpos);
                if (insert_wrap(exec_table, x, y, tpos)) { // try to insert in the table
                    rot[pos] = 1; // 90° rotation
                    solutions += next(exec_table, pos+1, rot, coord); // recursive call
                }
            } else if (pos == 2) { // inserting a Z piece, two rotations and two symmetries
                if (insert_wrap(exec_table, x, y, tpos)) {
                    rot[pos] = 0; // no rotations
                    solutions += next(exec_table, pos+1, rot, coord); // recursive call
                    memcpy(exec_table, table, 8*sizeof*exec_table); // resets data
                }
                rotate_piece_ncp(tpos);
                if (insert_wrap(exec_table, x, y, tpos)) { // try to insert in the table
                    rot[pos] = 1; // 90° rotation
                    solutions += next(exec_table, pos+1, rot, coord); // recursive call
                    memcpy(exec_table, table, 8*sizeof*exec_table); // resets data
                }
                // now have to compute simmetries
                symmetrize_piece_ncp(tpos);
                if (insert_wrap(exec_table, x, y, tpos)) { // try to insert in the table
                    rot[pos] = 4; // 90° rotation + symmetry
                    solutions += next(exec_table, pos+1, rot, coord); // recursive call
                    memcpy(exec_table, table, 8*sizeof*exec_table); // resets data
                }
                rotate_piece_ncp(tpos);
                if (insert_wrap(exec_table, x, y, tpos)) { // try to insert in the table
                    rot[pos] = 7; // 0° rotation + simmetry
                    solutions += next(exec_table, pos+1, rot, coord); // recursive call
                }
            } else if (pos < 7) { // 4 cases all reachable with rotations
                if (insert_wrap(exec_table, x, y, tpos)) {
                    rot[pos] = 0; // no rotations
                    solutions += next(exec_table, pos+1, rot, coord); // recursive call
                    memcpy(exec_table, table, 8*sizeof*exec_table); // resets data
                }
                rotate_piece_ncp(tpos);
                if (insert_wrap(exec_table, x, y, tpos)) { // try to insert in the table
                    rot[pos] = 1; // 90° rotation
                    solutions += next(exec_table, pos+1, rot, coord); // recursive call
                    memcpy(exec_table, table, 8*sizeof*exec_table); // resets data
                }
                rotate_piece_ncp(tpos);
                if (insert_wrap(exec_table, x, y, tpos)) { // try to insert in the table
                    rot[pos] = 2; // 180° rotation
                    solutions += next(exec_table, pos+1, rot, coord); // recursive call
                    memcpy(exec_table, table, 8*sizeof*exec_table); // resets data
                }
                rotate_piece_ncp(tpos);
                if (insert_wrap(exec_table, x, y, tpos)) { // try to insert in the table
                    rot[pos] = 3; // 270° rotation
                    solutions += next(exec_table, pos+1, rot, coord); // recursive call
                }
            } else { // default behavior, 8 positions, reachable with rotations and symmetries
                if (insert_wrap(exec_table, x, y, tpos)) {
                    rot[pos] = 0; // no rotations
                    solutions += next(exec_table, pos+1, rot, coord); // recursive call
                    memcpy(exec_table, table, 8*sizeof*exec_table); // resets data
                }
                rotate_piece_ncp(tpos);
                if (insert_wrap(exec_table, x, y, tpos)) { // try to insert in the table
                    rot[pos] = 1; // 90° rotation
                    solutions += next(exec_table, pos+1, rot, coord); // recursive call
                    memcpy(exec_table, table, 8*sizeof*exec_table); // resets data
                }
                rotate_piece_ncp(tpos);
                if (insert_wrap(exec_table, x, y, tpos)) { // try to insert in the table
                    rot[pos] = 2; // 180° rotation
                    solutions += next(exec_table, pos+1, rot, coord); // recursive call
                    memcpy(exec_table, table, 8*sizeof*exec_table); // resets data
                }
                rotate_piece_ncp(tpos);
                if (insert_wrap(exec_table, x, y, tpos)) { // try to insert in the table
                    rot[pos] = 3; // 270° rotation
                    solutions += next(exec_table, pos+1, rot, coord); // recursive call
                    memcpy(exec_table, table, 8*sizeof*exec_table); // resets data
                }
                // Now computes symmetries
                symmetrize_piece_ncp(tpos);
                if (insert_wrap(exec_table, x, y, tpos)) { // try to insert in the table
                    rot[pos] = 7; // 270° rotation + symmetry
                    solutions += next(exec_table, pos+1, rot, coord); // recursive call
                    memcpy(exec_table, table, 8*sizeof*exec_table); // resets data
                }
                rotate_piece_ncp(tpos);
                if (insert_wrap(exec_table, x, y, tpos)) { // try to insert in the table
                    rot[pos] = 6; // 0° rotation + symmetry
                    solutions += next(exec_table, pos+1, rot, coord); // recursive call
                    memcpy(exec_table, table, 8*sizeof*exec_table); // resets data
                }
                rotate_piece_ncp(tpos);
                if (insert_wrap(exec_table, x, y, tpos)) { // try to insert in the table
                    rot[pos] = 5; // 90° rotation + symmetry
                    solutions += next(exec_table, pos+1, rot, coord); // recursive call
                    memcpy(exec_table, table, 8*sizeof*exec_table); // resets data
                }
                rotate_piece_ncp(tpos);
                if (insert_wrap(exec_table, x, y, tpos)) { // try to insert in the table
                    rot[pos] = 4; // 180° rotation
                    solutions += next(exec_table, pos+1, rot, coord); // recursive call
                }
            }
        }
        return solutions;
    }
}

int main(int argc, char * argv[]) {
    uint8_t tab[8];
    uint8_t rot[12]; // there are 12 pieces
    uint8_t pos[12];
    int x;
    for (x = 0; x < 8; x++)
        tab[x] = 0; // initialize table
    //printtable(tab);
    //insert_wrap(tab, )
    x = next(tab, 0, rot, pos);
    printf("FINISH!\nFound %d solutions\n", x);
    return 0;
}
