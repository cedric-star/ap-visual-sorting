
#include "../ui.h"


void drawButton(Rectangle box, char* text, Color c, bool* isPressed) {
    
    drawOutline(box, 4, c);
        DrawText(text, box.x+6, box.y+2, box.height-2, c);

    int mX = GetMouseX();
    int mY = GetMouseY();
    //printf("%d, %d\n", mX, mY);


    if (mX >= box.x && mX <= (box.x + box.width) && mY >= box.y && mY <= ( box.y + box.height)) {
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) || IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
            printf("pressed");
            *isPressed = true;
            DrawRectangleRec(box, c);
        }      
        
        printf("hover");
        
    }

    
}