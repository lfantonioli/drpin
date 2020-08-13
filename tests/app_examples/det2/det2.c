#include <stdio.h>

/* void display(int *array, int size) { */
/*    for(int i = 0; i<size; i++) */
/*      printf("%d ", array[i]); */
/*    printf("\n"); */
/* } */

int det2 (int *array) {
  int a = array[0];
  int b = array[1];
  int c = array[2];
  int d = array[3];
  return a*d - b*c;

}

int main(int argc, char const *argv[])
{
    int arr[4] = {4, 6, 3, 8};

    int determinant = det2(arr);
    printf("The determinant is: %d\n", determinant);

    return 0;
}

