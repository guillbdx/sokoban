#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "game.h"
#include "../Model/model.h"
#include "../Model/move.h"
#include "../Model/grid.h"
#include "../View/view.h"

void game_move(Grid* grid, View* view, MoveStack* moveStack, int direction)
{
    bool hasMoved = grid_move(grid, direction);

    if (false == hasMoved) {
        return;
    }
    move_push(moveStack, direction);
    view_display(grid, view);
}

void game_reset(Grid* grid, View* view, MoveStack* moveStack, char* filename)
{
    grid_setPositions(filename, grid);
    view_display(grid, view);
    move_reset(moveStack);
}

void game_undo(Grid* grid, View* view, MoveStack* moveStack, char* filename)
{
    grid_setPositions(filename, grid);
    view_display(grid, view);
    move_pop(moveStack);
    Move** orderedMoves = move_getOrderedMoves(moveStack);
    for (int i = 0; i < moveStack->numberMoves; i++) {
        grid_move(grid, orderedMoves[i]->direction);
    }
    view_display(grid, view);
}