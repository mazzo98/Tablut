#include "Bitboard.h"
#include "Board.h"

int main(int argc, char *argv[])
{
    // Bitboard b1;
    // int line = 9;
    // b1.bb[0] = 1;
    // b1.bb[1] = 1;
    // b1.bb[2] = 3;
    // printBitboard(b1);
    // printLikeBoard(b1, line);

    // Bitboard b2;
    // b2 = leftShift(b1, 80);
    // b2 = Not(b1);
    // printBitboard(b2);

    // Bitboard b3;

    // b3.bb[0] = 1;
    // b3.bb[1] = 4;
    // b3.bb[2] = 34546;
    // Bitboard newB = setCellState(b3, 3, 5);
    // printLikeBoard(newB, WIDTH);
    // Bitboard prova = rightShift(newB, 27);
    // printLikeBoard(prova, WIDTH);
    // Bitboard prova1 = leftShift(prova, 27);
    // printLikeBoard(prova1, WIDTH);

    // int res = getCellState(newB, 3, 4);
    // printf("%d\n", res);

    // uint32_t n = 4294934528;
    // showBits(n);
    // showBits(~32767);

    // int pawns = countBitSet(b3);
    // printf("%d\n", pawns);

    //initial board
    // AshtonBoard b1;
    // b1.citadel = setBitboard(470024208, 471598080, 270270464);
    // printf("citadels (init blacks)\n");
    // printLikeBoard(b1.citadel, WIDTH);
    // b1.black = setBitboard(470024208, 471598080, 270270464);
    // b1.castle = setBitboard(0, 8388608, 0);
    // printf("castle (init king)\n");
    // printLikeBoard(b1.castle, WIDTH);
    // b1.king = setBitboard(0, 8388608, 0);
    // b1.white = setBitboard(513, 56639520, 0);
    // printf("init whites\n");
    // printLikeBoard(b1.white, WIDTH);
    // b1.escape = setBitboard(1665163296, 515, 23265280);
    // printf("escapes\n");
    // printLikeBoard(b1.escape, WIDTH);

    Board b1;
    b1.citadel = setBitboard(A_CITADEL_1, A_CITADEL_2, A_CITADEL_3);
    printf("citadels (init blacks)\n");
    printLikeBoard(b1.citadel, WIDTH);
    b1.black = setBitboard(470024208, 471598080, 270270464);
    b1.castle = setBitboard(A_CASTLE_1, A_CASTLE_2, A_CASTLE_3);
    printf("castle (init king)\n");
    printLikeBoard(b1.castle, WIDTH);
    b1.king = setBitboard(0, 8388608, 0);
    b1.white = setBitboard(A_WHITE_1, A_WHITE_2, A_WHITE_3);
    printf("init whites\n");
    printLikeBoard(b1.white, WIDTH);
    b1.escape = setBitboard(A_ESCAPE_1, A_ESCAPE_2, A_ESCAPE_3);
    printf("escapes\n");
    printLikeBoard(b1.escape, WIDTH);
}