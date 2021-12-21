/*
* sloppy-counter.c
* redoes the measurements of the approximate counter in chapter 29.
* 
* Nadine Görzen, 16.12.2021
* Gruppe 5
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include "common_threads.h" // wrapper
#include "sloppy-counter.h"
#include "measurements.h"
#define TO_NANO 1e+9
#define LOOPS 1000000
#define THRESHOLD 1000

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
    pthread_t threadID = pthread_self();
    for (int i = 0; i < LOOPS; i++) {
        update(m, threadID, 1);
    }
    pthread_exit(0);
}

int main(int argc, char *argv[])
{
    int num_cpu = getCPU();
    printf("cores: %d\n", num_cpu);

    for (int thread_nr = 1; thread_nr <= num_cpu; thread_nr++) {
        counter_t *counter = malloc(sizeof(counter_t));
        if (counter == NULL) {
            fprintf(stderr, "malloc failed.\n");
            exit(1);
        }
        init(counter, THRESHOLD);

        struct timespec start, end;
        pthread_t threads[thread_nr];

        clock_gettime(CLOCK_MONOTONIC_RAW, &start);
        for (int i = 0; i < thread_nr; i++) {
            Pthread_create(&threads[i], NULL, thread_worker, counter);
        }
        for (int i = 0; i < thread_nr; i++) {
            Pthread_join(threads[i], NULL);
        }
        clock_gettime(CLOCK_MONOTONIC_RAW, &end);
        printf("%d: total time: %fs\n", thread_nr, (duration(&start, &end)/TO_NANO));
        printf("\n------------------------------------------------------\n");

        Pthread_mutex_destroy(&counter->glock);
        for (int m = 0; m < NUMCPUS; m++) {
            Pthread_mutex_destroy(&counter->llock[m]);
        }
        free(counter);
    }
}