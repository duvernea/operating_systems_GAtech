#include <stdio.h>
#include <pthread.h>
#define NUM_THREADS 4

void *threadFunc (void *pArg) {
	int myNum = *((int*)pArg);
	printf("Thread number %d\n", myNum);;
	return 0;
}

int main (void) {
	int tNum[NUM_THREADS];
	pthread_t tid[NUM_THREADS];
	int i;
	for (i=0; i < NUM_THREADS; i++) {
		tNum[i] = i;
		// int pthread_create(pthread_t *thread, 
		// const pthread_attr_t *attr, 
		// void *(*start_routing) (void *), 
		// void *arg)
		pthread_create(&tid[i], NULL, threadFunc, &tNum[i]);
	}
	// We don't have control over how these newly created threads are scheduled
	// 'i' defined in main = globally visible variable
	// when value changes in one thread, all other threads see new value
	// data race or race condition - a thread tries to read a value while another thread modifies it

	for (i = 0; i < NUM_THREADS; i++) {
		// suspend execution of the calling thread until target thread terminates
		pthread_join(tid[i], NULL);
	}
	return 0;
}