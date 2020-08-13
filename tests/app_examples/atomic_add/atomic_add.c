#include <stdio.h>


int main(int argc, char const *argv[])
{
    int a = 4;
    int b = 200;
    __sync_fetch_and_add( &a, b );
    printf("value = %d\n", a);

    return 0;
}

