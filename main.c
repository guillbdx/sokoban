#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Model/model.h"
#include "Model/grid.h"
#include "Service/prompt.h"

int main()
{

    char* filename = prompt_promptGrid();

    grid_init(filename);



    free(filename);

    return EXIT_SUCCESS;
}