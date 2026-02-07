#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> 
#include <time.h>
#include <stdbool.h>
#include <pthread.h>
#include "raylib.h"


#include "ui/ui.h"
#include "sortAlgorithms.h"


#define defaultWidth 1200
#define defaultHeight 800
#define timeStep 1000
#define mass 100
#define len(arr) (sizeof(arr) / sizeof((arr)[0]))




int myRanNum() {
    return (rand() % mass + 1);
}

int findMax(int ar[], int length) {
    int maxValue = 0;
    for(int i = 0; i < length; i++) {
        if (ar[i] > maxValue) {
            maxValue = ar[i];
        }
    }
    return maxValue;
}






void* myThread(void* arg) {
    List* list = (List*) arg;
    simpelSort(list);
}

void createDiagram(Rectangle box, List* list) {
    int len = list->absLength;
    if (len <= 0) return;
    
    int barWidth = box.width / len;
    int maxValue = findMax(list->nums, len);  // Maximum berechnen

    
    for(int i = 0; i < len; i++) {
        int barHeight = (list->nums[i] * box.height) / maxValue;
        
        int x = box.x + (i * barWidth);
        int y = box.y + box.height - barHeight;
        
        
        if (i == list->index) {
            DrawRectangle(x, y, barWidth-1, barHeight, RED);
        } else {
            DrawRectangle(x, y, barWidth-1, barHeight, LIGHTGRAY);
        }

        if (list->isFinished) {
            DrawRectangle(x, y, barWidth-1, barHeight, GRAY);
            //usleep(timeStep); //animation so aufsteigende balken noch machen
        }

    }

    drawOutline(box, 4, PINK);
}

int main(void) {
    printf("starting...");
    int sWidth = defaultWidth;
    int sHeight = defaultHeight;

    int num = mass;
    int *nums = calloc(num, sizeof(int));
    pthread_t thread1;
    List list;
    
    
    for (int i = 0; i < num; i++) {
        nums[i] = myRanNum();
        printf("%d, ", nums[i]);
    }
    list.dynLength = num;
    list.absLength = num;
    list.nums = nums;
    list.index = 0;
    list.isFinished = false;

    SetConfigFlags(FLAG_WINDOW_MAXIMIZED | FLAG_WINDOW_RESIZABLE);
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



        }
        


        //createDiagram(dia, &list);
        EndDrawing();

        
    }

    pthread_join(thread1, NULL);
    free(nums);
    CloseWindow();
    printf("stopping...");
    return 0;
}