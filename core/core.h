
#ifndef CORE_H
#define CORE_H

#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    unsigned char id;
    bool isSelected;
    char* name;
    char* description;
    char* worstCase;
    char* averageCase;
    char* bestCase;
    char* stable;
} AlgoInfo;

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

    List* list;
    char* name;
    long time;
    long accesses; //listenzugriffe
    long repeats; //iterationen / rekursionen
    //speichernutzung / allokationen
    //cpu auslastung

    bool correct; //ist sortierung korekt?
} MyAlgorithm;


typedef struct {
    char numMaxInput[8];//max siebenstellige zahl eingeben, alles <1mio. wird auf festen kleinen wert gesetzt
    int letCount;
    int toDraw; //welches fenster soll gezeichnet werden
    bool allDistinct;
    MyAlgorithm algos[16];
    int algoNum;
    pthread_t threads[16];
    AlgoInfo* algoInfos;
    int algoInfoNum;

    int showSortChooserPage; //chooseUI -> wleche seite der sortieralgorithmen angezeigt werden soll
    bool nextSortChooserPage;
} AppState;





typedef struct {
    unsigned char algoNum; //wie viele algorithmen zu sortieren
    unsigned char *algoList; //liste, welche algorithmen verwendet werden sollen


    int maxArrNum; //wie viele elemente in liste, und wie groß ist größtes element
    bool allDistinct; //alle unterschiedlich in unsortierter liste, oder egal

} SortStruct;



#include "../ui/ui.h"





void initSort(MyAlgorithm* algoInfo);

void setAllDisctinctRanNums(int *p_nums, int max);
void setRanNums(int *p_nums, int max);
void shuffleNums(int *p_nums, int maxIndex);


#endif