#include <stdio.h>
#include <string.h>

#define FNAME "./input.txt"
#define R 140     // file rows
#define C (R + 1) // file cols
#define MAS (('M' + 'S') * 2)
static char grid[R][C];

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

    int sum = 0;
    for (int r = 0; r < R; r++)
        for (int c = 0; c < C; c++)
            if (grid[r][c] == 'X')
            {
                // verical
                sum += (r + 3 < R) && (grid[r + 1][c] == 'M' && grid[r + 2][c] == 'A' && grid[r + 3][c] == 'S'); // Down
                sum += (r > 2) && (grid[r - 1][c] == 'M' && grid[r - 2][c] == 'A' && grid[r - 3][c] == 'S');     // Up
                // horizontal
                sum += (c + 3 < C) && (grid[r][c + 1] == 'M' && grid[r][c + 2] == 'A' && grid[r][c + 3] == 'S'); // Right
                sum += (c > 2) && (grid[r][c - 1] == 'M' && grid[r][c - 2] == 'A' && grid[r][c - 3] == 'S');     // Left
                // diagonal
                sum += (r + 3 < R && c + 3 < C) && (grid[r + 1][c + 1] == 'M' && grid[r + 2][c + 2] == 'A' && grid[r + 3][c + 3] == 'S'); // Down-Right
                sum += (r + 3 < R && c > 2) && (grid[r + 1][c -1] == 'M' && grid[r + 2][c - 2] == 'A' && grid[r + 3][c - 3] == 'S');     // Down-Left
                sum += r > 2 && c > 2 && (grid[r - 1][c - 1] == 'M' && grid[r - 2][c - 2] == 'A' && grid[r - 3][c - 3] == 'S');   // Up-Left 
                sum += r > 2 && c + 3 < C && (grid[r - 1][c + 1] == 'M' && grid[r - 2][c + 2] == 'A' && grid[r - 3][c + 3] == 'S');  //Up-Right
            }
    printf("total sum for part1 is: %d", sum); //2644   
    sum = 0;
     for (int r = 0; r < R; r++)
        for (int c = 0; c < C; c++)
            if (grid[r][c] == 'A') {
                sum += (grid[r-1][c-1] + grid[r-1][c+1] + grid[r+1][c-1] + grid[r+1][c+1]) == MAS && grid[r-1][c-1] != grid[r+1][c+1];           
            }
    printf("total sum for part2 is: %d", sum); //1952
    
    return 1;
}
