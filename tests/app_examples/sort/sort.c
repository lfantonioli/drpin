#include <stdio.h>

void display(int *array, int size) {
   int i = 0;
   for(i = 0; i<size; i++)
     printf("%d ", array[i]);
   printf("\n");
}

void bubble_sort (int *a, int n) {
    int i, t, j = n, s = 1;
    while (s) {
        s = 0;
        for (i = 1; i < j; i++) {
            if (a[i] < a[i - 1]) {
                t = a[i];
                a[i] = a[i - 1];
                a[i - 1] = t;
                s = 1;
            }
        }
        j--;
    }
}

int main(int argc, char const *argv[])
{
    int arr[10] = {581, 549, 651, 738, 72, 363, 980, 345, 204, 826};

    printf("Array before Sorting: ");
    display(arr, 10);

    bubble_sort(arr, 10); 

    printf("Array after Sorting: ");
    display(arr, 10);

    return 0;
}

