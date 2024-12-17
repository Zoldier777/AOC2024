#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <stdlib.h>

// Node in the hash table
typedef struct HashNode {
    int key;                 // Key
    int count;               // Frequency
    struct HashNode* next;   // Pointer for collision handling
} HashNode;

typedef struct HashTable {
    HashNode** buckets; // Array of pointers to HashNode (the buckets)
    size_t size;        // Size of the table
} HashTable;

HashTable* ht_initialize(size_t size);   // Create a new hash table
void ht_insert(HashTable* table, int key); // Insert a key or update its frequency
int ht_get_freq(HashTable* table, int key); // Get frequency of a key
void ht_free(HashTable* table);          // Free the hash table

#endif
