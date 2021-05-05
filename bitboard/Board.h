//ashton tablut values to initialize the pawns and the citadels, escapes and castle
//same as the black init position
#define A_CITADEL_1 470024208
#define A_CITADEL_2 471598080
#define A_CITADEL_3 270270464
//same as the king init position
#define A_CASTLE_1 0
#define A_CASTLE_2 8388608
#define A_CASTLE_3 0

#define A_WHITE_1 513
#define A_WHITE_2 56639520
#define A_WHITE_3 0

#define A_ESCAPE_1 1665163296
#define A_ESCAPE_2 515
#define A_ESCAPE_3 23265280

typedef struct
{
    Bitboard black;
    Bitboard white;
    Bitboard citadel;
    Bitboard king;
    Bitboard castle;
    Bitboard escape;

} Board;

int winning_condition(Bitboard kingB, Bitboard escapeB);

int lose_condition(Bitboard kingB);