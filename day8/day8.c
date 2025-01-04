#include <stdio.h>
#include <stdbool.h>

#define EXAMPLE 0
#if EXAMPLE
    #define FNAME "./example.txt"
    #define N 12
#else
    #define FNAME "./input.txt" 
    #define N 50
#endif

#define NUM ('9' - '0' + 1)  // 10
#define LET ('Z' - 'A' + 1)  // 26
#define FRQ (NUM + (2 * LET))  // Lower and uppercase set of letters as well as nums
#define MAXNUMS 4
#define DOT '.'

typedef struct pos {
    int y, x;
} Pos;

typedef struct antenna {
    int count; // current amount of positions being used count < Maxnums always
    Pos pos[MAXNUMS]; 
} Antenna;


static char grid[N][N+1]; // data is given N*N size
static Antenna antenna_map[FRQ]; // 2d array with hashing to map freq to to correct set of antennas.
static bool antinode[N][N]; //history to track where antinodes have been placed.

static bool inbounds(const Pos pos) {
    return pos.x >= 0 && pos.x < N && pos.y >= 0 && pos.y < N;
}

static int hash(char const* c) { //hashspace is 0-9A-Z-a-z 0-62 pos. 
    if(*c <= '9' )
        return *c & 15; 
    if(*c <= 'Z') 
        return  *c - 'A' + NUM; 
    return *c - 'a' + (NUM + LET); 
}

static Pos dif(const Pos a, const Pos b)
{
    return (Pos){a.y - b.y, a.x - b.x};
}

static Pos add(const Pos a, const Pos b)
{
    return (Pos){a.y + b.y, a.x + b.x};
}


int main() {
    FILE *f = fopen(FNAME, "rb");
    if (!f) {
        fputs("File not found.\n", stderr);
        return 1;
    }
    fread(grid, sizeof grid, 1, f);
    fclose(f);

    // map antennas to correct freq O(N²)
    for(int y = 0; y < N; y++) {
        for(int x = 0; x < N; x++) {
            if(grid[y][x] != DOT){
                Antenna *const a = &antenna_map[hash(&grid[y][x])];
                a->pos[a->count++] = (Pos){y,x};                
            }
        }
    }

    int sum = 0; // assuming N < sqrt(MAXINT)
    for(int frq = 0; frq < FRQ; frq++) {
        Antenna *const a = &antenna_map[frq];
        for(int i = 0; i < a->count; i++) {
            for(int j = i+1; j < a->count; j++) {
                Pos offset = dif(a->pos[i], a->pos[j]); // find the offset where the new antinode should be placed which''ll then be twice the distance going from x->y. 
                
                Pos antinode_yx = add(a->pos[i],offset);
                if(inbounds(antinode_yx))
                    if(!antinode[antinode_yx.y][antinode_yx.x]){
                        antinode[antinode_yx.y][antinode_yx.x] = true;
                        sum++;
                    }
                Pos antinode_xy = add(a->pos[j],(Pos){-1 * offset.y, -1 * offset.x});
                    if(inbounds(antinode_xy))
                        if(!antinode[antinode_xy.y][antinode_xy.x]){
                            antinode[antinode_xy.y][antinode_xy.x] = true;
                            sum++;
                        }
                                    
            }
        }
    }
    printf("sum1: %d\n", sum); //390

    return 0;
}