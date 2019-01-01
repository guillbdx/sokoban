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

void grid_init(
        char* filename
        );

#endif //SOKOBAN_C_GRID_H
