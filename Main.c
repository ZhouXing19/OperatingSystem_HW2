#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h>   
#include <pthread.h> 
#include "hash.h"
#include "counter.h"
#include <sys/time.h>


float getTime(struct timeval t0, struct timeval t1){
  float elapsed = (t1.tv_sec-t0.tv_sec)*100000 + t1.tv_usec-t0.tv_usec;
  return elapsed;
}

void* call(void* myc){
  for(int i=0; i<1000000; i++){
    Counter_Increment((counter_t*)myc);
  }
  return NULL;
}

int main(){

  struct counter_t *myc = (counter_t*)malloc(sizeof(counter_t));

  struct timeval t1;
  struct timeval t2;
  gettimeofday(&t1, 0);

  for(int i=0; i<20; i++){
    pthread_t thread_id; 
    pthread_create(&thread_id, NULL, call, myc); 
  }
  gettimeofday(&t2, 0);
  float f = getTime(t1, t2)/100000;

  printf("f is %f\n", f);

  exit(0); 
}