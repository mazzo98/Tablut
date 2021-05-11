#include "ListMoves.h"
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
    //b1.citadel = setBitboard(A_CITADEL_1, A_CITADEL_2, A_CITADEL_3);
    // printf("citadels (init blacks)\n");
    // printLikeBoard(b1.citadel, WIDTH);
    b1.black = setBitboard(A_BLACK_1, A_BLACK_2, A_BLACK_3);
    //b1.castle = setBitboard(A_CASTLE_1, A_CASTLE_2, A_CASTLE_3);
    // printf("castle (init king)\n");
    // printLikeBoard(b1.castle, WIDTH);
    b1.king = setBitboard(A_CASTLE_1, A_CASTLE_2, A_CASTLE_1);
    b1.white = setBitboard(A_WHITE_1, A_WHITE_2, A_WHITE_3);
    // printf("init whites\n");
    // printLikeBoard(b1.white, WIDTH);
    //b1.escape = setBitboard(A_ESCAPE_1, A_ESCAPE_2, A_ESCAPE_3);
    //printf("escapes\n");
    //printLikeBoard(b1.escape, WIDTH);
    b1.black = setCellState(b1.black, 2, 6);
    //printLikeBoard(b1.black, WIDTH);

    // printLikeBoard(Not(b1.citadel), WIDTH);
    // printf("%d\n", countBitSet(Not(b1.citadel)));

    //b1.king = setCellState(b1.king, 0, 1);
    //printLikeBoard(b1.king, WIDTH);

    // b1.king = setCellState(b1.king, 0, 1);
    // int win = winning_condition(b1.king, b1.escape);
    // if (win == 1)
    //     printf("hai vinto\n");

    // int lose = lose_condition(b1.king);
    // if (lose == 1)
    //     printf("hai perso\n");

    // node_t *head = NULL;
    // //first node: initial state
    // append(&head, b1.black, b1.white, b1.king);
    // push(&head, Not(b1.black), b1.white, b1.king);
    // printList(head);

    // Bitboard a1 = Or(b1.white, b1.castle);
    // Bitboard a2 = Or(a1, b1.citadel);
    // Bitboard a3 = Or(a2, b1.black);
    // Bitboard a4 = Not(a3);
    // printLikeBoard(b1.castle, WIDTH);
    // printLikeBoard(b1.citadel, WIDTH);
    // printLikeBoard(a1, WIDTH);
    // printLikeBoard(a2, WIDTH);
    // printLikeBoard(a3, WIDTH);
    // printLikeBoard(a4, WIDTH);

    // int colonna = 6;
    // int riga = 4;

    // Bitboard vuota;
    // vuota.bb[0] = 0;
    // vuota.bb[1] = 0;
    // vuota.bb[2] = 0;

    // Bitboard newBit;
    // newBit.bb[0] = 1 << INT_SIZE - 1;
    // newBit.bb[1] = 0;
    // newBit.bb[2] = 0;
    // //printLikeBoard(newBit, WIDTH);
    // newBit = Or(vuota, rightShift(newBit, colonna));
    // //printLikeBoard(newBit, WIDTH);
    // for (int i = 0; i < WIDTH; i++)
    // {
    //     newBit = Or(newBit, rightShift(newBit, WIDTH));
    // }
    // //printLikeBoard(newBit, WIDTH);

    // Bitboard newBit1;
    // newBit1.bb[0] = 1 << INT_SIZE - 1;
    // newBit1.bb[1] = 0;
    // newBit1.bb[2] = 0;

    // for (int i = 0; i < riga; i++)
    // {
    //     newBit1 = Or(vuota, rightShift(newBit1, WIDTH));
    // }
    // for (int i = 0; i < WIDTH - 1; i++)
    // {
    //     newBit1 = Or(newBit1, rightShift(newBit1, 1));
    // }
    // //printLikeBoard(newBit1, WIDTH);
    // Bitboard finale = Or(newBit1, newBit);
    // //printLikeBoard(finale, WIDTH);
    // printLikeBoard(And(finale, a4), WIDTH);
    node_t* moves = findPossibleMoves(b1, WHITE);
    Bitboard all = findAllForAll(b1, WHITE);
    Bitboard allOne = findAllForOne(all, 4, 3);
    printList(moves);
    printLikeBoard(all, WIDTH);
    printLikeBoard(allOne, WIDTH);
    // int couple[2];
    // int *moves = malloc(((WIDTH - 1) * 2) * sizeof(couple));

/*
    //mosse in alto
    for (int i = 4 - 1; i >= 0; i--)
    {
        int isValid = getCellState(allOne, i, 6);
        if (isValid)
            // int *move =
            printf("(%d, %d)\n", i, 6);
        else
            break;
    }

    //mosse in basso
    for (int i = 4 + 1; i < WIDTH; i++)
    {
        int isValid = getCellState(allOne, i, 6);
        if (isValid)
            printf("(%d, %d)\n", i, 6);
        else
            break;
    }

    //mosse a destra
    for (int j = 6 - 1; j >= 0; j--)
    {
        int isValid = getCellState(allOne, 4, j);
        if (isValid)
            printf("(%d, %d)\n", 4, j);
        else
            break;
    }

    //mosse a sinistra
    for (int j = 6 + 1; j < WIDTH; j++)
    {
        int isValid = getCellState(allOne, 4, j);
        if (isValid)
            printf("(%d, %d)\n", 4, j);
        else
            break;
    }
*/
}