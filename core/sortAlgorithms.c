#include <unistd.h> 
#include <time.h>
#include <stdbool.h>

#include "core.h"

//#define wait 10000
#define baseWait 60000000 //60s

void checkOrder(List *p_list, int wait) {
    for(int i = 1; i < p_list->dynLength; i++) {
        if(p_list->nums[i] < p_list->nums[i-1]) {
            p_list->isFinished = false;
            return;
        }
        p_list->index = i;
        usleep(wait/4);
    }
    p_list->isFinished = true;
}

void simpleSort(MyAlgorithm* algo, int wait) {
    int swapped = 1;
    List* list = algo->list;
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
            
            list->index = i;
            usleep(wait);
        }
        
    }
    list->isFinished = true;
}

void bubbleSort(MyAlgorithm* algo, int wait) {
    int swapped = 1;
    List* list = algo->list;
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
            usleep(wait);
            list->index = i;
        }
        
    }
    list->isFinished = true;
}

void selectionSort(MyAlgorithm* algo, int wait) {
    
    List* list;
    int n;
    int minIdx;

    list = algo->list;
    n = list->dynLength;
    for(int i = 0; i < n - 1; i++) {
        minIdx = i;

        for(int j = i + 1; j < n; j++) {
            if(list->nums[j] < list->nums[minIdx]) {
                minIdx = j;
            }
        }

        int tmp = list->nums[i];
        list->nums[i] = list->nums[minIdx];
        list->nums[minIdx] = tmp;
        list->index = minIdx;
        usleep(wait);
    }
}

void insertionSort(MyAlgorithm* algo, int wait) {
    
    List* list;
    int n;

    list = algo->list;
    n = list->dynLength;

    for(int bound = 1; bound < n; bound++) {
        algo->repeats += 1;
        algo->accesses += 2;
        
        int currElem = list->nums[bound];
        int i = bound;

        list->index = bound;
        usleep(wait/3);

        while(i > 0 && (list->nums[i-1] > currElem)) {
            algo->accesses += 2;
            list->nums[i] = list->nums[i-1];
            i = i - 1;
            list->index = i;
            usleep(wait/3);
        }
        list->nums[i] = currElem;
        usleep(wait/3);
    }
}

void bogoSort(MyAlgorithm* algo, int wait) {
    
    List* list;
    list = algo->list;
    while(true) {
        algo->repeats += 1;
        shuffleNums(list->nums, (list->dynLength));
        checkOrder(list, wait/2);
        if(list->isFinished == true) {
            break;
        }
        usleep(wait/2);
    }
}

//geklaut :)
void shellSort(MyAlgorithm* algo, int wait) {
    int gaps[] = {701, 301, 132, 57, 23, 10, 4, 1};

    List* list;
    list = algo->list;
    int n = list->dynLength;

    for(int gap = n/2; gap > 0; gap /= 2) {
        for(int i = gap; i < n; i++) {
            int temp = list->nums[i];
            int j = i;

            while (j >= gap && list->nums[j - gap] > temp) {
                list->nums[j] = list->nums[j - gap];
                j -= gap;
            }

            list->nums[j] = temp;
            list->index = j;
            usleep(wait/2);
        }
        usleep(wait/2);
    }
}


int calcWait(int numsLength) {
    //Berechnet die Länge der Wartezeit in µs
    //Vgl.: 1s  = 1.000.000 µs
    //      1ms = 1.000 µs
    // 1s als define definiert für Basiswert

    int waitTime;

    //Gleichung durch Trial and Error bestimmt :P
    //Versucht die Wartezeit mit der Größe der Liste zu skalieren, 
    // sodass die Wartezeit für große Listen nicht extrem steigt.
    waitTime = baseWait / (numsLength * sqrt(numsLength));
    //waitTime = baseWait / (numsLength * numsLength);
    return waitTime;

}

void initSort(MyAlgorithm* algo) {
    
    int waitTime = calcWait(algo->list->dynLength);

    switch (algo->id) {
        case 0: simpleSort(algo, waitTime); break;
        case 1: bubbleSort(algo, waitTime); break;
        case 2: selectionSort(algo, waitTime); break;
        case 3: insertionSort(algo, waitTime); break;
        case 4: bogoSort(algo, waitTime); break;
        case 5: shellSort(algo, waitTime); break;

        //hier fehlt code
        case 6: selectionSort(algo, waitTime); break;
        case 7: selectionSort(algo, waitTime); break;
        case 8: selectionSort(algo, waitTime); break;
        case 9: selectionSort(algo, waitTime); break;
        case 10: selectionSort(algo, waitTime); break;
        case 11: selectionSort(algo, waitTime); break;
        case 12: selectionSort(algo, waitTime); break;
        case 13: selectionSort(algo, waitTime); break;
        case 14: selectionSort(algo, waitTime); break;
        case 15: selectionSort(algo, waitTime); break;
        case 16: selectionSort(algo, waitTime); break;
        case 17: selectionSort(algo, waitTime); break;
        case 18: selectionSort(algo, waitTime); break;
        case 19: selectionSort(algo, waitTime); break;
        case 20: selectionSort(algo, waitTime); break;
        case 21: selectionSort(algo, waitTime); break;
        case 22: selectionSort(algo, waitTime); break;
        case 23: selectionSort(algo, waitTime); break;
        case 24: selectionSort(algo, waitTime); break;
        
    }
    checkOrder(algo->list, waitTime);
}