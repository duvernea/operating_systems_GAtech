#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/types.h>
#include <unistd.h>

int SHARED_GLOBAL_VAR = -1;
int count = 0;
int readers = 0;

pthread_mutex_t mux = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t c_reader = PTHREAD_COND_INITIALIZER;
pthread_cond_t c_writer = PTHREAD_COND_INITIALIZER;

void *writer(void* param);
void *reader(void* param);
void randomWait();

int main() {
	// pthread_t tid1, tid2;
	srand(time(NULL));   // seed for random

	int num_threads = 5; // each
	// Threads creation
	int ints[num_threads];
	pthread_t writer_threads[num_threads];
	pthread_t reader_threads[num_threads];

	for (int i=0; i<num_threads; ++i) {
		ints[i] = i;
		pthread_create(&writer_threads[i], NULL, writer, &ints[i]);
		randomWait();
		pthread_create(&reader_threads[i], NULL, reader, NULL);

		readers++;
	}
	// join threads
	for (int i=0; i<num_threads; ++i) {
		pthread_join(writer_threads[i], NULL);
		pthread_join(reader_threads[i], NULL);
	}
}

void *writer(void* param) {
	uint64_t tid;
	pthread_threadid_np(NULL, &tid);

	randomWait();
	pthread_mutex_lock(&mux);
	int i = *((int *) param);
	while (readers > 0) {
		pthread_cond_signal(&c_reader);
	 	pthread_cond_wait(&c_writer, &mux);
	 }
	SHARED_GLOBAL_VAR = i;
	printf("Writing Global Var = %i, #Readers = %i (thread %llu)\n", SHARED_GLOBAL_VAR, readers, tid);
	fflush(stdout);
	pthread_mutex_unlock(&mux);
	pthread_cond_signal(&c_reader);
	pthread_cond_signal(&c_writer);	
	return 0;
}

void *reader(void* param) {
	uint64_t tid;
	pthread_threadid_np(NULL, &tid);

	randomWait();
	pthread_mutex_lock(&mux);
	while (readers == 0) {
		pthread_cond_wait(&c_reader, &mux);
	}
	printf("Reading Global Var = %i, #Readers = %i (thread %llu)\n", SHARED_GLOBAL_VAR, readers, tid);
	readers--;
	pthread_mutex_unlock(&mux);
	pthread_cond_signal(&c_writer);
	return 0;
}

void randomWait() {
	// sleep in microseconds
	int r = rand(); 
	r = 50 * (r % 10000);
	usleep(r);
	// convert to milliseconds
	float ms = r / 1000.0;
}