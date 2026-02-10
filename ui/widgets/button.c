
#include "../ui.h"


void drawButton(Rectangle box, char* text, Color c, bool* isPressed) {
    
    drawOutline(box, 4, c);
    DrawText(text, box.x+6, box.y+2, ((box.height-2)+(box.width-2)/120), c);

    int mX = GetMouseX();
    int mY = GetMouseY();
    //printf("%d, %d\n", mX, mY);


    if (mX >= box.x && mX <= (box.x + box.width) && mY >= box.y && mY <= ( box.y + box.height)) {
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) || IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
            printf("pressed");
            *isPressed = true;
            DrawRectangleRec(box, c);
        }      
    }
}

void drawInputField(Rectangle box, char* input, int* letterCount, Color c) {
    drawOutline(box, 4, c);


    if (CheckCollisionPointRec(GetMousePosition(), box)) {
        SetMouseCursor(MOUSE_CURSOR_IBEAM);

        int key = GetCharPressed();


        while ((key >= 32) && (key <= 125) && (*letterCount < 10)) {
            input[*letterCount] = (char) key;
            input[*letterCount+1] = '\0';
            *letterCount += 1;
            printf("%c", key);
        }

    } else {
        SetMouseCursor(MOUSE_CURSOR_DEFAULT);
    }

    DrawText(input, box.x, box.y, 30, c);
}