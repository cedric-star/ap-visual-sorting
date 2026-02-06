#include <unistd.h> 
#include <time.h>
#include <stdbool.h>

#include "structures.h"


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
            usleep(10000);
            list->index = i;
        }
    }
    list->isFinished = true;
}