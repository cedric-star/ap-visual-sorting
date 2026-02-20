
#ifndef CORE_H
#define CORE_H

#include <stdlib.h>
#include <stdbool.h>

#define MAXARNUM 25 //maximale Anzahl gleichzeitig anzeigbarer Algos
#define CSVNAME "mydata.csv" //Exportname

//Statische Informationen zu einem Algorithmus
//Daten für die Startseite und zur Info des Nutzers
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
    int index; //zur Anzeige in der UI
    bool isFinished;
} List;

//Daten zu einem gewählten Algorithmus
//Dynamische Anpassung während der Algorithmus läuft
typedef struct {
    unsigned char id;
    // 0 -> test
    // 1 -> bubblesort
    // 2 -> quicksort
    // 3 -> ...

    List* list;
    char* name;
    double time; //Thread-Zeit
    long accesses; //Listenzugriffe
    long repeats; //Iterationen/Rekursionen

    bool correct; //Ist sortierung korekt? (derzeit unbenutzt)
} MyAlgorithm;


typedef struct {
    char numMaxInput[8];//max siebenstellige zahl eingeben, alles <1mio. wird auf festen kleinen wert gesetzt
    int letCount;
    int toDraw; //welches fenster soll gezeichnet werden
    bool allDistinct;
    bool sorted;
    bool descending;
    MyAlgorithm algos[MAXARNUM];
    int algoNum; //ausgewählte sortieralgorithmen;
    pthread_t threads[MAXARNUM];
    AlgoInfo* algoInfos;
    int algoInfoNum;

    int showSortChooserPage; //chooseUI -> wleche seite der sortieralgorithmen angezeigt werden soll
    bool nextSortChooserPage;

    int showSortViewerPage;
    bool nextSortViewerPage;
} AppState;


typedef struct {
    unsigned char algoNum; //wie viele algorithmen zu sortieren
    unsigned char *algoList; //liste, welche algorithmen verwendet werden sollen


    int maxArrNum; //wie viele elemente in liste, und wie groß ist größtes element
    bool allDistinct; //alle unterschiedlich in unsortierter liste, oder egal

} SortStruct;

typedef struct {
    time_t   tv_sec;        // seconds 
    long     tv_nsec;       // nanoseconds
} timespec;

#include "../ui/ui.h"

void initSort(MyAlgorithm* algoInfo);
void initAppState(AppState* state);
void setAllDisctinctSortedAsc(int *p_nums, int max);
void setRanNumsUnsorted(int *p_nums, int max);
void setNumsBackwards(int *p_nums, int max);
void shuffleNums(int *p_nums, int maxIndex);
void setSorted(int *p_nums, int maxIndex);

#endif