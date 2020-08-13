#include <stdio.h>


int factorial(int n){
  if(n == 0 || n == 1){
    return 1; 
  }
  return n * factorial(n-1);
}

int main(int argc, char const *argv[])
{
    int n = 4;
    int fac_n = factorial(n);
    printf("%d! = %d\n", n, fac_n);

    return 0;
}

