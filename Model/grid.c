#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "model.h"
#include "grid.h"

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

void setPositions(
        char* filename,
        Position** walls,
        Position** grounds,
        Position** stands,
        Position** blocks,
        Position** sokobans
        )
{
    FILE* file;
    file = fopen(filename, "r");

    int wallsIndice = 0;
    int groundsIndice = 0;
    int standsIndice = 0;
    int blocksIndice = 0;


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
}

void displayInConsole(
        Grid* grid,
        int numberWalls,
        int numberGrounds,
        int numberStands,
        int numberBlocks
)
{
    printf("Calcul des nombres à partir du fichier : \n");
    printf("Nombre de walls : %d.\n", numberWalls);
    printf("Nombre de grounds : %d.\n", numberGrounds);
    printf("Nombre de blocks : %d.\n", numberBlocks);
    printf("Nombre de stands : %d.\n", numberStands);
    printf("\n");

    printf("Stands : \n");
    for (int i = 0; i < numberStands; i++) {
        printf("%d, %d\n", grid->stands[i]->x, grid->stands[i]->y);
    }
    printf("\n");

    printf("Blocks : \n");
    for (int i = 0; i < numberBlocks; i++) {
        printf("%d, %d\n", grid->blocks[i]->x, grid->blocks[i]->y);
    }
    printf("\n");

    printf("Grounds : \n");
    for (int i = 0; i < numberGrounds; i++) {
        printf("%d, %d\n", grid->grounds[i]->x, grid->grounds[i]->y);
    }
    printf("\n");

    printf("Walls : \n");
    for (int i = 0; i < numberWalls; i++) {
        printf("%d, %d\n", grid->walls[i]->x, grid->walls[i]->y);
    }
    printf("\n");

    printf("Sokoban : \n");
    printf("%d, %d\n", grid->sokobans[0]->x, grid->sokobans[0]->y);
    printf("\n");
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

    Position** walls = malloc(numberWalls * sizeof(Position));
    Position** grounds = malloc(numberGrounds * sizeof(Position));
    Position** stands = malloc(numberStands * sizeof(Position));
    Position** blocks = malloc(numberBlocks * sizeof(Position));
    Position** sokobans = malloc(sizeof(Position));

    setPositions(filename, walls, grounds, stands, blocks, sokobans);

    Grid* grid = malloc(
            numberWalls * sizeof(Position)
            + numberGrounds * sizeof(Position)
            + numberStands * sizeof(Position)
            + numberBlocks * sizeof(Position)
            + sizeof(Position)
            );

    grid->walls = walls;
    grid->grounds = grounds;
    grid->stands = stands;
    grid->blocks = blocks;
    grid->sokobans = sokobans;

    // displayInConsole(grid, numberWalls, numberGrounds, numberStands, numberBlocks);

    return grid;
}

