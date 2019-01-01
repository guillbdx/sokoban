#ifndef SOKOBAN_C_VIEW_H
#define SOKOBAN_C_VIEW_H

#include <SDL.h>
#include <SDL_image.h>
#include "../Model/model.h"

typedef struct View View;
struct View
{
    SDL_Surface* window;
    SDL_Surface* wall;
    SDL_Surface* ground;
    SDL_Surface* stand;
    SDL_Surface* block;
    SDL_Surface* sokoban;
};

void view_initSDL();

void view_quitSDL();

View* view_initView();

#endif //SOKOBAN_C_VIEW_H
