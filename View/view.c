#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "view.h"
#include "../Model/model.h"

SDL_Surface* createWindow()
{
    SDL_Surface* window;
    window = SDL_SetVideoMode(800, 600, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
    SDL_WM_SetCaption("Sokoban", NULL);
    SDL_Surface* background;
    background = IMG_Load("Assets/images/sky.jpeg");
    SDL_Rect backgroundPosition;
    backgroundPosition.x = 0;
    backgroundPosition.y = 0;
    SDL_BlitSurface(background, NULL, window, &backgroundPosition);

    return window;
}

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

void view_free(View* view)
{
    free(view->window);
    free(view->wall);
    free(view->ground);
    free(view->block);
    free(view->stand);
    free(view->sokoban);

    TTF_Quit();
    SDL_Quit();
}

View* view_initView()
{
    View* view = malloc(6 * sizeof(SDL_Surface));

    SDL_Surface* window = createWindow();
    view->window = window;

    SDL_Surface* wall;
    wall = IMG_Load("Assets/images/wall.png");
    view->wall = wall;

    SDL_Surface* ground;
    ground = IMG_Load("Assets/images/ground.png");
    view->ground = ground;

    SDL_Surface* stand;
    stand = IMG_Load("Assets/images/stand.png");
    view->stand = stand;

    SDL_Surface* block;
    block = IMG_Load("Assets/images/block.png");
    view->block = block;

    SDL_Surface* sokoban;
    sokoban = IMG_Load("Assets/images/sokoban.png");
    view->sokoban = sokoban;

    return view;
}

void view_display(Grid* grid, View* view)
{
    for (int i = 0; i < grid->numberWalls; i++) {
        SDL_Rect position;
        position.x = (Sint16)(grid->walls[i]->x * 60);
        position.y = (Sint16)(grid->walls[i]->y * 60);
        SDL_BlitSurface(view->wall, NULL, view->window, &position);
    }

    for (int i = 0; i < grid->numberGrounds; i++) {
        SDL_Rect position;
        position.x = (Sint16)(grid->grounds[i]->x * 60);
        position.y = (Sint16)(grid->grounds[i]->y * 60);
        SDL_BlitSurface(view->ground, NULL, view->window, &position);
    }

    for (int i = 0; i < grid->numberBlocks; i++) {
        SDL_Rect position;
        position.x = (Sint16)(grid->blocks[i]->x * 60);
        position.y = (Sint16)(grid->blocks[i]->y * 60);
        SDL_BlitSurface(view->block, NULL, view->window, &position);
    }

    for (int i = 0; i < grid->numberStands; i++) {
        SDL_Rect position;
        position.x = (Sint16)(grid->stands[i]->x * 60);
        position.y = (Sint16)(grid->stands[i]->y * 60);
        SDL_BlitSurface(view->stand, NULL, view->window, &position);
    }

    SDL_Rect position;
    position.x = (Sint16)(grid->sokobans[0]->x * 60);
    position.y = (Sint16)(grid->sokobans[0]->y * 60);
    SDL_BlitSurface(view->sokoban, NULL, view->window, &position);

    SDL_Flip(view->window);
}