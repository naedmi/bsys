#ifndef __measurements_h__
#define __measurements_h__

#include <time.h>
#include <stdint.h>
#define TO_NANO 1e+9

/* Returns duration from start to end in ns. */
uint64_t duration(struct timespec *start, struct timespec *end) {
    return (end->tv_sec - start->tv_sec) * TO_NANO + (end->tv_nsec - start->tv_nsec);
}

uint64_t loopDuration(int thread_nr) {
    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC_RAW, &start);
    for (int i = 0; i < thread_nr; i++) {
        ;
    }
    clock_gettime(CLOCK_MONOTONIC_RAW, &end);
    return duration(&start, &end);
}

#endif