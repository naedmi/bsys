#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sched.h>
#include <time.h>
#include <sys/wait.h>

int comp(const void *a, const void *b)
{
    return ( *(int*)a - *(int*)b );
}


int main(void)
{

    long long int iterations = 10000;
    long long int nsmult = 1e9;
    long long int time_start;
    long long int time_end;
    long long int time;
    // long long int for_time;
    struct timespec t_start;
    struct timespec t_end;


    int cpu = sched_getcpu();
    cpu_set_t mask;
    CPU_ZERO(&mask);
    CPU_SET(cpu,&mask);

    int rc = fork();
    if(sched_setaffinity(getpid(), sizeof(cpu_set_t), &mask) == -1)
    {
        fprintf(stderr,"core set failed parent\n");
        exit(1);
    }


    if(rc < 0)
    {
        fprintf(stderr,"fork failed\n");
        exit(1);
    } else if(rc == 0) {    //Children Code

        for(int i = 0; i < iterations; ++i)
        {
            sched_yield();
        }

        //Ausgabe zum überprüfen der Cores
        printf("Children: \n");
        printf("sched_getcpu = %d\n", sched_getcpu());


    } else {                //Parent Code

        long long int tm[iterations];

        for(int i = 0; i < iterations; ++i)
        {
            clock_gettime(CLOCK_MONOTONIC, &t_start);
            sched_yield();
            clock_gettime(CLOCK_MONOTONIC, &t_end);
            time_start = t_start.tv_nsec + (t_start.tv_sec * nsmult);
            time_end = t_end.tv_nsec + (t_end.tv_sec * nsmult);
            time = ((time_end - time_start) / 2);
            tm[i] = time;
        }
        qsort(tm,iterations, sizeof(long long int), comp);

        long long int border_values = iterations * 0.05;

        time = 0;

        for(int i = border_values; i < iterations - border_values; ++i)
        {
            //printf("AT: %lld\n", tm[i]);
            time += tm[i];
        }
        time /= (long long int)(iterations - (border_values * 2));

        printf("MAX: %lld \nMIN: %lld\n", tm[iterations - border_values], tm[border_values]);

        printf("finished: %lld\n",time);

        //Ausgabe zum überprüfen der Cores
        printf("Parent: \n");
        printf("sched_getcpu = %d\n", sched_getcpu());

    }
    return 0;
}