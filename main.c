#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Model/model.h"
#include "Model/grid.h"
#include "View/view.h"
#include "Service/prompt.h"

int main(int argc, char *argv[])
{

    char* filename = prompt_promptGrid();
    Grid* grid = grid_init(filename);


    view_initSDL();


    view_quitSDL();
    free(filename);
    grid_free(grid);



    return EXIT_SUCCESS;
}