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
#define timeStep 10000000
#define mass 50
#define len(arr) (sizeof(arr) / sizeof((arr)[0]))

void* myThread(void* arg) {
    MyAlgorithm* algoInfo = (MyAlgorithm*) arg;
    initSort(algoInfo);
}

void initAppState(AppState* state) {
    state->numMaxInput[0] = '0';
    state->numMaxInput[1] = '\0';
    state->letCount = 0;
    state->toDraw = 0;
    state->allDistinct = false;
}


int main(void) {
    AppState state = {0};
    initAppState(&state);


    printf("starting...");
    int sWidth = defaultWidth;
    int sHeight = defaultHeight;

    int num = mass;
    int *nums = calloc(num, sizeof(int));

    setRanNums(nums, mass);

    pthread_t thread1;
    List list;
    MyAlgorithm algoInfo;
    

    list.dynLength = num;
    list.absLength = num;
    list.nums = nums;
    list.index = 0;
    list.isFinished = false;

    algoInfo.id = 1;
    algoInfo.list = &list;
    algoInfo.name = "MyName";
    algoInfo.accesses = 0;
    algoInfo.repeats = 0;
    algoInfo.correct = false;
    algoInfo.stable = false;

    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(sWidth, sHeight, "Diagramm Beispiel");
    SetTargetFPS(60); 

    
    pthread_create(&thread1, NULL, myThread, &algoInfo);


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
            createDiagram(dia, &list);
            break;
        }
        
        EndDrawing();

        
    }

    pthread_join(thread1, NULL);
    free(nums);
    CloseWindow();
    printf("stopping...");
    return 0;
}