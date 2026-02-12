#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> 
#include <time.h>
#include <stdbool.h>
#include <pthread.h>
#include "raylib.h"


#include "ui/ui.h"
#include "core/core.h"
//#include "sortAlgorithms.h"


#define defaultWidth 1200
#define defaultHeight 800
#define len(arr) (sizeof(arr) / sizeof((arr)[0]))






int main(void) {
    AppState state = {0};
    initAppState(&state);


    printf("starting...");
    int sWidth = defaultWidth;
    int sHeight = defaultHeight;

    

    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    SetWindowMinSize(1000, 700);               // Set window minimum dimensions (for FLAG_WINDOW_RESIZABLE)
    InitWindow(sWidth, sHeight, "Diagramm Beispiel");
    SetTargetFPS(60); 

    //0 = chooser window
    //1 = sorting window 
    //2 = ergebnis window

    while (!WindowShouldClose()) 
    {
        BeginDrawing();
        
        sWidth = GetScreenWidth();
        sHeight = GetScreenHeight();
        ClearBackground(BLACK);

        switch (state.toDraw) {
        case 0: drawChooseUI(sWidth, sHeight, &state); break;
        case 1: 
            Rectangle dia = {0, 0, sWidth, sHeight};
            for (int i = 0; i < state.algoNum; i++) { 
                createDiagram(dia, state.algos[i].list);
            }
            break;
        }
        
        EndDrawing();
    }
    CloseWindow();
    printf("stopping...");
    return 0;
}