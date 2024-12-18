#include <stdio.h>
#include <stdlib.h>
#include "../misc/hashtable.h"

int compareAsc(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

long part2(char *filename) {
    FILE *pFile = fopen(filename, "r");
    if (pFile == NULL) {
        printf("Unable to read from file, check filename\n");
        return -1;
    }

    char line[256];
    int arr1[1000];
    int counter = 0;
    HashTable *table = ht_initialize(1000); 
    int key;

    while (fgets(line, sizeof(line), pFile) != NULL) {
        if (sscanf(line, "%d %d", &arr1[counter], &key) == 2) {
            ht_insert(table, key);
            counter++;
        }
    }
    fclose(pFile);
    
    long sum = 0;
    for (int i = 0; i < counter; i++) {
        sum += arr1[i] * ht_get_freq(table, arr1[i]);
    }

    ht_free(table); 
    return sum;
}

long part1(char *filename) {
    FILE *pFile = fopen(filename, "r");
    if (pFile == NULL) {
        printf("Unable to read from file, check filename\n");
        return -1;
    }   

    char line[256];
    int arr1[1000];
    int arr2[1000];
    int counter = 0;
    long sum = 0;

    while (fgets(line, sizeof(line), pFile) != NULL) {
        if (sscanf(line, "%d %d", &arr1[counter], &arr2[counter]) == 2) {
            counter++;
        }
    }
    fclose(pFile);

    qsort(arr1, counter, sizeof(int), compareAsc);
    qsort(arr2, counter, sizeof(int), compareAsc);

    for (int i = 0; i < counter; i++) {
        sum += abs(arr1[i] - arr2[i]);
    }
    return sum;
}

int main() {
    char *filename = "./input.txt";
    
    long sum1 = part1(filename);
    if (sum1 != -1) {
        printf("In part1 the total sum is: %ld\n", sum1);
    }

    long sum2 = part2(filename);
    if (sum2 != -1) {
        printf("In part2 the total sum is: %ld\n", sum2);
    }

    return 0;
}
