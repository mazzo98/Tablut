#ifndef BOARD_H
#define BOARD_H

#include "Bitboard.h"
#include "List.h"

//ashton tablut values to initialize the pawns and the citadels, escapes and castle
//same as the black init position
#define A_CITADEL_1 0x1C040010
#define A_CITADEL_2 0x1C1C0400
#define A_CITADEL_3 0x101C0000
//same as the king init position
#define A_CASTLE_1 0x0
#define A_CASTLE_2 0x800000
#define A_CASTLE_3 0x0

#define A_WHITE_1 0x201
#define A_WHITE_2 0x3604020
#define A_WHITE_3 0x0

#define A_BLACK_1 A_CITADEL_1
#define A_BLACK_2 A_CITADEL_2
#define A_BLACK_3 A_CITADEL_3

#define A_ESCAPE_1 0x63406020
#define A_ESCAPE_2 0x203
#define A_ESCAPE_3 0x1630000

static Bitboard CASTLE = { A_CASTLE_1, A_CASTLE_2, A_CASTLE_3 };
static Bitboard CITADEL = { A_CITADEL_1, A_CITADEL_2, A_CITADEL_3 };
static Bitboard ESCAPE = { A_ESCAPE_1, A_ESCAPE_2, A_ESCAPE_3 };

typedef struct
{
    Bitboard black;
    Bitboard white;
    Bitboard king;

} Board;

int winning_condition(Bitboard kingB);

int lose_condition(Bitboard kingB);

int draw_condition(node_t *n, Bitboard black, Bitboard white, Bitboard king);

Bitboard findAllForAll(Board from);

Bitboard findColForOne(Bitboard from, int col);

Bitboard findRowForOne(Bitboard from, int row);

Bitboard findAllForOne(Bitboard from, int row, int col);

#endif