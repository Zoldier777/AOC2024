#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

// Updated is_safe_report to take size explicitly
bool is_safe_report(int *report, int size)
{
    bool increasing = true, decreasing = true;

    for (int i = 0; i < size - 1; i++)
    {
        int dif = report[i] - report[i + 1];

        if (dif <= 0)
        {
            increasing = false;
        }
        if (dif >= 0)
        {
            decreasing = false;
        }
        if (abs(dif) < 1 || abs(dif) > 3)
        {
            return false;
        }
    }

    return (increasing || decreasing);
}

// Updated remove_index to use size explicitly
int *remove_index(int *array, int size, int index)
{
    if (index < 0 || index >= size)
    {
        fprintf(stderr, "Index out of bounds\n");
        return NULL;
    }

    int *new_array = malloc((size - 1) * sizeof(int));
    if (!new_array)
    {
        perror("Failed to allocate memory");
        exit(EXIT_FAILURE);
    }

    int j = 0;
    for (int i = 0; i < size; i++)
    {
        if (i != index)
        {
            new_array[j++] = array[i];
        }
    }

    return new_array;
}

// Updated is_safe_without to take size explicitly
bool is_safe_without(int *values, int size, int i)
{
    int *modified_values = remove_index(values, size, i);
    bool result = is_safe_report(modified_values, size - 1);
    free(modified_values); // Free the allocated memory
    return result;
}

// No changes to part1
int part1(char *filename)
{
    FILE *pFile = fopen(filename, "r");
    char line[256];
    int counter = 0;

    while (fgets(line, sizeof(line), pFile) != NULL)
    {
        int values[256];
        int size = 0;

        char *token = strtok(line, " ");
        while (token != NULL)
        {
            values[size++] = atoi(token);
            token = strtok(NULL, " ");
        }

        if (is_safe_report(values, size))
        {
            counter++;
        }
    }

    fclose(pFile);
    return counter;
}

// Updated part2 to fix size usage
int part2(char *filename)
{
    FILE *pFile = fopen(filename, "r");
    char line[256];
    int counter = 0;

    while (fgets(line, sizeof(line), pFile) != NULL)
    {
        int values[256];
        int size = 0;

        char *token = strtok(line, " ");
        while (token != NULL)
        {
            values[size++] = atoi(token);
            token = strtok(NULL, " ");
        }

        bool state = false;
        state |= is_safe_without(values, size, 0);
        for (int i = 0; i < size - 1; i++)
        {
            int diff = values[i] - values[i + 1];

            if (abs(diff) < 1 || abs(diff) > 3)
            {
                state |= is_safe_without(values, size, i);
                state |= is_safe_without(values, size, i + 1);
                break;
            }
            if (i + 2 < size)
            {
                int next_diff = values[i + 1] - values[i + 2];
                if ((next_diff > 0) != (diff > 0))
                {
                    state |= is_safe_without(values, size, i);
                    state |= is_safe_without(values, size, i + 1);
                    state |= is_safe_without(values, size, i + 2);
                    break;
                }
            }
        }
        if (state || is_safe_report(values, size))
        {
            counter++;
        }
    }

    fclose(pFile);
    return counter;
}

int main()
{
    char *filename = "./input.txt";
    printf("In part1 the total sum is: %d\n", part1(filename));
    printf("In part2 the total sum is: %d\n", part2(filename));
    return 0;
}
