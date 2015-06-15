# Data_manager
### 1. Run cppcheck
cppcheck cppcheck --enable=all --suppress=missingIncludeSystem main.c datamgr.c datamgr.h
### 2. Compile with shared library
gcc -Wall -Werror main.c datamgr.c -L. -Wl,-rpath=. -llist
### 3. Check memory leaks
valgrind --tool=memcheck --leak-check=yes ./a.out
