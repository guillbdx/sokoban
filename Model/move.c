#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "model.h"
#include "move.h"

Move** getOrderedMoves(MoveStack* moveStack)
{
    Move** orderedMoves = malloc(moveStack->numberMoves * sizeof(Move));
    int indice = moveStack->numberMoves - 1;
    Move* currentMove = moveStack->firstMove;
    while (NULL != currentMove) {
        orderedMoves[indice] = currentMove;
        indice--;
        currentMove = currentMove->nextMove;
    }

    return orderedMoves;
}

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
    moveStack->numberMoves = 0;
    moveStack->firstMove = NULL;
}

void move_free(MoveStack* moveStack)
{
    move_reset(moveStack);
    free(moveStack);
}



void move_displayInConsole(MoveStack* moveStack)
{
    Move** moves = getOrderedMoves(moveStack);
    for (int i = 0; i < moveStack->numberMoves; i++) {
        printf("%d\n", moves[i]->direction);
    }
    printf(" \n");
}