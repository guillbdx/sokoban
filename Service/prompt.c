#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "prompt.h"

#define MAX_STRING_MAX 100

void prompt_emptyBuffer()
{
    int character = 0;
    while (character != '\n' && character != EOF) {
        character = getchar();
    }
}

void prompt_replaceEntry(char* sentence)
{
    char* pointerOnEntry = strchr(sentence, '\n');

    if (NULL != pointerOnEntry) {
        *pointerOnEntry = '\0';
    } else {
        prompt_emptyBuffer();
    }
}

int prompt_promptString(char* sentence)
{
    if (NULL == fgets(sentence, MAX_STRING_MAX, stdin)) {
        prompt_emptyBuffer();
        return false;
    }

    prompt_replaceEntry(sentence);

    return true;
}

int prompt_promptInt()
{
    char sentence[MAX_STRING_MAX];
    prompt_promptString(sentence);

    return (int)strtol(sentence, NULL, 10);
}

double prompt_promptDouble()
{
    char sentence[MAX_STRING_MAX];
    prompt_promptString(sentence);

    return strtod(sentence, NULL);
}

void prompt_promptGrid()
{

}