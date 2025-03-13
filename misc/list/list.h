#ifndef LIST_H
#define LIST_H

#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>

// Define callback types for free and compare operations
typedef void (*CallbackFree)(void *);                // Callback for freeing data
typedef int (*CallbackCompare)(void *a, void *b);    // Callback for comparing data


// Define Node structure for linked list
typedef struct _node {
    void *data;           // Data can be of any type (void pointer)
    struct _node *next;   // Pointer to next node
} Node;

// Define List structure for the linked list
typedef struct {
    int count;            // Number of nodes in the list
    int data_size;        // Size of data held in each node
    Node *head;           // Pointer to the first node
    Node *tail;           // Pointer to the last node
    CallbackFree callback_free;      // Callback to free data
    CallbackCompare callback_compare;  // Callback to compare data
} List;
// Define callback for list iteration functions
// The iteration will break if it returns false
typedef bool (*CallbackIterate)(int index, Node *node);

// Function declarations
List* list_create(int dataSize, CallbackFree free_callback, CallbackCompare compare_callback);
void list_destroy(List *list);
void list_add(List *list, void *data);
void list_remove(List *list, int index);
bool list_contains(List *list, void *data);
Node* list_find(List *list, void *data);
Node* list_get_node(List *list, int index);
void* list_get_data(List *list, int index);
void list_iterate(List *list, CallbackIterate iterate_callback);
// Utility function to free node data based on provided callback
void free_node_data(CallbackFree free_callback, void *data);


#endif // LIST_H
