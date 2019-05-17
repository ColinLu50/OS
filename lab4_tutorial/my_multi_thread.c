#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#define NUM_THREADS	3

struct in{
  int length;
  char* nums; 
};

void cal_avg(struct in* arg)
{
	int sum = 0;
	for(int i = 0; i < arg->length; i++)
	{
		sum += (*arg)[i];
	}
	return sum/arg->length;
}


int main(int argc, char *argv[])
{
  pthread_t threads[NUM_THREADS];
  struct msg inputs;
  char* word = "Hello World! It's me, thread #";
  printf("In main: creating thread %d\n", t);
  arg[t] = (struct msg){t, word};
  pthread_create(&threads[t], NULL, &PrintHello, &arg[t]);
  for(int t=0;t<NUM_THREADS;t++)
    pthread_join(threads[t], NULL);
  printf("\nall threads finish.\n");
  /* Last thing that main() should do */
  pthread_exit(NULL);
}
