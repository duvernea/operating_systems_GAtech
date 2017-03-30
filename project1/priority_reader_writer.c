#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int SHARED_GLOBAL_VAR;
int count = 0;

pthread_mutex_t mux = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t c_cons = PTHREAD_COND_INITIALIZER;
pthread_cond_t c_prod = PTHREAD_COND_INITIALIZER;

void *producer(void* param);
void *consumer(void* param);

int main() {
	// pthread_t tid1, tid2;
	printf("prog start running...");

	int num_prod_threads = 4;
	int num_cons_threads = 4;

	// Producer Threads creation
	int ints[num_prod_threads];
	pthread_t prod_threads[num_prod_threads];
	for (int i=0; i<num_prod_threads; ++i) {
		ints[i] = i;
		pthread_create(&prod_threads[i], NULL, producer, &ints[i]);
	}
	// join producer threads
	for (int i=0; i<num_prod_threads; ++i) {
		pthread_join(prod_threads[i], NULL);
	}

	// Consumer Threads creation
	pthread_t cons_threads[num_cons_threads];
	for (int i=0; i<num_cons_threads; ++i) {
		ints[i] = i;
		pthread_create(&cons_threads[i], NULL, consumer, NULL);
	}
	// join producer threads
	for (int i=0; i<num_cons_threads; ++i) {
		pthread_join(cons_threads[i], NULL);
	}


	printf("parent quitting\n");
}

void *producer(void* param) {
	printf("Producer thread running...\n");

	pthread_mutex_lock(&mux);
	int i = *((int *) param);
	// while (count == 0) {
	// 	pthread_cond_wait(&c_cons, &mux);
	// }
	SHARED_GLOBAL_VAR = i;
	// count = 1;
	pthread_mutex_unlock(&mux);
	pthread_cond_signal(&c_cons);
	printf("Producer: inserted %d\n", SHARED_GLOBAL_VAR); fflush(stdout);
	return 0;
}

void *consumer(void* param) {
	return 0;
}