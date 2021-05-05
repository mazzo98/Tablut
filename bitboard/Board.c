#include "Bitboard.h"
#include "Board.h"

/*
* if king is on escape tile then you win (1:win)
*/
int winning_condition(Bitboard kingB, Bitboard escapeB)
{
    Bitboard res = And(kingB, escapeB);
    //printLikeBoard(res, WIDTH);
    return !(res.bb[0] == 0 && res.bb[1] == 0 && res.bb[2] == 0);
}
/*
* if there's no king you lose (1:lose) 
*/
int lose_condition(Bitboard kingB)
{
    return kingB.bb[0] == 0 && kingB.bb[1] == 0 && kingB.bb[2] == 0;
}