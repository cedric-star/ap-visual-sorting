#ifndef UI_H
#define UI_H

#include "raylib.h"
#include <stdbool.h>
#include <stdio.h>
#include "../core/core.h"

#define FSTCOLOR (Color){230, 230, 230, 255}
#define SNDCOLOR (Color){80, 80, 80, 255}
#define BGNCOLOR (Color){0, 0, 0, 255}

typedef struct {
    Rectangle box;
    char* text;
} Button;


void drawButton(Rectangle box, char* text, bool* isPressed);
void drawOutline(Rectangle box, int thickness, Color c);
void drawChooseUI(int w, int h, AppState* state);
void createDiagram(Rectangle box, List* list);
void drawInputField(Rectangle box, char* input, int* letterCount);



#endif