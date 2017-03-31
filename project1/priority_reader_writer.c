#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/types.h>
#include <unistd.h>

int SHARED_GLOBAL_VAR = -1;
int count = 0;
int readers = 0;

pthread_mutex_t mux = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t c_cons = PTHREAD_COND_INITIALIZER;
pthread_cond_t c_prod = PTHREAD_COND_INITIALIZER;

void *producer(void* param);
void *consumer(void* param);
void randomWait();

int main() {
	// pthread_t tid1, tid2;
	printf("prog start running...");
	srand(time(NULL));   // seed for random

	// int num_prod_threads = 5;
	// int num_cons_threads = 5;
	int num_threads = 10; // each

	// Producer Threads creation
	int ints[num_threads];
	pthread_t prod_threads[num_threads];
	pthread_t cons_threads[num_threads];

	for (int i=0; i<num_threads; ++i) {
		ints[i] = i;
		pthread_create(&cons_threads[i], NULL, consumer, NULL);
		randomWait();

		pthread_create(&prod_threads[i], NULL, producer, &ints[i]);

		readers++;
		randomWait();
	}

	// join threads
	for (int i=0; i<num_threads; ++i) {
		pthread_join(prod_threads[i], NULL);
		randomWait();

		pthread_join(cons_threads[i], NULL);
	}

	printf("parent quitting\n");
}

void *producer(void* param) {
	uint64_t tid;
	pthread_threadid_np(NULL, &tid);
	//printf("Producer thread %llu running...\n", tid);

	pthread_mutex_lock(&mux);
	int i = *((int *) param);
	while (readers > 0) {
		pthread_cond_signal(&c_cons);
	 	pthread_cond_wait(&c_prod, &mux);
	 }
	SHARED_GLOBAL_VAR = i;
	// count = 1;
	printf("Writing Global Var = %i, #Readers = %i (thread %llu)\n", SHARED_GLOBAL_VAR, readers, tid);
	fflush(stdout);
	pthread_mutex_unlock(&mux);
	pthread_cond_signal(&c_cons);
	pthread_cond_signal(&c_prod);	
	return 0;
}

void *consumer(void* param) {
	uint64_t tid;
	pthread_threadid_np(NULL, &tid);
	// printf("Consumer thread %llu running...\n", tid);

	pthread_mutex_lock(&mux);
	while (readers == 0) {
		pthread_cond_wait(&c_cons, &mux);
	}
	printf("Reading Global Var = %i, #Readers = %i (thread %llu)\n", SHARED_GLOBAL_VAR, readers, tid);
	// count = 0;
	readers--;
	pthread_mutex_unlock(&mux);
	pthread_cond_signal(&c_prod);
	return 0;
}

void randomWait() {
	// sleep in microseconds
	int r = rand(); 
	r = 50 * (r % 10000);
	usleep(r);
	// convert to milliseconds
	float ms = r / 1000.0;
	// printf("random sleep in milliseconds: %.2f\n", ms);

}