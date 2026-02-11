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



void initAppState(AppState* state) {
    

    for (int i = 0; i < 8; i++) {
        state->numMaxInput[i] = '0';
    }
    state->numMaxInput[1] = '\0';
    state->letCount = 0;
    state->toDraw = 0;
    state->allDistinct = false;
    state->algoNum = 0;
    state->showSortChooserPage = 0;
    state->nextSortChooserPage = false;

    
    AlgoInfo *algoInfos = calloc(10, sizeof(AlgoInfo));
    // Testsort
    algoInfos[0].id = 1;
    algoInfos[0].name = "TestSort";
    algoInfos[0].description = "Die Liste wird beginnend vom ersten Element "
    "(von rechts) angefangen zu sortiert. Jedes Element mit Index i wird mit dem Folgelement "
    "mit Index i+1 verglichen. Ist elem(i) > elem(i+1) werden die Elemente vertauscht. "
    "Nach jedem Durchlauf befindet sich das Größte Element der Liste am Ende und die "
    "Liste wird anschließend um das derzeit letzte Element verkleinert. \n"
    "Link: https://publications.scss.tcd.ie/tech-reports/reports.05/TCD-CS-2005-57.pdf ";
    algoInfos[0].worstCase = "O(n²)";
    algoInfos[0].averageCase = "O(n²)";
    algoInfos[0].bestCase = "O(n)";
    algoInfos[0].stable = "unknown";
    algoInfos[0].isSelected = false;

    // Bubblesort
    algoInfos[1].id = 1;
    algoInfos[1].name = "Bubblesort";
    algoInfos[1].description = "Die Liste wird beginnend vom ersten Element "
    "(von rechts) angefangen zu sortiert. Jedes Element mit Index i wird mit dem Folgelement "
    "mit Index i+1 verglichen. Ist elem(i) > elem(i+1) werden die Elemente vertauscht. "
    "Nach jedem Durchlauf befindet sich das Größte Element der Liste am Ende und die "
    "Liste wird anschließend um das derzeit letzte Element verkleinert. \n"
    "Link: https://publications.scss.tcd.ie/tech-reports/reports.05/TCD-CS-2005-57.pdf ";
    algoInfos[1].worstCase = "O(n²)";
    algoInfos[1].averageCase = "O(n²)";
    algoInfos[1].bestCase = "O(n)";
    algoInfos[1].stable = "unknown";
    algoInfos[1].isSelected = false;

    // Selectionsort
    algoInfos[2].id = 2;
    algoInfos[2].name = "Selectionsort";
    algoInfos[2].description = "Selection Sort beginnt stets mit dem "
    "ersten Element der Liste. Das Startelement wird als Minimum eingespeichert. "
    "Bei jedem Durchlauf werden alle Elemente der Liste mit dem Minimum verglichen. "
    "Am Ende der Liste angekommen, wird das Minimum am Anfang der Liste platziert und beim "
    "nächsten Durchlauf aus der Liste ausgelassen.\n"
    "Link: https://publications.scss.tcd.ie/tech-reports/reports.05/TCD-CS-2005-57.pdf ";
    algoInfos[2].worstCase = "O(n²)";
    algoInfos[2].averageCase = "O(n²)";
    algoInfos[2].bestCase = "O(n²)";
    algoInfos[2].stable = "unknown";
    algoInfos[2].isSelected = false;

    // Insertionsort
    algoInfos[3].id = 3;
    algoInfos[3].name = "Insertionsort";
    algoInfos[3].description = "Beginnend mit einer Teilliste, die nur das "
    "erste Element der zu sortierenden Liste enthält, wird immer das Element am "
    "Ende der Teilliste in die Teilliste einsortiert. Nach jedem Durchlauf wird die "
    "Teilliste um ein weiteres Element erweitert.\n"
    "Link: https://publications.scss.tcd.ie/tech-reports/reports.05/TCD-CS-2005-57.pdf ";
    algoInfos[3].worstCase = "O(n²)";
    algoInfos[3].averageCase = "O(n²)";
    algoInfos[3].bestCase = "O(n)";
    algoInfos[3].stable = "ja";
    algoInfos[3].isSelected = false;

    // Bogosort
    algoInfos[4].id = 4;
    algoInfos[4].name = "Bogosort";
    algoInfos[4].description = "Bogo Sort ist ein extrem ineffizienter "
    "Sortieralgorithmus, basierend auf dem \"Generier und Teste\"-Paradigma. "
    "Die Liste wird vollständig zufällig angeordnet und danach geprüft, ob sie richtig ist.\n"
    "Link: https://www.geeksforgeeks.org/dsa/bogosort-permutation-sort/ ";
    algoInfos[4].worstCase = "O(?)";
    algoInfos[4].averageCase = "O(n*n!)";
    algoInfos[4].bestCase = "O(n)";
    algoInfos[4].stable = "nein";
    algoInfos[4].isSelected = false;

    state->algoInfos = algoInfos;
    state->algoInfoNum = 4;

}


int main(void) {
    AppState state = {0};
    initAppState(&state);


    printf("starting...");
    int sWidth = defaultWidth;
    int sHeight = defaultHeight;

    

    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    SetWindowMinSize(500, 300);               // Set window minimum dimensions (for FLAG_WINDOW_RESIZABLE)
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