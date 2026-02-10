#include "ui.h"


//DrawText(text, box.x+6, box.y+2, box.height-2, c);
void drawSortChooser(int w, int h) {
    DrawText("choose sorting\nalgorithm", 8, 0, w/40, FSTCOLOR);

    Rectangle rec = {0, 0, ((int) w/4), ((int) h/5*3)};
    drawOutline(rec, 4, FSTCOLOR);
}


void drawTextInput(Rectangle rec, AppState* state) {
    
    
    drawInputField(rec, state->numMaxInput, &state->letCount);
}

#define calcRowY(row, rowNum, rec) (rec.y+(rec.height/rowNum*row))
void drawOptChooser(int w, int h, AppState* state) {
    Rectangle options = {0, h/5*3 - 4, w/4, h/5*2 + 4};
    int spaceRight = 8;
    int rows = 6;
    int fontSize = w/50;

    DrawText("choose parameter", spaceRight, calcRowY(0, rows, options), fontSize, FSTCOLOR);

    
    DrawText("List size n:", spaceRight, calcRowY(1, rows, options), fontSize, FSTCOLOR);

    Rectangle nRec = {spaceRight, calcRowY(2, rows, options), options.width-spaceRight*2, options.height/rows*0.6f};
    drawTextInput(nRec, state);

    DrawText("all distinct?:", spaceRight, calcRowY(3, rows, options), fontSize, FSTCOLOR);

    Rectangle btnRec = {spaceRight, calcRowY(4, rows, options), options.width-spaceRight*2, options.height/rows*0.6f};
    char* btnText = (state->allDistinct) ? "yes" : "no";
    drawButton(btnRec, btnText, &state->allDistinct, btnRec.height);


    drawOutline(options, 4, FSTCOLOR);
}

void drawStartButton(int w, int h, AppState* state) {
    int btnX = (int) w / 10 * 8;
    int btnY = (int) h / 20 * 18; 

    int btnWidth = (w / 6); 
    int btnHeight = (h / 14);
    
    
    Rectangle btn = {btnX, btnY, btnWidth, btnHeight};

    bool isPressed = false;
    drawButton(btn, "start", &isPressed, (btn.height+(btn.width/2)) / 3);
    if (isPressed) {
        state->toDraw = 1;
    }
}



void drawChooseUI(int w, int h, AppState* state) {
    drawSortChooser(w, h);
    drawOptChooser(w, h, state);
    drawStartButton(w, h, state);

    
    
}



