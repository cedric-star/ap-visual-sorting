#include <unistd.h> 
#include <time.h>
#include <stdbool.h>

#include "core.h"

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
            usleep(1000);
            list->index = i;
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
            usleep(1000);
            list->index = i;
        }
        
    }
    list->isFinished = true;
}

void initSort(MyAlgorithm* algoInfo) {
    
    switch (algoInfo->id) {
        case 0: simpleSort(algoInfo); break;
        case 1: bubbleSort(algoInfo); break;
        }
}