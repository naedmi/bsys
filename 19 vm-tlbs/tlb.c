/*
* tlb.c
* roughly measures the cost of accessing each page of the TLB.
* 
* Nadine Görzen, 15.11.2021
* Gruppe 5
*/
#define _GNU_SOURCE
#define TO_NANO 1e+9
#define BOUNDARY 0.05 
// boundary percentage to cut off at min/max values of array
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <errno.h>
#include <sched.h>
#include <pthread.h>

// übung:
// uint64_t
// rechnung besser aufteilen,
// um überläufe zu verhindern: (stop.sec - start.sec) * SEC_TO_NSEC + stop.nsec - start.nsec
// oder struct vom typ timespec

/* inputs: -n number of pages to touch. -l number of trials. */

/* returns duration from start to end in ns */
unsigned long duration(struct timespec *start, struct timespec *end) {
    return (end->tv_sec * TO_NANO + end->tv_nsec) 
    - (start->tv_sec * TO_NANO + start->tv_nsec);
}

/* compares two double values
* https://www.gnu.org/software/libc/manual/html_node/Comparison-Functions.html
*/
int cmp_doubles(const void *a, const void *b) {
    const unsigned long long *da = (const unsigned long long *) a;
    const unsigned long long *db = (const unsigned long long *) b;
    return (*da > *db) - (*da < *db);
}

int main(int argc, char *argv[])
{
    int opt, flags;
    int NUMPAGES, trials;
    unsigned long long PAGESIZE;
    NUMPAGES = 4;
    trials = 1000;

    /* get arguments */
    while ((opt = getopt(argc, argv, ":hn:l:")) != -1) { 
        switch (opt) {
            case 'h':
                printf("\nUsage:\n %s [options]", argv[0]);
                printf("\n\nOptions: \n");
                printf("-h show this help message and exit\n");               
                printf("-n specify number of pages to touch\n");
                printf("-l number of trials\n");
                exit(0);
            case 'n':
                NUMPAGES = atoi(optarg);
                if (NUMPAGES < 0) {
                    fprintf(stderr, "Number of pages cannot be < 0.\n");
                    exit(1);
                }
                flags++;
                break;
            case 'l':
                trials = atoi(optarg);
                if (trials < 0) {
                    fprintf(stderr, "Number of trials cannot be < 0.\n");
                    exit(1);
                }
                flags++;
                break;
            case ':':
                fprintf(stderr, "Option -%c requires an operand\n", optopt);
                exit(1);
            default: // '?'
                fprintf(stderr, "Usage: %s -n number of pages -l number of trials [-p page size]\n",
                argv[0]);
                exit(1);
        }
    }

    if (optind < argc) {
        fprintf(stderr, "Usage: %s -n number of pages -l number of trials [-p page size]\n",
        argv[0]);
        exit(1);
    }

    PAGESIZE = sysconf(_SC_PAGESIZE);
    if (PAGESIZE < 1) {
        perror("Error while obtaining page size.");
        exit(1);
    }
    const long int jump = PAGESIZE / sizeof(int);
    struct timespec start, end;
    const long int bound = trials * BOUNDARY;

    /* set cpu for process */
    cpu_set_t set; // CPU affinity mask
    pthread_t thread = pthread_self();
    CPU_ZERO(&set);
    CPU_SET(sched_getcpu(), &set);
    
    /*if(sched_setaffinity(getpid(), sizeof(cpu_set_t), &set) != 0){
        fprintf(stderr, "Error while setting cpu.\n");
        exit(1);
    }*/
    if (pthread_setaffinity_np(thread, sizeof(set), &set) != 0) {
        fprintf(stderr, "Error while calling pthread_setaffinity_np().\n");
        exit(1);
    }
    
    /* print arguments */
    printf("ARG number of pages to touch %d\n", NUMPAGES);
    printf("ARG number of trials %d\n", trials);
    printf("ARG page size %lld\n\n", PAGESIZE);

    /* array declaration */
    unsigned long long *time_ar = (unsigned long long*) malloc(trials * sizeof(unsigned long long));
    if (time_ar == NULL) {
        fprintf(stderr, "memory allocation failed.\n");
        exit(1);
    }

    int *a = (int*) calloc(NUMPAGES * jump, sizeof(int)); // NUMPAGES * PAGESIZE?
    if (a == NULL) {
        fprintf(stderr, "memory allocation failed.\n");
        exit(1);
    }

    /* measurement */
    for (int j = 0; j < trials; j++) {
        for (int i = 0; i < NUMPAGES * jump; i += jump) {
            if (clock_gettime(CLOCK_MONOTONIC_RAW, &start) != 0) exit(1);
            a[i] += 1;
            if (clock_gettime(CLOCK_MONOTONIC_RAW, &end) != 0) exit(1);

            unsigned long long dur = duration(&start, &end);
            time_ar[j] += dur;
        }
    }

    qsort(time_ar, trials, sizeof(unsigned long long), cmp_doubles);

    unsigned long long time = 0;
    for (long int i = bound; i < trials - bound; i++) {
        time += (time_ar[i]/NUMPAGES);
    }
    printf("average cost: %lld ns\n", (time / ((unsigned long long) trials - 2*bound)));

    free(a);
    free(time_ar);
    return 0;
}