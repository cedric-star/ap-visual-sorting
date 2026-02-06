#include "ui.h"

void drawSortChooser(int w, int h) {
    Rectangle rec = {0, 0, ((int) w/4), ((int) h/5*3)};
    drawOutline(rec, 4, LIGHTGRAY);
}

void drawOptChooser(int w, int h) {
    Rectangle rec = {0, ((int) h/5*3), ((int) w/4), h};
    drawOutline(rec, 4, LIGHTGRAY);
}


void drawChooseUI(int w, int h) {
    drawSortChooser(w, h);
    drawOptChooser(w, h);
}

