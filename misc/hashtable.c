#include "hashtable.h"
#include <stdio.h>
#include <string.h>

static size_t hash_function(int key, size_t size) {
    return (size_t)(key % size);
}

HashTable* ht_initialize(size_t size) {
    HashTable* table = (HashTable*)malloc(sizeof(HashTable));
    table->buckets = (HashNode**)calloc(size, sizeof(HashNode*));
    table->size = size;
    return table;
}

void ht_insert(HashTable* table, int key) {
    size_t index = hash_function(key, table->size);
    HashNode* node = table->buckets[index];

    while (node != NULL) {
        if (node->key == key) {
            node->count++;
            return;
        }
        node = node->next;
    }

    // Key not found, create a new node
    HashNode* new_node = (HashNode*)malloc(sizeof(HashNode));
    new_node->key = key;
    new_node->count = 1;
    new_node->next = table->buckets[index];
    table->buckets[index] = new_node;
}

int ht_get_freq(HashTable* table, int key) {
    size_t index = hash_function(key, table->size);
    HashNode* node = table->buckets[index];

    while (node != NULL) {
        if (node->key == key) {
            return node->count;
        }
        node = node->next;
    }

    return 0; 
}

void ht_free(HashTable* table) {
    for (size_t i = 0; i < table->size; i++) {
        HashNode* node = table->buckets[i];
        while (node != NULL) {
            HashNode* temp = node;
            node = node->next;
            free(temp);
        }
    }
    free(table->buckets);
    free(table);
}
