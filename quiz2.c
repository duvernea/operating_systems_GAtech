#include <stdio.h>
#include <pthread.h>
#define NUM_THREADS 4

void *threadFunc (void *pArg) {
	int *p = (int*)pArg;
	int myNum = *p;
	printf("Thread number %d\n", myNum);;
	return 0;
}

int main (void) {
	int i;
	pthread_t tid[NUM_THREADS];
	for (i=0; i < NUM_THREADS; i++) {
		// int pthread_create(pthread_t *thread, 
		// const pthread_attr_t *attr, 
		// void *(*start_routing) (void *), 
		// void *arg)
		pthread_create(&tid[i], NULL, threadFunc, &i);
	}
	for (i = 0; i < NUM_THREADS; i++) {
		// suspend execution of the calling thread until target thread terminates
		pthread_join(tid[i], NULL);
	}
	return 0;
}