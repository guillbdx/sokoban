#ifndef SOKOBAN_C_VIEW_H
#define SOKOBAN_C_VIEW_H

#include <SDL.h>
#include <SDL_image.h>

typedef struct View View;
struct View
{
    SDL_Surface* window;
};

void view_initSDL();

void view_quitSDL();

#endif //SOKOBAN_C_VIEW_H
