#include <unistd.h> 
#include <time.h>
#include <stdbool.h>

#include "core.h"

//#define wait 10000
#define baseWait 5000000 //5s

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

void bubbleSort(MyAlgorithm* algo, int wait, struct timespec* start) {
    struct timespec end;
    
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

                algo->accesses += 3;
            }
            list->index = i;

            usleep(wait);
            clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
            algo->time = (end.tv_sec - start->tv_sec);
            algo->time += (end.tv_nsec - start->tv_nsec) / 1000000000.0;
        }
        algo->repeats += 1;
    }
    list->isFinished = true;
}

void selectionSort(MyAlgorithm* algo, int wait, struct timespec* start) {
    
    List* list;
    int n;
    int minIdx;
    struct timespec end;

    list = algo->list;
    n = list->dynLength;
    for(int i = 0; i < n - 1; i++) {
        minIdx = i;

        for(int j = i + 1; j < n; j++) {
            if(list->nums[j] < list->nums[minIdx]) {
                minIdx = j;
            }
            algo->accesses += 1;
        }
        int tmp = list->nums[i];
        list->nums[i] = list->nums[minIdx];
        list->nums[minIdx] = tmp;
        list->index = minIdx;

        algo->repeats += 1;
        algo->accesses += 2;

        usleep(wait);
        clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
        algo->time = (end.tv_sec - start->tv_sec);
        algo->time += (end.tv_nsec - start->tv_nsec) / 1000000000.0;
    }
}

void insertionSort(MyAlgorithm* algo, int wait, struct timespec* start) {
    
    List* list;
    int n;
    struct timespec end;

    list = algo->list;
    n = list->dynLength;

    for(int bound = 1; bound < n; bound++) {
        
        
        int currElem = list->nums[bound];
        int i = bound;

        list->index = bound;
        usleep(wait/3);

        while(i > 0 && (list->nums[i-1] > currElem)) {
            list->nums[i] = list->nums[i-1];
            i = i - 1;

            list->index = i;
            algo->accesses += 2;
            usleep(wait/3);
        }
        list->nums[i] = currElem;

        algo->repeats += 1;
        algo->accesses += 1;

        usleep(wait/3);
        clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
        algo->time = (end.tv_sec - start->tv_sec);
        algo->time += (end.tv_nsec - start->tv_nsec) / 1000000000.0;
    }
}

void bogoSort(MyAlgorithm* algo, int wait, struct timespec* start) {
    
    struct timespec end;
    List* list;
    list = algo->list;
    while(true) {
        shuffleNums(list->nums, (list->dynLength));
        checkOrder(list, wait/2);
        if(list->isFinished == true) {
            break;
        }

        algo->repeats += 1;
        algo->accesses += list->dynLength * 2;

        usleep(wait/2);
        clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
        algo->time = (end.tv_sec - start->tv_sec);
        algo->time += (end.tv_nsec - start->tv_nsec) / 1000000000.0;
    }
}

//geklaut :)
void shellSort(MyAlgorithm* algo, int wait, struct timespec* start) {
    struct timespec end;

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

            algo->accesses += 4;

            usleep(wait/2);
            clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
            algo->time = (end.tv_sec - start->tv_sec);
            algo->time += (end.tv_nsec - start->tv_nsec) / 1000000000.0;
        }
        algo->repeats += 1;

        usleep(wait/2);
    }
}


void quickSort(MyAlgorithm* algo, int* arr, int left, int right, int wait) {
    if (left < right) {
        // Select pivot (using rightmost element)
        int pivot = arr[right];
        algo->list->index = right;
        
        // Index of smaller element
        int i = left - 1;
        
        // Partition the array
        for (int j = left; j < right; j++) {
            algo->list->index = j;
            if (arr[j] <= pivot) {
                i++;
                // Swap arr[i] and arr[j]
                int temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
        
        // Place pivot in correct position
        int temp = arr[i + 1];
        arr[i + 1] = arr[right];
        arr[right] = temp;
        
        int pivotIndex = i + 1;
        
        // Recursively sort elements before and after pivot
        usleep(wait*1000);
        quickSort(algo, arr, left, pivotIndex - 1, wait);
        quickSort(algo, arr, pivotIndex + 1, right, wait);
    }
}

void quickSortWrapper(MyAlgorithm* algo, int wait, struct timespec* start) {
    struct timespec end;
    List* list = algo->list;  // Assuming there's a list pointer
    int* arr = algo->list->nums;  // Array to sort
    int length = list->absLength;  // Length of the array
    
    quickSort(algo, arr, 0, length - 1, wait);  // Sort the entire array
    
    // Rest of your timing/waiting logic here
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
    struct timespec start, end;

    clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
    int waitTime = calcWait(algo->list->dynLength);

    switch (algo->id) {
        case 0: bubbleSort(algo, waitTime, &start); break;
        case 1: bubbleSort(algo, waitTime, &start); break;
        case 2: selectionSort(algo, waitTime, &start); break;
        case 3: insertionSort(algo, waitTime, &start); break;
        case 4: bogoSort(algo, waitTime, &start); break;
        case 5: quickSortWrapper(algo, waitTime, &start); break;
        case 6: shellSort(algo, waitTime, &start); break;



        //hier fehlt code
        
        case 7: selectionSort(algo, waitTime, &start); break;
        case 8: selectionSort(algo, waitTime, &start); break;
        case 9: selectionSort(algo, waitTime, &start); break;
        case 10: selectionSort(algo, waitTime, &start); break;
        case 11: selectionSort(algo, waitTime, &start); break;
        case 12: selectionSort(algo, waitTime, &start); break;
        case 13: selectionSort(algo, waitTime, &start); break;
        case 14: selectionSort(algo, waitTime, &start); break;
        case 15: selectionSort(algo, waitTime, &start); break;
        case 16: selectionSort(algo, waitTime, &start); break;
        case 17: selectionSort(algo, waitTime, &start); break;
        case 18: selectionSort(algo, waitTime, &start); break;
        case 19: selectionSort(algo, waitTime, &start); break;
        case 20: selectionSort(algo, waitTime, &start); break;
        case 21: selectionSort(algo, waitTime, &start); break;
        case 22: selectionSort(algo, waitTime, &start); break;
        case 23: selectionSort(algo, waitTime, &start); break;
        case 24: selectionSort(algo, waitTime, &start); break;

    }

    checkOrder(algo->list, waitTime);
}