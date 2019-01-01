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