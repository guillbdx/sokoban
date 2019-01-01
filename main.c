#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Model/model.h"
#include "Model/grid.h"
#include "View/view.h"
#include "Service/prompt.h"

int main()
{

    char* filename = prompt_promptGrid();

    Grid* grid = grid_init(filename);



    free(filename);
    grid_free(grid);

    return EXIT_SUCCESS;
}