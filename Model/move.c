#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "model.h"
#include "move.h"

MoveStack* move_init()
{
    MoveStack* moveStack = malloc(sizeof(MoveStack));
    moveStack->firstMove = NULL;

    return moveStack;
}

void move_push(MoveStack* moveStack, int direction)
{
    Move* newMove = malloc(sizeof(Move));
    newMove->direction = direction;
    Move* firstMove = moveStack->firstMove;
    moveStack->firstMove = newMove;
    if (NULL == firstMove) {
        newMove->nextMove = NULL;
    } else {
        newMove->nextMove = firstMove;
    }
}