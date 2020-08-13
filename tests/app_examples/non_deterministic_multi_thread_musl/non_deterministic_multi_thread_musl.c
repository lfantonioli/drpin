#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <sys/time.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_THREADS 5

int dataRace = 0;

long getMicrotime(){
	struct timeval currentTime;
	gettimeofday(&currentTime, NULL);
	return currentTime.tv_sec * (int)1e6 + currentTime.tv_usec;
}


void func0(){
  dataRace = 7;
}
void func1(){
  dataRace = 15;
}
void func2(){
  dataRace = 31;
}
void func3(){
  dataRace = 63;
}
void func4(){
  dataRace = 127;
}



/* this function is run by all threads thread */
void* threadFunc(void* label)
{
  long func_of_time = getMicrotime() + time(NULL);
  // sleep for at most 200 miliseconds;
  usleep(rand()%2000);

  long labelInt = (long) label;
  // There is only 5 functions 
  labelInt = labelInt % 5;
  if(labelInt == 0){
    func0();
  } else if (labelInt == 1){
    func1();
  } else if (labelInt == 2){
    func2();
  } else if (labelInt == 3){
    func3();
  } else if (labelInt == 4){
    func4();
  }

  return NULL;

}

int main() {
    long i = 0;
    long fn_of_time = getMicrotime() + time(NULL);
    srand(fn_of_time); // randomize seed
    printf("%d\n", fn_of_time);

    /* this variable is our reference to the second thread */
    pthread_t inc_x_thread[NUM_THREADS];

  /* create a second thread which executes inc_x(&x) */
  for ( i = 0; i < NUM_THREADS; i++){
    if(pthread_create(&(inc_x_thread[i]), NULL, threadFunc, (void*) i)) {

      fprintf(stderr, "Error creating thread\n");
      return 1;

    }
  }

  /* wait for all the threads to finish */
  for ( i = 0; i < NUM_THREADS; i++){
    if(pthread_join(inc_x_thread[i], NULL)) {

      fprintf(stderr, "Error joining thread\n");
      return 2;

    }
  }

  printf("The final value in dataRace variable is: %d\n", dataRace);
  return 0;
}