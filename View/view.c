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

    return window;
}

void applyBackground(View* view)
{

    SDL_Rect backgroundPosition;
    backgroundPosition.x = 0;
    backgroundPosition.y = 0;
    SDL_BlitSurface(view->background, NULL, view->window, &backgroundPosition);
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
    free(view->background);

    TTF_Quit();
    SDL_Quit();
}

View* view_initView()
{
    View* view = malloc(7 * sizeof(SDL_Surface));

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

    SDL_Surface* background;
    background = IMG_Load("Assets/images/sky.jpeg");
    view->background = background;

    return view;
}

void view_display(Grid* grid, View* view, MoveStack* moveStack)
{
    SDL_FillRect(view->window, NULL, SDL_MapRGB(view->window->format, 255, 255, 255));

    applyBackground(view);

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

    for (int i = 0; i < grid->numberStands; i++) {
        SDL_Rect position;
        position.x = (Sint16)(grid->stands[i]->x * 60);
        position.y = (Sint16)(grid->stands[i]->y * 60);
        SDL_BlitSurface(view->stand, NULL, view->window, &position);
    }

    for (int i = 0; i < grid->numberBlocks; i++) {
        SDL_Rect position;
        position.x = (Sint16)(grid->blocks[i]->x * 60);
        position.y = (Sint16)(grid->blocks[i]->y * 60);
        SDL_BlitSurface(view->block, NULL, view->window, &position);
    }

    SDL_Rect position;
    position.x = (Sint16)(grid->sokobans[0]->x * 60);
    position.y = (Sint16)(grid->sokobans[0]->y * 60);
    SDL_BlitSurface(view->sokoban, NULL, view->window, &position);

    view_displayNumberMoves(moveStack, view);

    SDL_Flip(view->window);
}

void view_displayNumberMoves(MoveStack* moveStack, View* view)
{
    SDL_Color textColor = {255, 255, 255};

    TTF_Font* font = NULL;
    font = TTF_OpenFont("Assets/fonts/angelina.ttf", 40);
    SDL_Surface* textMovesSurface;

    char sentence[100];
    sprintf(sentence, "Coups : %d", moveStack->numberMoves);
    textMovesSurface = TTF_RenderText_Blended(font, sentence, textColor);

    SDL_Rect textPosition;
    textPosition.x = (Sint16)(view->window->w - textMovesSurface->w - 20);
    textPosition.y = 20;
    SDL_BlitSurface(textMovesSurface, NULL, view->window, &textPosition);
}