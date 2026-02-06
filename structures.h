#ifndef STRUCTURES_H
#define STRUCTURES_H


#include <stdbool.h>


typedef struct {
    int x;
    int y;
    int width;
    int height;
} Box;

typedef struct {
    int dynLength;
    int absLength;
    int *nums;
    int index;
    bool isFinished;
} List;

#endif