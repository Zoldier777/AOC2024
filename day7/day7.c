#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <inttypes.h>  // PRId64

#define EXAMPLE 0
#if EXAMPLE
    #define FNAME "./example.txt"
    #define N 9
#else 
    #define FNAME "./input.txt"
    #define N 850
#endif

#define MAXNUMS 12 // left side of equation max number of values.

typedef struct equation {
    int64_t sum; // big nums in input avoid overflow
    int count;
    int nums[MAXNUMS];
    int conc_mask[MAXNUMS]; // to 486 see if 6 exist inside we divide by 10 and then 48 and check if 6 is the reminder 
} Equation;

static Equation equations[N];

static int masks[] = {10, 100, 1000};

static void parser(Equation *const eq, const char *s ) {
    int64_t sum = 0;
    do { //none of the line is empty before ':' hence do while
        sum = sum * 10 + (*s++ & 15);
    } while (*s != ':');
    ++s;
    eq->sum = sum;
    int n = 0;
    for(; *s++ == ' '; n++) { // step to next value separated by space
        int nums = *s++ & 15;
        int len = 0;
        for(; *s >= '0' && *s <= '9'; len++) // validate and append value
            nums = (nums * 10) + (*s++ & 15);
        eq->nums[n] = nums;
        eq->conc_mask[n] = masks[len];
    }
    eq->count = n;

  
}   
// recursive call all possiblities by branching by 2 subtract/divide sum 
    static bool solve(const Equation *const eq, const int numi, const int64_t res, const bool part2) {
    // base case compare last number with the sum should be equal
    if(numi == 0){
       return res == eq->nums[0]; 
    }
    // addition 
    if(res > eq->nums[numi] && solve(eq, numi-1, res-eq->nums[numi], part2) )
        return true;
    // multiplication 
    lldiv_t dv = lldiv(res, eq->nums[numi]);
    if(!dv.rem && solve(eq, numi-1, dv.quot, part2))
        return true;
    
    // third operator from part 2 concatenation
    if(part2){  
        lldiv_t dv = lldiv(res, eq->conc_mask[numi]);
        if(dv.rem == eq->nums[numi] && solve(eq, numi-1, dv.quot, part2))
            return true;
    }

    return false;
}



int main() {
    FILE *f = fopen(FNAME, "r");
    if (!f) {
        fputs("File not found.\n", stderr);
        return 1;
    }
    char buffer[256];
    // read in file and parse each line
    for(int i = 0; i < N && fgets(buffer,sizeof buffer, f);)
        parser(&equations[i++],buffer);    
    fclose(f);
    
    int64_t sum = 0, sum2 = 0;
    for(int i = 0; i < N; i++)
    {
        Equation *const equation = &equations[i]; 
        if(solve(equation,equation->count-1, equation->sum, false)) {
            sum += equation->sum;
        } //if it could not be solved with just mult and addition try with concatentaion as well. 
        else if(solve(equation, equation->count-1, equation->sum, true)) 
            sum2 += equation->sum;
    }
    printf("%"PRId64"\n", sum);  //8401132154762
    printf("%"PRId64"\n", sum2+sum); //95297119227552
    return 0;

}