#include "ui.h"

void drawSortChooser(int w, int h) {
    Rectangle rec = {0, 0, ((int) w/4), ((int) h/5*3)};
    drawOutline(rec, 4, LIGHTGRAY);
}

void drawOptChooser(int w, int h) {
    Rectangle rec = {0, ((int) h/5*3), ((int) w/4), h};
    drawOutline(rec, 4, LIGHTGRAY);
}

void drawStartButton(int w, int h, int* toDraw) {
    int btnWidth = (int) w / 10; 
    int btnHeight = (int) h / 20;
    int btnX = w - btnWidth - 20;  
    int btnY = h - btnHeight - 20; 
    
    Rectangle btn = {btnX, btnY, btnWidth, btnHeight};

    bool isPressed = false;
    drawButton(btn, "start", LIGHTGRAY, &isPressed);
    if (isPressed) {
        *toDraw = 1;
    }
}


void drawChooseUI(int w, int h, int* toDraw) {
    drawSortChooser(w, h);
    drawOptChooser(w, h);
    drawStartButton(w, h, toDraw);
}

