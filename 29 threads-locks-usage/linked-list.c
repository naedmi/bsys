/*
* linked-list.c
* 
* Nadine Görzen, 16.12.2021
* Gruppe 5
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <stdint.h>
#include "common_threads.h" // wrapper
#include "measurements.h"
#include "linked-list.h"
#define TO_NANO 1e+9
#define NUMCPUS 8
#define LENGTH 10000000

int getCPU() {
    int num_cpu = (int) sysconf(_SC_NPROCESSORS_ONLN); // number of processors currently online (available)
    if (num_cpu < 0) {
        fprintf(stderr, "sysconf failed.\n");
        exit(1);
    }
    return num_cpu;
}

void *thread_worker(void *args) {
    list_t *l = (list_t *) args;
    List_Lookup(l, 0);
    pthread_exit(0);
}

int main(int argc, char *argv[])
{
    int num_cpu = getCPU();
    printf("cores: %d\n", num_cpu);

    list_t *list = malloc(sizeof(list_t));
    if (list == NULL) {
        fprintf(stderr, "malloc failed.\n");
        exit(1);
    }
    List_Init(list);

    for (int i = 0; i < LENGTH; i++) {
        List_Insert(list, i);
    }

    for (int thread_nr = 1; thread_nr <= num_cpu; thread_nr++) {
        struct timespec start, end;
        pthread_t threads[thread_nr];

        clock_gettime(CLOCK_MONOTONIC_RAW, &start);
        for (int i = 0; i < thread_nr; i++) {
            Pthread_create(&threads[i], NULL, thread_worker, list);
        }
        for (int i = 0; i < thread_nr; i++) {
            Pthread_join(threads[i], NULL);
        }
        clock_gettime(CLOCK_MONOTONIC_RAW, &end);
        printf("%d: total time: %fs\n", thread_nr, ((duration(&start, &end)-2*loopDuration(thread_nr))/TO_NANO));
        printf("\n------------------------------------------------------\n");
    }
    List_Free(list);
}