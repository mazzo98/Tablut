#include "Bitboard.h"

/*
* prints out the binary string for the input integer
*/
void showBits(uint32_t x)
{
    int i = 0;
    for (i = INT_SIZE - 1; i >= 0; i--)
    {
        putchar(x & (1u << i) ? '1' : '0');
    }
    printf("\n");
}
/*
* prints out the bitboard as bynary values
*/
void printBitboard(Bitboard b)
{
    showBits(b.bb[0]);
    showBits(b.bb[1]);
    showBits(b.bb[2]);
    printf("\n");
}
/*
* pretty print for a bitboard as a square of binary values (9x9 + 15)
*/
void printLikeBoard(Bitboard b, int line)
{
    int j = 0;
    int count = 0;
    for (int x = 0; x < 3; x++)
    {
        int i = 0;
        for (i = INT_SIZE - 1; i >= 0; i--)
        {
            putchar(b.bb[x] & (1u << i) ? '1' : '0');
            printf(" ");
            j++;
            count++;
            if (j == line)
            {
                j = 0;
                printf("\n");
            }
            if (count == 81)
            {
                printf("\n");
            }
        }
    }
    printf("\n\n");
}
/*
* computes bitwise AND between two bitboards
*/
Bitboard And(Bitboard from1, Bitboard from2)
{
    Bitboard to;
    to.bb[0] = from1.bb[0] & from2.bb[0];
    to.bb[1] = from1.bb[1] & from2.bb[1];
    to.bb[2] = (from1.bb[2] & from2.bb[2]) & CORRECT_SHIFT;
    return to;
}
/*
* computes bitwise OR between two bitboards
*/
Bitboard Or(Bitboard from1, Bitboard from2)
{
    Bitboard to;
    to.bb[0] = from1.bb[0] | from2.bb[0];
    to.bb[1] = from1.bb[1] | from2.bb[1];
    to.bb[2] = (from1.bb[2] | from2.bb[2]) & CORRECT_SHIFT;
    return to;
}
/*
* computes bitwise XOR between two bitboards
*/
Bitboard Xor(Bitboard from1, Bitboard from2)
{
    Bitboard to;
    to.bb[0] = from1.bb[0] ^ from2.bb[0];
    to.bb[1] = from1.bb[1] ^ from2.bb[1];
    to.bb[2] = (from1.bb[2] ^ from2.bb[2]) & CORRECT_SHIFT;
    return to;
}
/*
* computes bitwise NOT between two bitboards
*/
Bitboard Not(Bitboard from)
{
    Bitboard to;
    to.bb[0] = ~(from.bb[0]);
    to.bb[1] = ~(from.bb[1]);
    to.bb[2] = (~(from.bb[2])) & CORRECT_SHIFT;
    return to;
}
/*
* computes a right shift on a bitboard.
* shift is for the bits to shift
*/
Bitboard rightShift(Bitboard from, int shift)
{
    Bitboard to;
    if(shift == 0){
        to = from;
    } 
    else if (shift < INT_SIZE)
    {
        int oppositeShift = INT_SIZE - shift;
        to.bb[0] = from.bb[0] >> shift;
        to.bb[1] = (from.bb[0] << oppositeShift) | (from.bb[1] >> shift);
        to.bb[2] = (from.bb[1] << oppositeShift) | (from.bb[2] >> shift);
    }
    else if (shift >= INT_SIZE && shift < 2 * INT_SIZE)
    {
        int otherShift = shift - INT_SIZE;
        int oppositeShift = INT_SIZE - otherShift;
        to.bb[0] = 0; //from.bb[0] >> shift; //to.bb[0] >> INT_SIZE//to.bb[0] = 0;
        to.bb[1] = from.bb[0] >> otherShift;
        to.bb[2] = shift == INT_SIZE ? from.bb[1] : (from.bb[0] << oppositeShift) | (from.bb[1] >> otherShift);
    }
    else if (shift >= 2 * INT_SIZE && shift < 3 * INT_SIZE)
    {
        int otherShift = shift - 2 * INT_SIZE;
        to.bb[0] = 0; //from.bb[0] >> shift; //to.bb[0] >> INT_SIZE //to.bb[0] = 0;
        to.bb[1] = 0; //from.bb[1] >> shift; //to.bb[1] >> INT_SIZE //to.bb[1] = 0;
        to.bb[2] = from.bb[0] >> otherShift;
    }
    else if (shift >= 3 * INT_SIZE)
    {
        printf("cases with shift over %ld not considered\n", 3 * INT_SIZE);
    }
    // need this because we consider just the first 81 bit out of 96
    // so we need to mask out the last 15 bits
    to.bb[2] = to.bb[2] & CORRECT_SHIFT;
    return to;
}
/*
* computes a left shift on a bitboard.
* shift is for the bits to shift
*/
Bitboard leftShift(Bitboard from, int shift)
{
    Bitboard to;
    // need this because we consider just the first 81 bit out of 96
    // so we need to mask out the last 15 bits
    from.bb[2] = from.bb[2] & CORRECT_SHIFT;
    if(shift == 0){
        to = from;
    } 
    else if (shift < INT_SIZE)
    {
        int oppositeShift = INT_SIZE - shift;
        to.bb[2] = from.bb[2] << shift;
        to.bb[1] = (from.bb[2] >> oppositeShift) | (from.bb[1] << shift);
        to.bb[0] = (from.bb[1] >> oppositeShift) | (from.bb[0] << shift);
    }
    else if (shift >= INT_SIZE && shift < 2 * INT_SIZE)
    {
        int otherShift = shift - INT_SIZE;
        int oppositeShift = INT_SIZE - otherShift;
        to.bb[2] = 0; //from.bb[2] << shift; //to.bb[2] << INT_SIZE//to.bb[2] = 0;
        to.bb[1] = from.bb[2] << otherShift;
        to.bb[0] = shift == INT_SIZE ? from.bb[1] : (from.bb[2] >> oppositeShift) | (from.bb[1] << otherShift);
    }
    else if (shift >= 2 * INT_SIZE && shift < 3 * INT_SIZE)
    {
        int otherShift = shift - 2 * INT_SIZE;
        to.bb[2] = 0; //from.bb[2] << shift; //to.bb[2] << INT_SIZE //to.bb[2] = 0;
        to.bb[1] = 0; //from.bb[1] << shift; //to.bb[1] << INT_SIZE //to.bb[1] = 0;
        to.bb[0] = from.bb[2] << otherShift;
    }
    else if (shift >= 3 * INT_SIZE)
    {
        printf("cases with shift over %ld not considered\n", 3 * INT_SIZE);
    }
    return to;
}
/*
* sets a bitboard given three int32
*/
Bitboard setBitboard(uint32_t first, uint32_t second, uint32_t third)
{
    Bitboard res;
    res.bb[0] = first;
    res.bb[1] = second;
    res.bb[2] = third;
    //printLikeBoard(res, WIDTH);
    return res;
}
/*
* sets a pawn to a given row,col position
*/
Bitboard setCellState(Bitboard from, int row, int col)
{
    return Or(from, rightShift(NEW_BIT, row * WIDTH + col));
}
/*
* gets the state of a given row,col position
*/
int getCellState(Bitboard from, int row, int col)
{
    Bitboard res = And(from, rightShift(MASK, row * WIDTH + col));

    return res.bb[0] != 0 || res.bb[1] != 0 || res.bb[2] != 0;
}
/*
* gets the number of bit set to 1 in a bitboard
*/
int countBitSet(Bitboard from)
{
    // need this because we consider just the first 81 bit out of 96
    // so we need to mask out the last 15 bits
    //from.bb[2] = from.bb[2] & ~CORRECT_SHIFT;
    int count = 0;
    for (int i = 0; i < 3; i++)
    {
        while (from.bb[i] != 0)
        {
            from.bb[i] = from.bb[i] & (from.bb[i] - 1);
            count++;
        }
    }
    return count;
}
/*
* if Bitboard is all zero than return 1
*/
int allZero(Bitboard from)
{
    return from.bb[0] == 0 && from.bb[1] == 0 && from.bb[2] == 0;
}