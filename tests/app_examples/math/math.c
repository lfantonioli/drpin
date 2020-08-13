#include <stdio.h>
#include "foo.h"
#include "complex.h"
 
int main(void)
{
    puts("This is a multi c file program test");
    foo();
    int k = complex_operation(10, 32);
    printf("Result: %d\n", k);
    return 0;
}
