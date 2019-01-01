#ifndef SOKOBAN_C_GAME_H
#define SOKOBAN_C_GAME_H

#include "../Model/model.h"
#include "../View/view.h"

void game_move(Grid* grid, View* view, MoveStack* moveStack, int direction);

#endif //SOKOBAN_C_GAME_H
