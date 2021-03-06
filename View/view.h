#ifndef SOKOBAN_C_VIEW_H
#define SOKOBAN_C_VIEW_H

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
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
    SDL_Surface* background;
    TTF_Font* font;
};

void view_initSDL();

void view_free(View* view);

View* view_initView();

void view_display(Grid* grid, View* view, MoveStack* moveStack);

void view_displayNumberMoves(MoveStack* moveStack, View* view);

#endif //SOKOBAN_C_VIEW_H
