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