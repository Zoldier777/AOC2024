#include "arr.h"

void initDynamicArr(DynamicArr *arr, size_t size) {
    arr->array = malloc(size * sizeof(int));
    arr->used = 0;
    arr->size = size;
}

void insertDyanmicArr(DynamicArr *arr, int element) {

    if(arr->used == arr->size) {
        arr->size *= 2; // default behvaior is to double when out of space
        arr->array = realloc(arr->array, arr->size * sizeof(int));
    }
    arr->array[arr->used++] = element;
}

void freeDynamicArr(DynamicArr *arr) { 
    free(arr->array);
    //cleanup
    arr->array = NULL;
    arr->used = 0;
}

