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
#define mass 20
#define len(arr) (sizeof(arr) / sizeof((arr)[0]))

void* myThread(void* arg) {
    MyAlgorithm* algo = (MyAlgorithm*) arg;
    initSort(algo);
}

void initAppState(AppState* state, AlgoInfo *algoInfos) {

    AlgoInfo *bubbleInfos;
    AlgoInfo *selectionInfos;
    AlgoInfo *insertionInfos;
    AlgoInfo *bogoInfos;

    state->numMaxInput[0] = '\0';
    state->letCount = 0;
    state->toDraw = 0;

    bubbleInfos = malloc(sizeof(AlgoInfo));
    bubbleInfos -> id = 1;
    bubbleInfos -> name = "Bubblesort";
    bubbleInfos -> description = "Die Liste wird beginnend vom ersten Element "
    "(von rechts) angefangen zu sortiert. Jedes Element mit Index i wird mit dem Folgelement "
    "mit Index i+1 verglichen. Ist elem(i) > elem(i+1) werden die Elemente vertauscht. "
    "Nach jedem Durchlauf befindet sich das Größte Element der Liste am Ende und die "
    "Liste wird anschließend um das derzeit letzte Element vekleinert. \n"
    "Link: https://publications.scss.tcd.ie/tech-reports/reports.05/TCD-CS-2005-57.pdf";
    bubbleInfos -> worstCase = "O(n²)";
    bubbleInfos -> averageCase = "O(n²)";
    bubbleInfos -> bestCase = "O(n)";
    bubbleInfos -> stable = "unknown";
    algoInfos[1] = *bubbleInfos;

    
    selectionInfos = malloc(sizeof(AlgoInfo));
    selectionInfos -> id = 2;
    selectionInfos -> name = "Selectionsort";
    selectionInfos -> description = "Selection Sort beginnt stets mit dem "
    "ersten Element der Liste. Das Startelement wird als Minimum eingespeichert. "
    "Bei jedem Durchlauf werden alle Elemente der Liste mit dem Minimum verglichen. "
    "Am Ende der Liste angekommen, wird das Minimum am Anfang der Liste platziert und beim "
    "nächten Durchlauf aus der Liste ausgelassen." 
    "Link: https://publications.scss.tcd.ie/tech-reports/reports.05/TCD-CS-2005-57.pdf";
    selectionInfos -> worstCase = "O(n²)";
    selectionInfos -> averageCase = "O(n²)";
    selectionInfos -> bestCase = "O(n²)";
    selectionInfos -> stable = "unknown";
    algoInfos[2] = *selectionInfos;

    insertionInfos = malloc(sizeof(AlgoInfo));
    insertionInfos -> id = 3;
    insertionInfos -> name = "Insertionsort";
    insertionInfos -> description = "Beginnend mit einer Teilliste, die nur das "
    "erste Element der zu sortierenden Liste enthält, wird immer das Element am "
    "Ende der Teilliste in die Teilliste einsortiert. Nach jedem Durchlauf, wird die "
    "Teilliste um ein weiteres Element erweitert.\n"
    "Link: https://publications.scss.tcd.ie/tech-reports/reports.05/TCD-CS-2005-57.pdf";
    insertionInfos -> worstCase = "O(n²)";
    insertionInfos -> averageCase = "O(n²)";
    insertionInfos -> bestCase = "O(n)";
    insertionInfos -> stable = "ja";
    algoInfos[3] = *insertionInfos;

    bogoInfos = malloc(sizeof(AlgoInfo));
    bogoInfos -> id = 4;
    bogoInfos -> name = "Bogosort";
    bogoInfos -> description = "Bogo Sort ist ein extrem ineffizienter "
    "Sortieralgorithmus, basierend auf dem \"Generier und Teste\"-Paradigma. "
    "Die Liste wird vollständig zufällig angeordnet und danach geprüft, ob sie richtig ist.\n"
    "Link: https://www.geeksforgeeks.org/dsa/bogosort-permutation-sort/";
    bogoInfos -> worstCase = "O(?)";
    bogoInfos -> averageCase = "O(n*n!)";
    bogoInfos -> bestCase = "O(n)";
    bogoInfos -> stable = "nein";
    algoInfos[4] = *bogoInfos;

}


int main(void) {
    AppState state = {0};
    AlgoInfo *algoInfos = calloc(10, sizeof(AlgoInfo));
    initAppState(&state, algoInfos);

    printf("ID of bubble sort: %d\n", algoInfos[1].id);
    printf("Desc of bubble sort: %s\n", algoInfos[1].description);

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

    algoInfo.id = 3;
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