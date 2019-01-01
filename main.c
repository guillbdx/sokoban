#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Model/model.h"
#include "Model/grid.h"
#include "View/view.h"
#include "Service/prompt.h"

void pause()
{

    int continuer = 1;

    SDL_Event event;



    while (continuer)

    {

        SDL_WaitEvent(&event);

        switch(event.type)

        {

            case SDL_QUIT:

                continuer = 0;

        }

    }

}

int main(int argc, char *argv[])
{

    char* filename = prompt_promptGrid();
    Grid* grid = grid_init(filename);


    view_initSDL();
    View* view = view_initView();
    view_display(grid, view);



    pause();


    view_free(view);
    free(filename);
    grid_free(grid);

    return EXIT_SUCCESS;
}