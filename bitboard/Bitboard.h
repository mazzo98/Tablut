#include <stdint.h>
#include <stdio.h>

#define INT_SIZE (8 * sizeof(uint32_t))
#define WIDTH 9

typedef struct
{
    uint32_t bb[3];

} Bitboard;

void showBits(uint32_t x);

void printBitboard(Bitboard b);

void printLikeBoard(Bitboard b, int line);

Bitboard And(Bitboard from1, Bitboard from2);

Bitboard Or(Bitboard from1, Bitboard from2);

Bitboard Xor(Bitboard from1, Bitboard from2);

Bitboard Not(Bitboard from);

Bitboard rightShift(Bitboard from, int shift);

Bitboard leftShift(Bitboard from, int shift);

Bitboard setCellState(Bitboard from, int row, int col);

int getCellState(Bitboard from, int row, int col);