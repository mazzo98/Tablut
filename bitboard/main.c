#include "Bitboard.h"

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

    Bitboard b3;

    b3.bb[0] = 1;
    b3.bb[1] = 4;
    b3.bb[2] = 34546;
    Bitboard newB = setCellState(b3, 3, 5);
    printLikeBoard(newB, WIDTH);
    Bitboard prova = rightShift(newB, 27);
    printLikeBoard(prova, WIDTH);
    Bitboard prova1 = leftShift(prova, 27);
    printLikeBoard(prova1, WIDTH);

    int res = getCellState(newB, 3, 4);
    printf("%d\n", res);

    uint32_t n = 4294934528;
    showBits(n);
}