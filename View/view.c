#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "view.h"

void view_initSDL()
{
    if (-1 == SDL_Init(SDL_INIT_VIDEO)) {
        fprintf(stderr, "Erreur : %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    if (-1 == TTF_Init()) {
        fprintf(stderr, "Erreur : %s\n", TTF_GetError());
        exit(EXIT_FAILURE);
    }
}

void view_quitSDL()
{
    TTF_Quit();
    SDL_Quit();
}