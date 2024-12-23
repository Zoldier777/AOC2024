# AOC2024

This is my attempt at 2024 advent of code challanges using C.

## Project Structure

- `dayX/`: Each day has its own folder (e.g., `day1/`, `day2/`) containing:
  - A source file for the main program logic (e.g., `day1.c`).
  - Input data for the task (e.g., `input.txt`).
- `misc/`: Contains shared libraries and structures, such as:
  - `libraryX.c` (e.g., `hashtable.c`): Implementation of shared functionality.
  - `libraryX.h` (e.g., `hashtable.h`): Declarations for the shared library.

## Steps to Compile and Link

Ensure that your files are properly structured, with source files (e.g., `day1.c`, `hashtable.c`) and header files (e.g., `hashtable.h`) in appropriate directories.

For example:

```bash
gcc -c misc/hashtable.c -o misc/hashtable.o
gcc -o day1 day1.c ../misc/hashtable.o
./day1
```

