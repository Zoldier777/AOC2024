#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

// #define FNAME "./example.txt"
// #define UPDATES 6
// #define MAXPAGESIZE 5

#define FNAME "./input.txt"
#define UPDATES 217
#define MAXPAGESIZE 23

static int ruleset[100][100];
static int page[UPDATES][MAXPAGESIZE];
static int pagelength[UPDATES];

static inline int num(const char *const s)
{
    return (*s & 15) * 10 + (*(s + 1) & 15);
}

static int cmp_pos(const void *a, const void *b)
{
    const int val1 = *(const int *)a;
    const int val2 = *(const int *)b;

    if (ruleset[val1][val2]) return -1;  
    if (ruleset[val2][val1]) return  1;  
    return 0;  
}

int main() {
    FILE *f = fopen(FNAME, "r");
    if (!f) {
        fputs("File not found.\n", stderr);
        return 1;
    }
    char buffer[BUFSIZ];
    for(int i=0; fgets(buffer,sizeof(buffer),f); ) {
        // line end
        if(buffer[0] == '\n')
            continue;
        // add rule 
        if(buffer[2] == '|') {
            ruleset[num(buffer)][num(buffer+3)] = true; // a < b logical ordering
       }
        // setup page ordering
        else {
            int n = 0;
            for(const char *s = buffer; *s; s+=3)
                page[i][n++] = num(s);
            pagelength[i++] = n;
        }
    }

    fclose(f);

    int sum = 0, sum2 = 0;
    
    for(int i = 0; i < UPDATES; ++i) {
        for(int j = 1; j < pagelength[i]; ++j) 
            if(ruleset[ page[i][j]][ page[i][j-1]] ) {
                qsort(&page[i][0], pagelength[i], sizeof(int), cmp_pos); 
                sum2 += page[i][pagelength[i] >> 1];
                goto skip_i; // valid case for goto since nested loop and skipping use of flag to validate before incrementing sum
            }
      
            sum += page[i][pagelength[i] >> 1];
            skip_i:;
    }    
      
    printf("part1: %d part2: %d\n", sum, sum2); //6034 //6305
    return 0;
}
