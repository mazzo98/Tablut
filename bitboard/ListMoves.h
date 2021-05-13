#ifndef LIST_MOVES_H
#define LIST_MOVES_H

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

typedef struct
{
    uint8_t row;
    uint8_t col;
} Position;

typedef struct
{
    Position start;
    Position end;
} Move;

typedef struct node
{
    Move move;
    struct node *next;
} node_t;

void printList(node_t *n);

void push(node_t **head_ref, Move move);

void insertAfter(node_t *prev_node, Move move);

void append(node_t **head_ref, Move move);

void appendList(node_t **head_ref, node_t **tail);

void sizeList(node_t* moves, int* size);

#endif