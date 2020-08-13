#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <sys/time.h>

#define size 20

long getMicrotime(){
	struct timeval currentTime;
	gettimeofday(&currentTime, NULL);
	return currentTime.tv_sec * (int)1e6 + currentTime.tv_usec;
}

int func0(int a){
  return a * 2;
}

int func1(int b){
  int c = b;
  int d = c - 2;
  int i = 0;
  if (b < 0) {
    b += 20;
  }
  for (i = 0; i < b; i ++){
    b + i - d;
  }
}

int func2(int b){
  return 4*(b -1);
}

int func3(int b){
  b = b - 10;
  return --b;
}

int main() {
    int i = 0;
    long fn_of_time = getMicrotime() + time(NULL);
    srand(fn_of_time); // randomize seed
    printf("%d\n", fn_of_time);
    int value = 1;

    for(i=0;i<size;i++){
        int chosen = rand()%4;
        if (chosen == 0){
            value = func0(value);
        } else if (chosen == 1){
            value = func1(value);
        } else if (chosen == 2){
            value = func2(value);
        } else if (chosen == 3){
            value = func3(value);
        }
    }
    printf("Final value: %d\n", value);

    return 0;
}


