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

#define NUM ('9' - '0' + 1)   // 10
#define LET ('Z' - 'A' + 1)   // 26
#define FRQ (NUM + (2 * LET)) // Lower and uppercase set of letters as well as nums
#define MAXNUMS 4
#define DOT '.'

typedef struct pos
{
    int y, x;
} Pos;

typedef struct antenna
{
    int count; // current amount of positions being used count < Maxnums always
    Pos pos[MAXNUMS];
} Antenna;

static char grid[N][N + 1];      // data is given N*N size
static Antenna antenna_map[FRQ]; // 2d array with hashing to map freq to to correct set of antennas.
static bool antinode[2][N][N];   // history to track where antinodes have been placed.

static bool inbounds(const Pos pos)
{
    return pos.x >= 0 && pos.x < N && pos.y >= 0 && pos.y < N;
}

static int hash(char const *c)
{ // hashspace is 0-9A-Z-a-z 0-62 pos.
    if (*c <= '9')
        return *c & 15;
    if (*c <= 'Z')
        return *c - 'A' + NUM;
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

static Pos sub(const Pos a, const Pos b)
{
    return (Pos){a.y - b.y, a.x - b.x};
}

static int sumgrid(const void *const a)
{
    int sum = 0;
    for (int i = 0; i < N * N; ++i)
        sum += ((const bool *const)a)[i];
    return sum;
}

int main()
{
    FILE *f = fopen(FNAME, "rb");
    if (!f)
    {
        fputs("File not found.\n", stderr);
        return 1;
    }
    fread(grid, sizeof grid, 1, f);
    fclose(f);

    // map antennas to correct freq O(N²)
    for (int y = 0; y < N; y++)
    {
        for (int x = 0; x < N; x++)
        {
            if (grid[y][x] != DOT)
            {
                Antenna *const a = &antenna_map[hash(&grid[y][x])];
                a->pos[a->count++] = (Pos){y, x};
                antinode[1][y][x] = true; // only works if frq happens at least twice(which does so for my input) otherwise need to add a sanity check,
            }
        }
    }
    // 
    for (int frq = 0; frq < FRQ; frq++)
    {
        Antenna *const a = &antenna_map[frq];
        for (int i = 0; i < a->count; i++)
            for (int j = i + 1; j < a->count; j++)
            {
                Pos offset = dif(a->pos[i], a->pos[j]); // find the offset where the new antinode should be placed which''ll then be twice the distance going from x->y.

                Pos pos = add(a->pos[i], offset);
                if (inbounds(pos))
                {
                    antinode[0][pos.y][pos.x] = true;
                    do
                    {
                        antinode[1][pos.y][pos.x] = true;
                        pos = add(pos, offset);
                    } while (inbounds(pos));
                }

                pos = sub(a->pos[j], offset);
                if (inbounds(pos))
                {
                    antinode[0][pos.y][pos.x] = true;
                    do
                    {
                        antinode[1][pos.y][pos.x] = true;
                        pos = sub(pos, offset);
                    } while (inbounds(pos));
                }
            }
    }
    printf("sum1: %d\n", sumgrid(antinode[0])); // 390
    printf("sum2 %d\n", sumgrid(antinode[1])); // 1246
    return 0;
}