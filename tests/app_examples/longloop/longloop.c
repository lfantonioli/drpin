#include <stdio.h>


int loop(int n){
  if(n == 0 || n == 1){
    return 1; 
  }
  int i, j, k  = 0;
  unsigned int t = 2;
  for(i = 0; i < n ; i++){
     t += 10 ;
     for(j = 0; j < n; j++){
       t -= 1;
       if (t < 0) {
         return 0;
       }
       for(k = 0; k < n/2; k++){
         t += 1;
         if (t < 0) {
           return 0;
         }
       }
     }
  }
  return t;
}

int main(int argc, char const *argv[])
{
    int n = 1000;
    int loop_n = loop(n);
    printf("longloop(%d) = %d\n", n, loop_n);

    return 0;
}

