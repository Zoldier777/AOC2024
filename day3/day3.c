#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define FNAME "./input.txt"
#define FSIZE (5 << 12)
#define MUL 0x286C756D // "mul(" 
#define DO   0x29286f64  // "do()"
#define DON  0x276e6f64  // "don'"
#define T 0x00292874  // "t()"

static char input[FSIZE];

static int isNum(const char **const c)
{
    int val = 0;
    while (**c >= '0' && **c <= '9')
    {
        val = val * 10 + (*(*c)++ & 15);
    }
    return val;
}

static int doubles(const char **const c)
{
    const int num1 = isNum(c);
    if (!num1 || **c != ',')
    {
        return 0;
    }
    ++(*c);
    const int num2 = isNum(c);
    if (!num2 || **c != ')')
    {
        return 0;
    }
    ++(*c);
    return num1 * num2;
}

int main(void)
{

    FILE *f = fopen(FNAME, "rb");
    if (!f)
    {
        fputs("File not found.\n", stderr);
        return 1;
    }
    fread(input, sizeof input, 1, f);
    fclose(f);

    int sum = 0,sum2 = 0, val;
    bool allow = true;

    for (const char *c = input; *c;)
    {
        switch (*(int *)c) {

        case MUL:
            c += 4;
            if ((val = doubles(&c)))
            {
                sum += val;
                sum2 += allow * val;
            }
            break;
        case DO:
            c += 4;
            allow = true;
            break;
        case DON:
            c += 4;
            if( (*(int *)c & 0x00FFFFFF) == T) { // Mask to ignore MSB
                allow = false;  
            }
            c += 3;
            break;

        default:
            c++;
        }
    }
    printf("sum1 is %d\n sum2 is %d\n", sum, sum2); // 155955228 //100189366  

    return 0;
}
