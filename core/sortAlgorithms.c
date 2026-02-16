#include <unistd.h> 
#include <time.h>
#include <stdbool.h>

#include "core.h"

#define baseWait 30000000 //30s

typedef struct {
  int* elements;
  int size;
  int capacity;
} Bucket;

//Überprüfung der Sortierung; inklusive Visualisierung
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

//##### SORTIERALGORITHMEN #####

void bubbleSort(MyAlgorithm* algo, int wait, struct timespec* start) {
    struct timespec end;
    List* list = algo->list;
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

                algo->accesses += 4;
            }
            list->index = i;

            algo->accesses += 1;

            //Zeitmessung
            usleep(wait/10);
            clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
            algo->time = (end.tv_sec - start->tv_sec);
            algo->time += (end.tv_nsec - start->tv_nsec) / 1000000000.0;
        }
        algo->repeats += 1;
    }
}

void selectionSort(MyAlgorithm* algo, int wait, struct timespec* start) {
    struct timespec end;
    List* list = algo->list;
    int n;
    int minIdx;
    int tmp;
    
    n = list->dynLength;
    
    for(int i = 0; i < n - 1; i++) {
        minIdx = i;

        for(int j = i + 1; j < n; j++) {
            if(list->nums[j] < list->nums[minIdx]) {
                minIdx = j;
            }
            algo->accesses += 1;
        }
        tmp = list->nums[i];
        list->nums[i] = list->nums[minIdx];
        list->nums[minIdx] = tmp;
        list->index = minIdx;

        algo->repeats += 1;
        algo->accesses += 4;

        //Zeitmessung
        usleep(wait);
        clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
        algo->time = (end.tv_sec - start->tv_sec);
        algo->time += (end.tv_nsec - start->tv_nsec) / 1000000000.0;
    }
}

void insertionSort(MyAlgorithm* algo, int wait, struct timespec* start) {
    struct timespec end;
    List* list;
    int n;
    
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
            algo->accesses += 3;
            usleep(wait/3);
        }
        list->nums[i] = currElem;

        algo->repeats += 1;
        algo->accesses += 2;

        //Zeitmessung
        usleep(wait/3);
        clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
        algo->time = (end.tv_sec - start->tv_sec);
        algo->time += (end.tv_nsec - start->tv_nsec) / 1000000000.0;
    }
}

void bogoSort(MyAlgorithm* algo, int wait, struct timespec* start) {
    struct timespec end;
    List* list = algo->list;

    checkOrder(list, wait/2);
    algo->accesses += list->dynLength; //Zugriffe in checkOrder; Durchschn.
    if(list->isFinished) return;

    while(true) {
        shuffleNums(list->nums, (list->dynLength));
        checkOrder(list, wait/2);
        if(list->isFinished) {
            break;
        }

        algo->repeats += 1;
        algo->accesses += list->dynLength * 2;

        //Zeitmessung
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

    //durchlaufe sequentiell die einzelnen Gap-Folgen
    //hier wird keine ideale Gap-Sequenz vewendet
    for(int gap = n/2; gap > 0; gap /= 2) {
        for(int i = gap; i < n; i++) {
            int temp = list->nums[i];
            int j = i;

            while (j >= gap && list->nums[j - gap] > temp) {
                list->nums[j] = list->nums[j - gap];
                j -= gap;

                algo->accesses += 2;
            }

            list->nums[j] = temp;
            list->index = j; 

            algo->accesses += 3;

            //Zeitmessung
            usleep(wait/2);
            clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
            algo->time = (end.tv_sec - start->tv_sec);
            algo->time += (end.tv_nsec - start->tv_nsec) / 1000000000.0;
        }
        algo->repeats += 1;

        usleep(wait/2);
    }
}

//Hilfsfunktion zum Heapsort
//stellt einen Heap vom angegebenen Knoten her
//stellt sicher, dass der Heap seine Eigenschaften einhält
void heapify(MyAlgorithm* algo, int n, int i, int wait, struct timespec* start) {
    struct timespec end;
    List* list = algo->list;
    
    int biggestIndex = i; //Index des Elternknotens; größter Index des betrachteten Subbaums
    int leftNodeIndex = 2 * i + 1; //Index des linken Kind-Knotens bestimmen
    int rightNodeIndex = 2 * i + 2; //Index des rechten Kind-Knotens bestimmen
    int* nums = list->nums;
    
    list->index = biggestIndex; 

    //Zeitmessung
    usleep(wait/4);
    clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
    algo->time = (end.tv_sec - start->tv_sec);
    algo->time += (end.tv_nsec - start->tv_nsec) / 1000000000.0;

    if(leftNodeIndex < n && nums[leftNodeIndex] > nums[biggestIndex]) {
        biggestIndex = leftNodeIndex;
    }

    if(rightNodeIndex < n && nums[rightNodeIndex] > nums[biggestIndex]) {
        biggestIndex = rightNodeIndex;
    }

    algo->accesses += 4;

    if(biggestIndex != i) {
        int temp = nums[i];
        nums[i] = nums[biggestIndex];
        nums[biggestIndex] = temp;

        algo->accesses += 4;

        heapify(algo, n, biggestIndex, wait, start);
    }
}

void heapSort(MyAlgorithm* algo, int wait, struct timespec* start) {
    struct timespec end;
    List* list = algo->list;
    int n = list->dynLength;

    //beginne vom letzten möglichen Elternknoten mit Heapify
    for(int i = n/2 - 1; i >= 0; i--) {
        list->index = i; 
        algo->repeats += 1;
        usleep(wait/4);

        heapify(algo, n, i, wait, start);
    }

    //baue finale Liste aus dem Heap auf
    for(int i = n - 1; i > 0; i--) {
        list->index = i; 

        int temp = list->nums[0];
        list->nums[0] = list->nums[i];
        list->nums[i] = temp;

        algo->accesses += 4;

        //Zeitmessung
        clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
        algo->time = (end.tv_sec - start->tv_sec);
        algo->time += (end.tv_nsec - start->tv_nsec) / 1000000000.0;
        usleep(wait/4);

        //Wiederherstellen des Heaps nach Austausch des Elements
        heapify(algo, i, 0, wait, start);
    }
}

//Hilfsfunktion zum Bucketsort
//Initialisiert einen Bucket
void initBucket(Bucket* bucket, int initCapacity) {
    bucket->elements = (int*) malloc(initCapacity * sizeof(int));
    bucket->size = 0;
    bucket->capacity = initCapacity;
}

//Hilfsfunktion zum Bucketsort
//Fügt ein Element zum Bucket hinzu.
void addToBucket(Bucket* bucket, int val) {
    if (bucket->size >= bucket->capacity) {
    bucket->capacity *= 2;
    bucket->elements = (int*) realloc(bucket->elements, 
        bucket->capacity * sizeof(int));
    }
    bucket->elements[bucket->size++] = val;
}

//Hilfsfunktion zum Bucketsort
//Implementierung des Selectionssorts, jedoch mit weniger Parameter für die Anwendung beim
// Sortieren der Buckets
void bucketSelectionSort(int arr[], int n, int wait) {
    for (int i = 0; i < n - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }
        if (minIndex != i) {
            int temp = arr[i];
            arr[i] = arr[minIndex];
            arr[minIndex] = temp;
        }
        usleep(wait/4);
    }
}

void bucketSort(MyAlgorithm* algo, int wait, struct timespec* start) {
    struct timespec end;
    List* list = algo->list;
    
    int idx;
    int n = list->dynLength;
    int bucketNum = sqrt(n); //Anzahl der Buckets basierend auf der Listengröße
    
    Bucket* buckets = (Bucket*)malloc(bucketNum * sizeof(Bucket));

    //Initialisiere alle Buckets
    for(int i = 0; i < bucketNum; ++i) {
        initBucket(&buckets[i], 10);
    }

    //Fülle die Buckets mit den korrespondierenden Elementen der Liste
    for(int i = 0; i < n; ++i) {
        int bucketIdx = (bucketNum * list->nums[i]) / (n-1); //normalisiere Zahlen der Liste für den Bucketindex
        if(bucketIdx >= bucketNum) bucketIdx = bucketNum - 1; //füge zusätzliche Elemente in den letzten Bucket
        addToBucket(&buckets[bucketIdx], list->nums[i]);

        list->index = i;
        algo->accesses += 2; 

        //Zeitmessung
        usleep(wait/4);
        clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
        algo->time = (end.tv_sec - start->tv_sec);
        algo->time += (end.tv_nsec - start->tv_nsec) / 1000000000.0;
    }

    //Sortiere alle Buckets in sich selbst
    for(int i = 0; i < bucketNum; i++) {
        usleep(wait/4);
        if(buckets[i].size > 0) {
            bucketSelectionSort(buckets[i].elements, buckets[i].size, wait);
        }
        algo->repeats += 1;
    }

    //Füge die Elemente aus den Buckets in die Liste ein
    idx = 0;
    for(int i = 0; i < bucketNum; i++) {
        usleep(wait/4);
        for(int j = 0; j < buckets[i].size; j++) {

            list->index = idx; 
            list->nums[idx++] = buckets[i].elements[j];

            algo->accesses += 1;

            //Zeitmessung
            usleep(wait/4);
            clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
            algo->time = (end.tv_sec - start->tv_sec);
            algo->time += (end.tv_nsec - start->tv_nsec) / 1000000000.0;
        }
    }
}

void quickSort(MyAlgorithm* algo, int* arr, int left, int right, int wait, struct timespec* start) {
    struct timespec end;
    clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
    algo->time = (end.tv_sec - start->tv_sec);
    algo->time += (end.tv_nsec - start->tv_nsec) / 1000000000.0;
    algo->repeats += 1;
    if (left < right) {
        int pivot = arr[right];
        algo->accesses += 1;
        algo->list->index = right;
        
        int i = left - 1;
        
        for (int j = left; j < right; j++) {
            algo->list->index = j;
            algo->accesses += 1;
            if (arr[j] <= pivot) {
                i++;
                int temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
                algo->accesses += 3;
            }
        }
        
        int temp = arr[i + 1];
        arr[i + 1] = arr[right];
        arr[right] = temp;
        algo->accesses += 3;   
        
        int pivotIndex = i + 1;
        
        
        usleep(wait);
        quickSort(algo, arr, left, pivotIndex - 1, wait, start);
        quickSort(algo, arr, pivotIndex + 1, right, wait, start);
    }
}

void quickSortWrapper(MyAlgorithm* algo, int wait, struct timespec* start) {
    List* list = algo->list; 
    int* arr = algo->list->nums;  
    int length = list->absLength; 
    
    quickSort(algo, arr, 0, length - 1, wait, start); 
    algo->list->isFinished = true;
}

void merge(MyAlgorithm* algo, int* arr, int left, int mid, int right, int wait, struct timespec* start) {
    struct timespec end;
    algo->repeats += 1;
    usleep(wait);
    
    int n1 = mid - left + 1;
    int n2 = right - mid;

    int leftArr[n1];
    int rightArr[n2];
    algo->accesses += 2;

    int i = 0;
    int j = 0;
    for (i; i < n1; i++) {
        leftArr[i] = arr[left + i];
        algo->list->index = left + i;
        algo->accesses += 2;
    }

    for (j; j < n2; j++) {
        rightArr[j] = arr[mid + 1 + j];
        algo->list->index = mid + 1 + j;
        algo->accesses += 2;
    }

    int k = left;
    i = 0;
    j = 0;
    while (i < n1 && j < n2) {
        algo->accesses += 2;
        if (leftArr[i] <= rightArr[j]) {
            arr[k] = leftArr[i];
            algo->accesses += 2;
            i++;
        } else {
            arr[k] = rightArr[j];
            algo->accesses += 2;
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = leftArr[i];
        algo->accesses += 2;
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = rightArr[j];
        algo->accesses += 2;
        j++;
        k++;
    }
    clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
    algo->time = (end.tv_sec - start->tv_sec);
    algo->time += (end.tv_nsec - start->tv_nsec) / 1000000000.0;
}

void mergeSort(MyAlgorithm* algo, int* arr, int left, int right, int wait, struct timespec* start) {
    struct timespec* end;
    
    if (left < right) {
        int mid = left + (right - left) / 2;

        mergeSort(algo, arr, left, mid, wait, start);
        mergeSort(algo, arr, mid + 1, right, wait, start); 
        merge(algo, arr, left, mid, right, wait, start);
    }
}

void mergeSortWrapper(MyAlgorithm* algo, int wait, struct timespec* start) {
    mergeSort(algo, algo->list->nums, 0, algo->list->absLength - 1, wait, start);

}

void stalinSort(MyAlgorithm* algo, int wait, struct timespec* start) {
    struct timespec end;
    int max = 0;
    int len = algo->list->absLength;
    int itemSize = sizeof(algo->list->nums[0]);
    algo->accesses += 1;
    int* tempArr = calloc(len, itemSize);

    for (int i = 0; i < len; i++) {
        clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
        algo->time = (end.tv_sec - start->tv_sec);
        algo->time += (end.tv_nsec - start->tv_nsec) / 1000000000.0;
        algo->accesses += 1;
        if (algo->list->nums[i] >= max) {
            max = algo->list->nums[i];
            algo->accesses += 1;
        } else {
            //len--;
            algo->list->nums[i] = 0;
            algo->accesses += 1;
        }
        usleep(wait);
        algo->repeats += 1;
    }

    algo->list->isFinished = true;
 
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
        case 7: bucketSort(algo, waitTime, &start); break;
        case 8: quickSortWrapper(algo, waitTime, &start); break;
        case 9: mergeSortWrapper(algo, waitTime, &start); break;
        case 10: stalinSort(algo, waitTime, &start); break;
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

    if (algo->id != 10) checkOrder(algo->list, waitTime);
}