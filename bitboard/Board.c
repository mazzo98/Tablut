#include "Board.h"

/*
* if king is on escape tile then you win (1:win)
*/
int winning_condition(Bitboard kingB)
{
    Bitboard res = And(kingB, ESCAPE);
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
/*
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
*/
/*
* find all legal possible moves for all pawns? di sicuro per i bianchi
*/
Bitboard findAllForAll(Board from, uint8_t player)
{
    if (player == WHITE)
        return Not(Or(Or(Or(from.white, CASTLE), CITADEL), from.black));
    else if (player == BLACK)
        return Not(Or(Or(Or(from.black, CASTLE), CITADEL), from.black));
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

node_t* findPossibleMoves(Board from, uint8_t player)
{
    node_t* moves = NULL;
    node_t* tmp;
    Bitboard all = findAllForAll(from, player);
    Bitboard p, allOne;
    if(player == WHITE){
        p = from.white;
    } else if(player == BLACK){
        p = from.black;
    }

    for(uint8_t i=0; i < WIDTH; i++){
        for(uint8_t y=0; y < WIDTH; y++){
            if(getCellState(p, i, y)){
                allOne = findAllForOne(all, i, y);
                tmp = findMovesForOne(allOne, i, y);
                appendList(&moves, &tmp);
            }
        }
    }

    return moves;
}

node_t* findMovesForOne(Bitboard allOne, uint8_t row, uint8_t col){
    node_t* moves = NULL;
    //mosse in alto
    for (int i = row - 1; i >= 0; i--)
    {
        int isValid = getCellState(allOne, i, col);
        if (isValid){
            // int *move =
            //printf("(%d, %d)\n", i, 6);
            Move move = { .start.row = row, .start.col = col, 
                            .end.row = i, .end.col = col };
            append(&moves, move);
        } else{
            break;
        }
    }

    //mosse in basso
    for (int i = row + 1; i < WIDTH; i++)
    {
        int isValid = getCellState(allOne, i, col);
        if (isValid){
            //printf("(%d, %d)\n", i, 6);
            Move move = { .start.row = row, .start.col = col, 
                            .end.row = i, .end.col = col };
            append(&moves, move);
        } else{
            break;
        }
    }

    //mosse a destra
    for (int j = col - 1; j >= 0; j--)
    {
        int isValid = getCellState(allOne, row, j);
        if (isValid){
            //printf("(%d, %d)\n", 4, j);
            Move move = { .start.row = row, .start.col = col, 
                            .end.row = row, .end.col = j };
            append(&moves, move);
        } else{
            break;
        }
    }

    //mosse a sinistra
    for (int j = col + 1; j < WIDTH; j++)
    {
        int isValid = getCellState(allOne, row, j);
        if (isValid){
            //printf("(%d, %d)\n", 4, j);
            Move move = { .start.row = row, .start.col = col, 
                            .end.row = row, .end.col = j };
            append(&moves, move);
        } else{
            break;
        }
    }

    return moves;
}