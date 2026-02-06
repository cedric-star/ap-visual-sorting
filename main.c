#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> 
#include <time.h>
#include <pthread.h>
#include "raylib.h"


#define defaultWidth 1200
#define defaultHeight 800
#define timeStep 10000
#define mass 60
#define len(arr) (sizeof(arr) / sizeof((arr)[0]))

typedef struct {
    int x;
    int y;
    int width;
    int height;
} Box;

typedef struct {
    int dynLength;
    int absLength;
    int *nums;
    int index;
    bool isFinished;
} List;

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

void drawOutline(Box box, int thickness, Color c) {
    //oben
    DrawRectangle(box.x, box.y, box.width, thickness, c);

    //links
    DrawRectangle(box.x, box.y, thickness, box.height, c);
   
    //untent
    DrawRectangle(box.x, box.height-thickness, box.width, box.height, c);
    
    //rechts
    DrawRectangle(box.x + box.width - thickness, box.y, thickness, box.height, c);
}


void simpelSort(List* list) {
    int swapped = 1;
    while (swapped && list->dynLength-- > 0)
    {  
        swapped = 0;
        for(int i=0; i<list->dynLength; ++i)
        {
            if(list->nums[i] > list->nums[i+1])
            {
                int temp = list->nums[i];
                list->nums[i] = list->nums[i+1];
                list->nums[i+1] = temp;
                swapped = 1;
            }
            usleep(timeStep);
            list->index = i;
        }
    }
    list->isFinished = true;
}

void* myThread(void* arg) {
    List* list = (List*) arg;
    simpelSort(list);
}

void createDiagram(Box box, List* list) {
    int len = list->absLength;
    if (len <= 0) return;
    
    int barWidth = box.width / len;
    int maxValue = findMax(list->nums, len);  // Maximum berechnen
    
    for(int i = 0; i < len; i++) {
        int barHeight = (list->nums[i] * box.height) / maxValue;
        
        int x = box.x + (i * barWidth);
        int y = box.y + box.height - barHeight;
        
        
        if (i == list->index) {
            DrawRectangle(x, y, barWidth, barHeight, RED);
        } else {
            DrawRectangle(x, y, barWidth, barHeight, LIGHTGRAY);
        }

        if (list->isFinished) {
            DrawRectangle(x, y, barWidth, barHeight, GRAY);
            //usleep(timeStep); //animation so aufsteigende balken noch machen
        }
    }

    drawOutline(box, 4, PINK);
}

int main(void) {
    printf("1");
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
    //simpelSort(nums, num);

    while (!WindowShouldClose()) 
    {
        BeginDrawing();
        
        sWidth = GetScreenWidth();
        sHeight = GetScreenHeight();
        Box b = {0, 0, sWidth, sHeight};
        ClearBackground(BLACK);
        createDiagram(b, &list);
        
        EndDrawing();
    }

    //pthread_join(thread1, NULL);
    free(nums);
    CloseWindow();
    return 0;
}