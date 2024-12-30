#ifndef ARR_H 
#define ARR_H

#include <stdlib.h>

typedef struct DynamicArr {
    int *array;
    size_t size;
    size_t used;
} DynamicArr;
    
void initDynamicArr(DynamicArr *arr, size_t size);
void insertDyanmicArr(DynamicArr *arr, int element);
void freeDynamicArr(DynamicArr *arr);

#endif