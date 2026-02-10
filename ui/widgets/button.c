
#include "../ui.h"


void drawButton(Rectangle box, char* text, bool* isPressed, int fontSize) {
    int mX = GetMouseX();
    int mY = GetMouseY();

    if (mX >= box.x && mX <= (box.x + box.width) && mY >= box.y && mY <= ( box.y + box.height)) {
        DrawRectangleRec(box, SNDCOLOR);

        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
            printf("pressed");
            *isPressed = !(*isPressed); //toggle boolean
        }      
    }
    drawOutline(box, 4, FSTCOLOR);
    
    
    
    DrawText(text, box.x+6, box.y, fontSize-4, FSTCOLOR);
}

void drawInputField(Rectangle box, char* input, int* letterCount) {
    drawOutline(box, 4, FSTCOLOR);


    if (CheckCollisionPointRec(GetMousePosition(), box)) {
        DrawRectangleRec(box, SNDCOLOR);
        SetMouseCursor(MOUSE_CURSOR_IBEAM);

        int key = GetCharPressed();

        //48 - 57 = zahlentasten oben auf tastatur (1,2,...9,0)
        while ((key >= 48) && (key <= 57) && (*letterCount < 10)) {
            input[*letterCount] = (char) key;
            input[*letterCount+1] = '\0';
            *letterCount += 1;
            printf("%c", key);

            key = GetCharPressed();
        }
        if (IsKeyPressed(KEY_BACKSPACE)) {
            *letterCount -= 1;
            if (*letterCount <  0) *letterCount = 0;
            input[*letterCount] = '\0';
        }

    } else {
        SetMouseCursor(MOUSE_CURSOR_DEFAULT);
    }

    int fontSize = 30;
    
    drawOutline(box, 4, FSTCOLOR);
    DrawText(input, box.x+6, box.y+2, fontSize, FSTCOLOR);    
}