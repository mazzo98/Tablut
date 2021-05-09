#include "Bitboard.h"
#include "List.h"
#include "Board.h"

/*
* if king is on escape tile then you win (1:win)
*/
int winning_condition(Bitboard kingB, Bitboard escapeB)
{
    Bitboard res = And(kingB, escapeB);
    //printLikeBoard(res, WIDTH);
    return !allZero(res);
}
/*
* if there's no king you lose (1:lose) 
*/
int lose_condition(Bitboard kingB)
{
    return allZero(kingB);
}
/*
* if the current state is present in the list then it's a draw (return 1)
*/
int draw_condition(node_t *n, Bitboard black, Bitboard white, Bitboard king)
{
    while (n != NULL)
    {
        if (allZero(Xor(black, n->black)) && allZero(Xor(white, n->white)) && allZero(Xor(king, n->king)))
            return 1;
        else
            n = n->next;
    }
    return 0;
}
/*
* find all legal possible moves for all pawns? di sicuro per i bianchi
*/
Bitboard findAllForAll(Board from)
{
    return Not(Or(Or(Or(from.white, from.castle), from.citadel), from.black));
}
/*
* find all legal possible moves for one pawn vertically 
*/
Bitboard findColForOne(Bitboard from, int col)
{
    Bitboard empty;
    empty.bb[0] = 0;
    empty.bb[1] = 0;
    empty.bb[2] = 0;

    Bitboard newBit;
    newBit.bb[0] = 1 << INT_SIZE - 1;
    newBit.bb[1] = 0;
    newBit.bb[2] = 0;
    newBit = Or(empty, rightShift(newBit, col));
    for (int i = 0; i < WIDTH; i++)
    {
        newBit = Or(newBit, rightShift(newBit, WIDTH));
    }
    return newBit;
}
/*
* find all legal possible moves for one pawn horizontally 
*/
Bitboard findRowForOne(Bitboard from, int row)
{
    Bitboard empty;
    empty.bb[0] = 0;
    empty.bb[1] = 0;
    empty.bb[2] = 0;

    Bitboard newBit;
    newBit.bb[0] = 1 << INT_SIZE - 1;
    newBit.bb[1] = 0;
    newBit.bb[2] = 0;

    for (int i = 0; i < row; i++)
    {
        newBit = Or(empty, rightShift(newBit, WIDTH));
    }
    for (int i = 0; i < WIDTH - 1; i++)
    {
        newBit = Or(newBit, rightShift(newBit, 1));
    }
    return newBit;
}
/*
* find all legal possible moves for one pawn hortogonally 
*/
Bitboard findAllForOne(Bitboard from, int row, int col)
{
    Bitboard final = Or(findColForOne(from, col), findRowForOne(from, row));
    return And(from, final);
}