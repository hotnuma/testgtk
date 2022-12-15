
// gcc -g -O0 -o test_valgrind test_valgrind.c
// valgrind --leak-check=yes ./test_valgrind 

#include <stdlib.h>

void func(void)
{
    int *x = malloc(10 * sizeof(int));
    x[10] = 0;
    
    // problem 1: heap block overrun
    // problem 2: memory leak -- x not freed
}

int main(void)
{
    func();
    return 0;
}


