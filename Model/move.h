#ifndef SOKOBAN_C_MOVE_H
#define SOKOBAN_C_MOVE_H

MoveStack* move_init();

void move_push(MoveStack* moveStack, int direction);

#endif //SOKOBAN_C_MOVE_H
