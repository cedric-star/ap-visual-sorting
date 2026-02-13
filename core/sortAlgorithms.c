#include <unistd.h> 
#include <time.h>
#include <stdbool.h>

#include "core.h"

//#define wait 10000
#define baseWait 30000000 //30s

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

            usleep(wait/10);
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

    checkOrder(list, wait/2);
    algo->accesses += list->dynLength;
    if(list->isFinished) return;

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

void heapify(MyAlgorithm* algo, int n, int i, int wait, struct timespec* start) {
    struct timespec end;
    List* list;
    
    int biggestIndex = i;
    int leftNodeIndex = 2 * i + 1; //Index des linken Kind-Knotens
    int rightNodeIndex = 2 * i + 2; //Index des rechten Kind-Knotens
    list = algo->list;

    usleep(wait/4);
    clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
    algo->time = (end.tv_sec - start->tv_sec);
    algo->time += (end.tv_nsec - start->tv_nsec) / 1000000000.0;

    int* nums = list->nums;
    list->index = biggestIndex; 

    if(leftNodeIndex < n && nums[leftNodeIndex] > nums[biggestIndex]) {
        biggestIndex = leftNodeIndex;
    }

    if(rightNodeIndex < n && nums[rightNodeIndex] > nums[biggestIndex]) {
        biggestIndex = rightNodeIndex;
    }

    algo->accesses += 1;

    if(biggestIndex != i) {
        int temp = nums[i];
        nums[i] = nums[biggestIndex];
        nums[biggestIndex] = temp;


        heapify(algo, n, biggestIndex, wait, start);
    }
}

void heapSort(MyAlgorithm* algo, int wait, struct timespec* start) {
    
    struct timespec end;
    List* list;
    list = algo->list;
    int n = list->dynLength;

    //beginne vom letzten möglichen Elternknoten
    for(int i = n/2 - 2; i >= 0; i--) {
        list->index = i; 
        usleep(wait/4);

        heapify(algo, n, i, wait, start);
    }

    for(int i = n - 1; i > 0; i--) {
        list->index = i; 
        clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
        algo->time = (end.tv_sec - start->tv_sec);
        algo->time += (end.tv_nsec - start->tv_nsec) / 1000000000.0;

        int temp = list->nums[0];
        list->nums[0] = list->nums[i];
        list->nums[i] = temp;

        algo->repeats += 2;
        heapify(algo, i, 0, wait, start);
        usleep(wait/4);
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
    struct timespec start, end;

    clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
    int waitTime = calcWait(algo->list->dynLength);

    switch (algo->id) {
        case 0: bubbleSort(algo, waitTime, &start); break;
        case 1: bubbleSort(algo, waitTime, &start); break;
        case 2: selectionSort(algo, waitTime, &start); break;
        case 3: insertionSort(algo, waitTime, &start); break;
        case 4: bogoSort(algo, waitTime, &start); break;
        case 5: shellSort(algo, waitTime, &start); break;
        case 6: heapSort(algo, waitTime, &start); break;
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