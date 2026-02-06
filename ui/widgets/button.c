
#include "../ui.h"


void drawButton(Rectangle box, char* text, Color c) {
    DrawRectangleRec(box, c);

    int mX = GetMouseX();
    int mY = GetMouseY();
    //printf("%d, %d\n", mX, mY);

    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
        if (mX >= box.x && mX <= (box.x + box.width) && mY >= box.y && mY <= ( box.y + box.height)) {
            printf("pressed");
            DrawRectangleRec(box, PINK);

        }
    }
}