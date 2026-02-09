#include "ui.h"
//DrawText(text, box.x+6, box.y+2, box.height-2, c);
void drawSortChooser(int w, int h) {
    DrawText("choose sorting\nalgorithm", 8, 0, w/40, LIGHTGRAY);

    Rectangle rec = {0, 0, ((int) w/4), ((int) h/5*3)};
    drawOutline(rec, 4, LIGHTGRAY);
}

void drawOptChooser(int w, int h) {
    DrawText("choose list\nparameter", 8, (int) h/5*3, w/40, LIGHTGRAY);

    Rectangle rec = {0, ((int) h/5*3) - 4, ((int) w/4), h/5*2 + 4};
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

void drawTextInput(Rectangle rec) {

    char input[11] = "";
    int letC = 0;
    
    drawInputField(rec, input, &letC, LIGHTGRAY);

}

void drawChooseUI(int w, int h, int* toDraw) {
    drawSortChooser(w, h);
    drawOptChooser(w, h);
    drawStartButton(w, h, toDraw);

    Rectangle test = {350, 100, 300, 70};
    drawTextInput(test);
}



