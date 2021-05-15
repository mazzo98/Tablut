#include "Board.h"

int size;
Move *moves_array;
node_t *moves_list;

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
    return Not(Or(Or(Or(Or(from.white, CASTLE), CITADEL), from.black), from.king));
}
/*
* find all legal possible moves for one pawn vertically 
*/
Bitboard findColForOne(Bitboard from, int col)
{
    Bitboard res;

    res = Or(EMPTY, rightShift(NEW_BIT, col));
    for (int i = 0; i < WIDTH; i++)
    {
        res = Or(res, rightShift(res, WIDTH));
    }
    return res;
}
/*
* find all legal possible moves for one pawn horizontally 
*/
Bitboard findRowForOne(Bitboard from, int row)
{
    Bitboard res;

    //for (int i = 0; i < row; i++)
    //{
    res = Or(EMPTY, rightShift(NEW_BIT, WIDTH * row));
    //}
    for (int i = 0; i < WIDTH - 1; i++)
    {
        res = Or(res, rightShift(res, 1));
    }
    return res;
}
/*
* find all legal possible moves for one pawn hortogonally 
*/
Bitboard findAllForOne(Bitboard from, int row, int col)
{
    Bitboard final = Or(findColForOne(from, col), findRowForOne(from, row));
    return And(from, final);
}

/*
* Given a board and a player it returns an array of all possible moves
*/
Move *findPossibleMoves(Board from, uint8_t player)
{
    moves_list = NULL;
    node_t *tmp = NULL;
    Bitboard all = findAllForAll(from, player);
    Bitboard p, allOne, all_black;

    p = player == WHITE ? Or(from.white, from.king) : from.black;

    for (uint8_t i = 0; i < WIDTH; i++)
    {
        for (uint8_t y = 0; y < WIDTH; y++)
        {
            if (getCellState(p, i, y))
            {
                if (player == BLACK)
                {
                    all_black = all;
                    if (getCellState(BIT_CITADEL_UP, i, y))
                        all_black = Or(all, And(Xor(BIT_CITADEL_UP, from.black), BIT_CITADEL_UP));
                    else if (getCellState(BIT_CITADEL_DOWN, i, y))
                        all_black = Or(all, And(Xor(BIT_CITADEL_DOWN, from.black), BIT_CITADEL_DOWN));
                    else if (getCellState(BIT_CITADEL_LEFT, i, y))
                        all_black = Or(all, And(Xor(BIT_CITADEL_LEFT, from.black), BIT_CITADEL_LEFT));
                    else if (getCellState(BIT_CITADEL_RIGHT, i, y))
                        all_black = Or(all, And(Xor(BIT_CITADEL_RIGHT, from.black), BIT_CITADEL_RIGHT));

                    allOne = findAllForOne(all_black, i, y);
                }
                else
                {
                    allOne = findAllForOne(all, i, y);
                }

                tmp = findMovesForOne(allOne, i, y);
                appendList(&moves_list, &tmp);
            }
        }
    }

    sizeList(moves_list, &size);
    moves_array = malloc(sizeof(Move) * size);
    for (uint8_t i = 0; i < size; i++)
    {
        moves_array[i] = moves_list->move;
        moves_list = moves_list->next;
    }

    return moves_array;
}

/*
* Given a bitboard it returns a list of all possible moves for the specified pawn
*/
node_t *findMovesForOne(Bitboard allOne, uint8_t row, uint8_t col)
{
    node_t *moves = NULL;
    Move move = {.start.row = row, .start.col = col};

    //Up
    for (int i = row - 1; i >= 0; i--)
    {
        if (getCellState(allOne, i, col))
        {
            move.end.row = i;
            move.end.col = col;
            append(&moves, move);
        }
        else
        {
            break;
        }
    }

    //Down
    for (int i = row + 1; i < WIDTH; i++)
    {
        if (getCellState(allOne, i, col))
        {
            move.end.row = i;
            move.end.col = col;
            append(&moves, move);
        }
        else
        {
            break;
        }
    }

    //Right
    for (int j = col - 1; j >= 0; j--)
    {
        if (getCellState(allOne, row, j))
        {
            move.end.row = row;
            move.end.col = j;
            append(&moves, move);
        }
        else
        {
            break;
        }
    }

    //Left
    for (int j = col + 1; j < WIDTH; j++)
    {
        if (getCellState(allOne, row, j))
        {
            move.end.row = row;
            move.end.col = j;
            append(&moves, move);
        }
        else
        {
            break;
        }
    }

    return moves;
}

/*
* Return size of list
*/
int getSize()
{
    return size;
}

void freeMemory()
{
    node_t *tmp;
    free(moves_array);
    while (moves_list != NULL)
    {
        tmp = moves_list;
        moves_list = moves_list->next;
        free(tmp);
    }
}