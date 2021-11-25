#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sched.h>
#include <errno.h>
#include <sys/wait.h>

/* returns duration from start to end in ns */
double duration(struct timespec *start, struct timespec *end) {
    return ((end->tv_sec - start->tv_sec) * 1000000000.0
    + (end->tv_nsec - start->tv_nsec));
}

/* compares two double values
https://www.gnu.org/software/libc/manual/html_node/Comparison-Functions.html */
int cmp_doubles(const void *a, const void *b) {
    const double *da = (const double *) a;
    const double *db = (const double *) b;
    return (*da > *db) - (*da < *db);
}

/* measurement of the null loop */
double measure_loop(const int loopnum) {
    struct timespec start, end;
    if (clock_gettime(CLOCK_MONOTONIC, &start) != 0) exit(1);
    for (int i = 0; i < loopnum; i++) {}
    if (clock_gettime(CLOCK_MONOTONIC, &end) != 0) exit(1);
    return duration(&start, &end);
}

int main(int argc, char *argv[])
{
    if(argc != 1)
    {
        fprintf(stderr, "Wrong input: %s", argv[1]);
        exit(1);
    }

    struct timespec start, end;

    const int loops = 100000;
    const double boundary = 0.05; // boundary percentage which is cut off at max/min
    const long long int bnd = loops * boundary;
    const int considered = loops - 2*bnd;
    const double null_loop = measure_loop(loops);

    printf("_______________________________________________________________________\n");
    printf("_________________________PARAMETERS____________________________________\n");

    /* printing parameters */

    printf("number of iterations: %d\n", loops);
    printf("considered iterations for context switch: %d\n", considered);
    printf("duration of empty loop with %d iterations: %0.f ns\n", loops, null_loop);

    printf("_______________________________________________________________________\n");
    printf("_________________________SYSTEM CALL___________________________________\n");

    /* measuring the cost of a system call */
    
    if (clock_gettime(CLOCK_MONOTONIC, &start) != 0) exit(1);
    for (int i = 0; i < loops; i++) syscall(-1); // invalid syscall
    //read(0, NULL, 0);
    if (clock_gettime(CLOCK_MONOTONIC, &end) != 0) exit(1);

    printf("average cost of a system call:\n");
    printf("%0.f ns\n", (duration(&start, &end) - null_loop) / loops);
    
    /* measuring the cost of a context switch */

    cpu_set_t set; // CPU affinity mask
    CPU_ZERO(&set);
    CPU_SET(sched_getcpu(), &set);

    int rc = fork();

    if (sched_setaffinity(0, sizeof(cpu_set_t), &set) == -1) {
        fprintf(stderr, "sched_setaffinity failed\n");
        exit(1);
    }

    if (rc < 0)
    {
        fprintf(stderr, "fork failed\n");
        exit(1);
    }
    else if (rc == 0) // CHILD PROCESS
    {
        for (int i = 0; i < loops; i++) {
            sched_yield();
        }
    }
    else // PARENT PROCESS
    {
        long long int time_ar[loops];

        for (int i = 0; i < loops; i++) {
            if (clock_gettime(CLOCK_MONOTONIC, &start) != 0) exit(1);
            sched_yield(); 
            if (clock_gettime(CLOCK_MONOTONIC, &end) != 0) exit(1);
            time_ar[i] = duration(&start, &end);
        }

        qsort(time_ar, loops, sizeof(long long int), cmp_doubles);

        long long int time = 0;
        for (int i = bnd; i < loops - bnd; i++) {
            // printf("%llu\n", time_ar[i]);
            time = time + time_ar[i];
        }
        printf("_______________________________________________________________________\n");
        printf("_________________________CONTEXT SWITCH________________________________\n");
        // printf("total time: %0.f ns\n", time);
        printf("average cost of a context switch:\n");
        printf("%0.f ns\n", (time-null_loop)/(2*(loops - 2*bnd)));

        printf("min value:\n");
        printf("%lld ns\n", (time_ar[bnd]));
        printf("max value:\n");
        printf("%lld ns\n", (time_ar[loops-bnd]));

        printf("_______________________________________________________________________\n");
    }
    return 0;
}