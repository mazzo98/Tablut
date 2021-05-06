#include "Bitboard.h"
#include "List.h"
// This function prints contents of linked list starting from
// the given node
void printList(node_t *n)
{
    while (n != NULL)
    {
        printLikeBoard(n->black, WIDTH);
        printLikeBoard(n->white, WIDTH);
        printLikeBoard(n->king, WIDTH);
        n = n->next;
    }
}

/* Given a reference (pointer to pointer) to the head of a list
   and an int,  inserts a new node on the front of the list. */
void push(node_t **head_ref, Bitboard black, Bitboard white, Bitboard king)
{
    /* 1. allocate node */
    node_t *new_node = (node_t *)malloc(sizeof(node_t));

    /* 2. put in the data  */
    new_node->black = black;
    new_node->white = white;
    new_node->king = king;

    /* 3. Make next of new node as head */
    new_node->next = (*head_ref);

    /* 4. move the head to point to the new node */
    (*head_ref) = new_node;
}

/* Given a node prev_node, insert a new node after the given 
prev_node */
void insertAfter(node_t *prev_node, Bitboard black, Bitboard white, Bitboard king)
{
    /*1. check if the given prev_node is NULL */
    if (prev_node == NULL)
    {
        printf("the given previous node cannot be NULL");
        return;
    }

    /* 2. allocate new node */
    node_t *new_node = (node_t *)malloc(sizeof(node_t));

    /* 3. put in the data */
    new_node->black = black;
    new_node->white = white;
    new_node->king = king;

    /* 4. Make next of new node as next of prev_node */
    new_node->next = prev_node->next;

    /* 5. move the next of prev_node as new_node */
    prev_node->next = new_node;
}

/* Given a reference (pointer to pointer) to the head
   of a list and an int, appends a new node at the end  */
void append(node_t **head_ref, Bitboard black, Bitboard white, Bitboard king)
{
    /* 1. allocate node */
    node_t *new_node = (node_t *)malloc(sizeof(node_t));

    node_t *last = *head_ref; /* used in step 5*/

    /* 2. put in the data  */
    new_node->black = black;
    new_node->white = white;
    new_node->king = king;

    /* 3. This new node is going to be the last node, so make next 
          of it as NULL*/
    new_node->next = NULL;

    /* 4. If the Linked List is empty, then make the new node as head */
    if (*head_ref == NULL)
    {
        *head_ref = new_node;
        return;
    }

    /* 5. Else traverse till the last node */
    while (last->next != NULL)
        last = last->next;

    /* 6. Change the next of last node */
    last->next = new_node;
    return;
}