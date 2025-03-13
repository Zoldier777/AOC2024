#include <stdio.h> 
#include <stdlib.h>
#include <stdbool.h>
#include "../misc/list/list.h"

#define EXAMPLE 1 // wc example.txt = 19
#if EXAMPLE
    #define FNAME "./example.txt"
    #define N 19 
#else 
    #define FNAME  "./input.txt"
    #define N 19999
#endif

typedef struct block {
     int value, size;
} Block;
    
static char s[N]; 

int main() {
    // read values from file and store in buffer

    FILE *f = fopen(FNAME, "rb");
    if (!f)
    {
        fputs("File not found.\n", stderr);
        return 1;
    }
    fread(s, sizeof s, 1, f);
    fclose(f);
    
    List* blocklist =  list_create(sizeof(Block),NULL,NULL);
    // setup each block
    for(int i = 0, pos = 0;  i < N; i++)
    {    
        Block b = { !(i & 1) ? pos++ : 0, s[i] & 15};
        list_add(blocklist,&b);
    }
    

    return 0;
}