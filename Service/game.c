#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "game.h"
#include "../Model/model.h"
#include "../Model/grid.h"
#include "../View/view.h"

void game_move(Grid* grid, View* view, int direction)
{
    grid_move(grid, direction);
    view_display(grid, view);
}