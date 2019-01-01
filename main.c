#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Model/model.h"
#include "Service/prompt.h"

int main()
{

    char* filename = prompt_promptGrid();

    printf("%s", filename);




    free(filename);

    return EXIT_SUCCESS;
}