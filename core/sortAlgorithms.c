#include <unistd.h> 
#include <time.h>
#include <stdbool.h>

#include "core.h"

#define wait 10000

void checkOrder(List *p_list) {
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

void simpleSort(MyAlgorithm* algo) {
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

void bubbleSort(MyAlgorithm* algo) {
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

void selectionSort(MyAlgorithm* algo) {
    
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

void insertionSort(MyAlgorithm* algo) {
    
    List* list;
    int n;

    list = algo->list;
    n = list->dynLength;

    for(int bound = 1; bound < n; bound++) {
        
        int currElem = list->nums[bound];
        int i = bound;

        list->index = bound;
        usleep(wait);

        while(i > 0 && (list->nums[i-1] > currElem)) {
            list->nums[i] = list->nums[i-1];
            i = i - 1;
            list->index = i;
            usleep(wait);
        }
        list->nums[i] = currElem;
        usleep(wait);
    }
}

void bogoSort(MyAlgorithm* algo) {
    
    List* list;
    list = algo->list;
    while(true) {
        shuffleNums(list->nums, (list->dynLength));
        checkOrder(list);
        if(list->isFinished == true) {
            break;
        }
        usleep(wait);
    }
}

void initSort(MyAlgorithm* algo) {
    
    switch (algo->id) {
        case 0: simpleSort(algo); break;
        case 1: bubbleSort(algo); break;
        case 2: selectionSort(algo); break;
        case 3: insertionSort(algo); break;
        case 4: bogoSort(algo); break;
    }
    checkOrder(algo->list);
}