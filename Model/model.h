#ifndef SOKOBAN_C_MODEL_H
#define SOKOBAN_C_MODEL_H

typedef struct Position Position;
struct Position
{
    int x;
    int y;
};

typedef struct Grid Grid;
struct Grid
{
    Position** grounds;
    Position** walls;
    Position** stands;
    Position** blocks;
    Position** sokobans;
    int numberGrounds;
    int numberWalls;
    int numberStands;
    int numberBlocks;
};

typedef struct Move Move;
struct Move
{
    int direction;
    Move* nextMove;
};

typedef struct MoveStack MoveStack;
struct MoveStack
{
    Move* firstMove;
};

#endif //SOKOBAN_C_MODEL_H
