# Data_manager
### 1. Run cppcheck
cppcheck --enable=all --suppress=missingIncludeSystem main.c datamgr.c datamgr.h
### 2. Compile with shared library
gcc -Wall -Werror -DSET_MIN_TEMP=20 -DSET_MAX_TEMP=25 main.c datamgr.c -L. -Wl,-rpath=. -llist
### 3. Check memory leaks
valgrind --tool=memcheck --leak-check=yes ./a.out
