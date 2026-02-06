#ifndef UI_H
#define UI_H

#include "raylib.h"
#include <stdbool.h>
#include <stdio.h>

typedef struct {
    int dynLength;
    int absLength;
    int *nums;
    int index;
    bool isFinished;
} List;

typedef struct {
    Rectangle box;
    char* text;
} Button;


void drawButton(Rectangle box, char* text, Color c);
void drawOutline(Rectangle box, int thickness, Color c);

void drawChooseUI(int w, int h);
//void drawChooseUI(int w, int h);


#endif