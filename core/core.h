
#ifndef CORE_H
#define CORE_H

#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    char numMaxInput[11];
    int letCount;
    int toDraw; //welches fenster soll gezeichnet werden
} AppState;

typedef struct {
    int dynLength;
    int absLength;
    int *nums;
    int index;
    bool isFinished;
} List;

typedef struct {
    unsigned char id;
    // 0 -> test
    // 1 -> bubblesort
    // 2 -> quicksort

    char* name;
    long time;
    long accesses; //listenzugriffe
    long repeats; //iterationen / rekursionen
    //speichernutzung / allokationen
    //cpu auslastung

    bool correct; //ist sortierung korekt?
    bool stable; //ändert algorithmus reihenfolge gleicher elemente


} MyAlgorithm;

typedef struct {
    unsigned char algoNum; //wie viele algorithmen zu sortieren
    unsigned char *algoList; //liste, welche algorithmen verwendet werden sollen


    int maxArrNum; //wie viele elemente in liste, und wie groß ist größtes element
    bool allDistinct; //alle unterschiedlich in unsortierter liste, oder egal

} SortStruct;



#include "../ui/ui.h"





void simpelSort(List* list);

void setAllDisctinctRanNums(int *p_nums, int max);
void setRanNums(int *p_nums, int max);


#endif