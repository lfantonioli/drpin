#include <stdlib.h>
#include <time.h>
#include <stdio.h>

#define size 10

int main() {
    int i = 0;
    srand(time(NULL)); // randomize seed

    int Arr[size];

    for(i=0;i<size;i++){
        Arr[i] = rand()%10000;
    }

    for(i=0;i<size;i++){
        printf("Random: %d\n", Arr[i]);
    }

    return 0;
}


