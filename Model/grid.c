#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <SDL.h>
#include "model.h"
#include "grid.h"

Position* getNextPosition(Position* position, int direction)
{
    Position* nextPosition = malloc(sizeof(Position));
    nextPosition->x = position->x;
    nextPosition->y = position->y;

    switch (direction) {
        case SDLK_UP:
            nextPosition->y = position->y - 1;
            break;
        case SDLK_DOWN:
            nextPosition->y = position->y + 1;
            break;
        case SDLK_LEFT:
            nextPosition->x = position->x - 1;
            break;
        case SDLK_RIGHT:
            nextPosition->x = position->x + 1;
            break;
        default:
            break;
    }

    return nextPosition;
}

bool isWallAtPosition(Grid* grid, Position* position)
{
    for (int i = 0; i < grid->numberWalls; i++) {
        if (grid->walls[i]->x == position->x && grid->walls[i]->y == position->y) {
            return true;
        }
    }

    return false;
}

bool isBlockAtPosition(Grid* grid, Position* position)
{
    for (int i = 0; i < grid->numberBlocks; i++) {
        if (grid->blocks[i]->x == position->x && grid->blocks[i]->y == position->y) {
            return true;
        }
    }

    return false;
}

int getBlockIndiceAtPosition(Grid* grid, Position* position)
{
    for (int i = 0; i < grid->numberBlocks; i++) {
        if (grid->blocks[i]->x == position->x && grid->blocks[i]->y == position->y) {
            return i;
        }
    }
}

void setNumberPositions(
        char* filename,
        int* numberGrounds,
        int* numberWalls,
        int* numberStands,
        int* numberBlocks
        )
{
    FILE* file;
    file = fopen(filename, "r");
    if (NULL == file) {
        fprintf(stderr, "Impossible de lire le fichier de grille");
        exit(EXIT_FAILURE);
    }
    int currentCharacter = 0;
    int x = 0;
    int y = 0;

    while (EOF != currentCharacter) {
        currentCharacter = fgetc(file);
        if ('\n' == currentCharacter || EOF == currentCharacter) {
            y++;
            x = 0;
            continue;
        }

        switch (currentCharacter) {
            case '#': // wall
                (*numberWalls)++;
                break;
            case ' ': // ground
                (*numberGrounds)++;
                break;
            case '.': // stand on ground
                (*numberStands)++;
                (*numberGrounds)++;
                break;
            case '$': // block on ground
                (*numberBlocks)++;
                (*numberGrounds)++;
                break;
            case '@': // sokoban on ground
                (*numberGrounds)++;
                break;
            case '*': // block on stand on ground
                (*numberBlocks)++;
                (*numberStands)++;
                (*numberGrounds)++;
                break;
            case '+': // sokoban on stand on ground
                (*numberStands)++;
                (*numberGrounds)++;
                break;
            default:
                break;
        }
        x++;
    }
}

void grid_setPositions(
        char* filename,
        Grid* grid
        )
{
    FILE* file;
    file = fopen(filename, "r");

    int wallsIndice = 0;
    int groundsIndice = 0;
    int standsIndice = 0;
    int blocksIndice = 0;

    Position** walls = malloc(grid->numberWalls * sizeof(Position));
    Position** grounds = malloc(grid->numberGrounds * sizeof(Position));
    Position** stands = malloc(grid->numberStands * sizeof(Position));
    Position** blocks = malloc(grid->numberBlocks * sizeof(Position));
    Position** sokobans = malloc(sizeof(Position));

    int currentCharacter = 0;
    int x = 0;
    int y = 0;

    while (EOF != currentCharacter) {
        currentCharacter = fgetc(file);
        if ('\n' == currentCharacter || EOF == currentCharacter) {
            y++;
            x = 0;
            continue;
        }

        Position* position = malloc(sizeof(Position));
        position->x = x;
        position->y = y;

        switch (currentCharacter) {
            case '#': // wall
                walls[wallsIndice] = position;
                wallsIndice++;
                break;
            case ' ': // ground
                grounds[groundsIndice] = position;
                groundsIndice++;
                break;
            case '.': // stand on ground
                stands[standsIndice] = position;
                standsIndice++;
                grounds[groundsIndice] = position;
                groundsIndice++;
                break;
            case '$': // block on ground
                blocks[blocksIndice] = position;
                blocksIndice++;
                grounds[groundsIndice] = position;
                groundsIndice++;
                break;
            case '@': // sokoban on ground
                grounds[groundsIndice] = position;
                groundsIndice++;
                sokobans[0] = position;
                break;
            case '*': // block on stand on ground
                blocks[blocksIndice] = position;
                blocksIndice++;
                stands[standsIndice] = position;
                standsIndice++;
                grounds[groundsIndice] = position;
                groundsIndice++;
                break;
            case '+': // sokoban on stand on ground
                stands[standsIndice] = position;
                standsIndice++;
                grounds[groundsIndice] = position;
                groundsIndice++;
                sokobans[0] = position;
                break;
            default:
                break;
        }

        x++;
    }

    grid->walls = walls;
    grid->grounds = grounds;
    grid->stands = stands;
    grid->blocks = blocks;
    grid->sokobans = sokobans;
}

void displayInConsole(
        Grid* grid
)
{
    printf("Nombre de walls : %d.\n", grid->numberWalls);
    printf("Nombre de grounds : %d.\n", grid->numberGrounds);
    printf("Nombre de blocks : %d.\n", grid->numberBlocks);
    printf("Nombre de stands : %d.\n", grid->numberStands);
    printf("\n");

    printf("Stands : \n");
    for (int i = 0; i < grid->numberStands; i++) {
        printf("%d, %d\n", grid->stands[i]->x, grid->stands[i]->y);
    }
    printf("\n");

    printf("Blocks : \n");
    for (int i = 0; i < grid->numberBlocks; i++) {
        printf("%d, %d\n", grid->blocks[i]->x, grid->blocks[i]->y);
    }
    printf("\n");

    printf("Grounds : \n");
    for (int i = 0; i < grid->numberGrounds; i++) {
        printf("%d, %d\n", grid->grounds[i]->x, grid->grounds[i]->y);
    }
    printf("\n");

    printf("Walls : \n");
    for (int i = 0; i < grid->numberWalls; i++) {
        printf("%d, %d\n", grid->walls[i]->x, grid->walls[i]->y);
    }
    printf("\n");

    printf("Sokoban : \n");
    printf("%d, %d\n", grid->sokobans[0]->x, grid->sokobans[0]->y);
    printf("\n");
}

bool canMove(Grid* grid, int direction)
{
    Position* nextPosition = getNextPosition(grid->sokobans[0], direction);
    if (isWallAtPosition(grid, nextPosition)) {
        free(nextPosition);
        return false;
    }

    if (isBlockAtPosition(grid, nextPosition)) {
        Position* nextNextPosition = getNextPosition(nextPosition, direction);
        if (isWallAtPosition(grid, nextNextPosition)) {
            free(nextPosition);
            free(nextNextPosition);
            return false;
        }
        if (isBlockAtPosition(grid, nextNextPosition)) {
            free(nextPosition);
            free(nextNextPosition);
            return false;
        }
        free(nextPosition);
        free(nextNextPosition);
        return true;
    }
    free(nextPosition);
    return true;
}

Grid* grid_init(
        char* filename
        )
{
    int numberWalls = 0;
    int numberGrounds = 0;
    int numberStands = 0;
    int numberBlocks = 0;

    setNumberPositions(filename, &numberGrounds, &numberWalls, &numberStands, &numberBlocks);

    Grid* grid = malloc(
            numberWalls * sizeof(Position)
            + numberGrounds * sizeof(Position)
            + numberStands * sizeof(Position)
            + numberBlocks * sizeof(Position)
            + sizeof(Position)
            + 4 * sizeof(int)
    );

    grid->numberGrounds = numberGrounds;
    grid->numberWalls = numberWalls;
    grid->numberStands = numberStands;
    grid->numberBlocks = numberBlocks;

    grid_setPositions(filename, grid);

    // displayInConsole(grid);

    return grid;
}

void grid_free(Grid* grid)
{
    for (int i = 0; i < grid->numberWalls; i++) {
        free(grid->walls[i]);
    }
    for (int i = 0; i < grid->numberGrounds; i++) {
        free(grid->grounds[i]);
    }
    for (int i = 0; i < grid->numberStands; i++) {
        free(grid->stands[i]);
    }
    for (int i = 0; i < grid->numberBlocks; i++) {
        free(grid->blocks[i]);
    }
    free(grid->sokobans[0]);
    free(grid);
}

bool grid_move(Grid* grid, int direction)
{
    if (!canMove(grid, direction)) {
        return false;
    }

    Position* nextPosition = getNextPosition(grid->sokobans[0], direction);

    if (false == isBlockAtPosition(grid, nextPosition)) {
        grid->sokobans[0] = nextPosition;
        return true;
    }

    Position* nextNextPosition = getNextPosition(nextPosition, direction);
    int indiceBlock = getBlockIndiceAtPosition(grid, nextPosition);
    grid->blocks[indiceBlock] = nextNextPosition;
    grid->sokobans[0] = nextPosition;


    return true;
}