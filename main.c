#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Model/model.h"
#include "Model/grid.h"
#include "Model/move.h"
#include "View/view.h"
#include "Service/prompt.h"
#include "Service/game.h"

int main()
{

    char* filename = prompt_promptGrid();
    Grid* grid = grid_init(filename);

    MoveStack* moveStack = move_init();

    view_initSDL();
    View* view = view_initView();
    view_display(grid, view, moveStack);



    bool continu = true;
    while (continu) {
        SDL_Event event;
        SDL_WaitEvent(&event);
        switch (event.type) {
            case SDL_QUIT:
                continu = false;
                break;
            case SDL_KEYDOWN:
                game_move(grid, view, moveStack, event.key.keysym.sym);
                break;
            case SDL_MOUSEBUTTONUP:
                if (SDL_BUTTON_RIGHT == event.button.button) {
                    game_reset(grid, view, moveStack, filename);
                }
                if (SDL_BUTTON_LEFT == event.button.button) {
                    game_undo(grid, view, moveStack, filename);
                }
                break;
            default:
                break;
        }
    }


    move_free(moveStack);
    view_free(view);
    free(filename);
    grid_free(grid);

    return EXIT_SUCCESS;
}