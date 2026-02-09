#ifndef UI_H
#define UI_H

#include "raylib.h"
#include <stdbool.h>
#include <stdio.h>
#include "../core/core.h"

typedef struct {
    Rectangle box;
    char* text;
} Button;


void drawButton(Rectangle box, char* text, Color c, bool* isPressed);
void drawOutline(Rectangle box, int thickness, Color c);
void drawChooseUI(int w, int h, int* toDraw);
void createDiagram(Rectangle box, List* list);
void drawInputField(Rectangle box, char* input, int* letterCount, Color c);



#endif