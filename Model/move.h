#ifndef SOKOBAN_C_MOVE_H
#define SOKOBAN_C_MOVE_H

MoveStack* move_init();

void move_push(MoveStack* moveStack, int direction);

void move_pop(MoveStack* moveStack);

void move_reset(MoveStack* moveStack);

void move_free(MoveStack* moveStack);

void move_displayInConsole(MoveStack* moveStack);

Move** move_getOrderedMoves(MoveStack* moveStack);

#endif //SOKOBAN_C_MOVE_H
