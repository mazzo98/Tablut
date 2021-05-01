#include "Bitboard.h"

int main(int argc, char *argv[])
{
    Bitboard b1;
    int line = 9;
    b1.bb[0] = 1;
    b1.bb[1] = 1;
    b1.bb[2] = 3;
    printBitboard(b1);
    printLikeBoard(b1, line);

    Bitboard b2;
    Bitboard b3;
    b2 = leftShift(b1, 80);
    b2 = Not(b1);
    printBitboard(b2);
}