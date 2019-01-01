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
    moveStack->numberMoves++;
}

void move_reset(MoveStack* moveStack)
{
    Move** moves = malloc(moveStack->numberMoves * sizeof(Move));

    Move* currentMove = moveStack->firstMove;
    int indice = 0;
    while (NULL != currentMove) {
        moves[indice] = currentMove;
        currentMove = currentMove->nextMove;
    }

    for (int i = 0; i < moveStack->numberMoves; i++) {
        free(moves[i]);
    }

    moveStack->numberMoves = 0;
    moveStack->firstMove = NULL;
}

void move_free(MoveStack* moveStack)
{
    move_reset(moveStack);
    free(moveStack);
}