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
    List* list = (List*) arg;
    simpelSort(list);
}

int main(void) {
    printf("starting...");
    int sWidth = defaultWidth;
    int sHeight = defaultHeight;

    int num = mass;
    int *nums = calloc(num, sizeof(int));

    setRanNums(nums, mass);

    pthread_t thread1;
    List list;
    
    

    list.dynLength = num;
    list.absLength = num;
    list.nums = nums;
    list.index = 0;
    list.isFinished = false;

    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(sWidth, sHeight, "Diagramm Beispiel");
    SetTargetFPS(60); 

    
    pthread_create(&thread1, NULL, myThread, &list);


    

    //0 = chooser window
    //1 = sorting window 
    //2 = ergebnis window
    int toDraw = 0;

    while (!WindowShouldClose()) 
    {
        BeginDrawing();
        
        sWidth = GetScreenWidth();
        sHeight = GetScreenHeight();
        ClearBackground(BLACK);

        switch (toDraw) {
        case 0: drawChooseUI(sWidth, sHeight, &toDraw); break;
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