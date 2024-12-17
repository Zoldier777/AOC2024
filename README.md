# AOC2024

In this structure:
- `dayX.c` contains the main program logic for the specific day (e.g., `day1.c`, `day2.c`).
- `libraryX.c` contains the implementation of a library that provides additional functionality (e.g., `hashtable.c` for hash table operations).
- `libraryX.h` contains the declarations for the library functions and types (e.g., the interface to the hash table functions).

## Steps to Compile and Link
Ensure that your files are properly structured, with source files (e.g., `day1.c`, `hashtable.c`) and header files (e.g., `hashtable.h`) in appropriate directories.

For example:

```bash
gcc -c misc/hashtable.c -o misc/hashtable.o
gcc -o day1 day1.c misc/hashtable.o
./day1
```