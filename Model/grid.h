#ifndef SOKOBAN_C_GRID_H
#define SOKOBAN_C_GRID_H

/**
    / : empty
      : ground
    # : wall
    . : stand
    $ : block
    @ : sokoban on ground
    * : block on stand on ground
    + : sokoban on stand on ground
*/

Grid* grid_init(
        char* filename
        );

void grid_free(Grid* grid);

bool grid_move(Grid* grid, int direction);

void grid_setPositions(char* filename, Grid* grid);

#endif //SOKOBAN_C_GRID_H
