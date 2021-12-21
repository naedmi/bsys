/*
* counter.c
* redoes the measurements of the traditional counter in chapter 29.
* 
* Nadine Görzen, 16.12.2021
* Gruppe 5
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include "common_threads.h" // wrapper
#include "counter.h"
#include "measurements.h"
#define TO_NANO 1e+9
#define LOOPS 1e+7
#define NUMCPUS 8

int getCPU() {
    int num_cpu = (int) sysconf(_SC_NPROCESSORS_ONLN); // number of processors currently online (available)
    if (num_cpu < 0) {
        fprintf(stderr, "sysconf failed.\n");
        exit(1);
    }
    return num_cpu;
}

void *thread_worker(void *args) {
    counter_t *m = (counter_t*) args;

    for (int i = 0; i < LOOPS; i++) {
        increment(m);
    }
    pthread_exit(0);
}

int main(int argc, char *argv[])
{
    int num_cpu = getCPU();
    printf("cores: %d\n", num_cpu);

    for (int thread_nr = 1; thread_nr <= num_cpu; thread_nr++) {
        struct timespec start, end;
        pthread_t threads[thread_nr];
        counter_t *counter = malloc(sizeof(counter_t));
        if (counter == NULL) {
                fprintf(stderr, "malloc failed.\n");
                exit(1);
            }
        init(counter);

        assert(clock_gettime(CLOCK_MONOTONIC_RAW, &start) == 0);
        for (int i = 0; i < thread_nr; i++) {
            Pthread_create(&threads[i], NULL, thread_worker, counter)
        }
        for (int i = 0; i < thread_nr; i++) {
            Pthread_join(threads[i], NULL);
        }
        assert(clock_gettime(CLOCK_MONOTONIC_RAW, &end) == 0);

        printf("%d: total time: %fs\n", thread_nr, (duration(&start, &end))/TO_NANO);
        printf("\n------------------------------------------------------\n");

        Pthread_mutex_destroy(&counter->lock);
        free(counter);
    }
}