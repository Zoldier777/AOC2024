#include <stdio.h> 
#include <stdlib.h>
#include <stdbool.h>
#define EXAMPLE 1 // wc example.txt = 19
#if EXAMPLE
    #define FNAME "./example.txt"
    #define N 19 
#else 
    #define FNAME  "./input.txt"
    #define N 19999
#endif

typedef struct block {
     int id, size;
} Block;
    
static char s[N]; 

int main() {
    // read values from file and store in buffer
    Block blocks[N];

    FILE *f = fopen(FNAME, "rb");
    if (!f)
    {
        fputs("File not found.\n", stderr);
        return 1;
    }
    fread(s, sizeof s, 1, f);
    fclose(f);
    // setup each block
    for(int i = 0, pos = 0;  i < N; i++)
    {    
        blocks[i] = (Block){!(i & 1) ? pos++ : 0, s[i] & 15};
    }
    // two pointer  
    int left = 1, right = N-1; //skip first 0 id block because no contribution to checksum. 
    int checksum = 0, idx = blocks[left-1].size;
    while(left < right) {
        if(blocks[left].id != 0) {
            while(blocks[left].size > 0) {
                checksum += idx++ * blocks[left].id;
                blocks[left].size--;  
            }
            left++;
        } 
        else {
            while(blocks[left].size > 0) {  
                while(blocks[right].size == 0 || blocks[right].id == 0) {  
                    right--;
                    if(right <= left)
                        goto skip;
                 }
                checksum += idx++ * blocks[right].id;
                blocks[left].size--;  
                blocks[right].size--;  
            }

        }
        skip:;
    }
    printf("sum1: %d", checksum);
    return 0;
}