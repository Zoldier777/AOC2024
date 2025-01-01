#include <stdio.h>
#include <stdbool.h>
#include <string.h>

// switch between testfile and input file. 
#define EXAMPLE 0
#if EXAMPLE
    #define FNAME "./example.txt" 
    #define N 10
#else
    #define FNAME "./input.txt"
    #define N 130
#endif

#define FSIZE N + 1


typedef enum directions { UP, RIGHT, DOWN, LEFT } Direction;

typedef struct pos {
    int y; 
    int x;
} Pos;

static const Pos step[] = {{-1,0}, {0,1}, {1,0}, {0,-1}};
// one addional line of newline char
static char grid[N][N+1];
// 4 bit represenatation of positon that has been visisted from which direction UP/RIGHT/DOWN/LEFT -> 0001/0010/0100/1000.
static char hist[N][N];

static Pos go(Pos pos, const Direction dir) {
    return (Pos){pos.y += step[dir].y, pos.x += step[dir].x};
}

static bool inbounds(const Pos pos) {
    return pos.x >= 0 && pos.x < N && pos.y >= 0 && pos.y < N;
}

static char look(Pos pos){
   return grid[pos.y][pos.x];
}

static Direction turn(const Direction dir)
{
    return (dir + 1) & 3;
}

static void sethist(const Pos pos, const Direction dir)
{
    hist[pos.y][pos.x] |= (1 << dir);
}

static bool isdupe(const Pos pos, const Direction dir)
{
     return hist[pos.y][pos.x] & (1 << dir);
}

static bool save(const Pos pos, const Direction dir)
{
    const bool isnew = !hist[pos.y][pos.x];
    sethist(pos, dir);
    return isnew;
}

// loop for finding counter until gaurd leaves the arena
static int walk(Pos pos, Direction dir) {
    int visited = 0;
    Pos next;
    while (inbounds((next = go(pos, dir))))
    {
        if(look(next) != '#')
        {
            visited += save(pos,dir);
            pos = next;
        }
        else {
            dir = turn(dir);
        }
    }
    visited += save(pos, dir);  
    return visited;
}
static bool hasLoop(Pos pos, Direction dir)
{
    memset(hist, 0, sizeof hist); //reset hist at the start
    Pos next;
    
    while (inbounds((next = go(pos, dir))))
        if (look(next) != '#') {
            if (isdupe(pos, dir)) //loop condition satisified when a positon is about to be visited again with same direction. 
                return true;
            sethist(pos, dir);
            pos = next;
        } else
            dir = turn(dir);  
    return false;
}



int main() {
    FILE *f = fopen(FNAME, "rb");
    if (!f) {
        fputs("File not found.\n", stderr);
        return 1;
    }
    fread(grid, sizeof grid, 1, f);
    fclose(f);

    #if EXAMPLE
        Pos pos = {6, 4};
    #else
        Pos pos = {52,72}; // hardcoded starting position... beautiful right? :D 
    #endif
    Direction dir = UP;

    printf("Part 1: %d\n", walk(pos, dir));  //4977
    
    int loops = 0; //bruteforce every position that isn't '#' and can be '#' and check for potential loop
    for (int i = 0; i < N; i++)
        for(int j = 0; j < N; j++)
            if(grid[i][j] != '#'){
                grid[i][j] = '#';
                loops += hasLoop(pos,dir);
                grid[i][j] = '.';
            }
    printf("Part 2: %d\n", loops);  //1729

    return 0;


}
