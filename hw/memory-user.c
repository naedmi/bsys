#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>

int main(int argc, char *argv[]) {
    int flags, opt, time_val;
    flags = 0;
    size_t size;

    // -s als nicht-option argument?
    while ((opt = getopt(argc, argv, ":hs:t:")) != -1) { 
        // : at the beginnning disables automatic error printing
        switch (opt) {
            case 'h':
                //
                printf("\nUsage:\n %s [-t secs] -s size", argv[0]);
                printf("\n\nOptions: \n");
                printf("-t specify amount of time to run the program\n");
                printf("-s number of megabytes the program will use\n");
                exit(0);
            case 's':
                // printf("Option s has arg: %s\n", optarg);
                size = (atoi(optarg) * 1e6) / sizeof(int); // byte to megabyte
                flags++;
                break;
            case 't':
                // printf("Option t has arg: %s\n", optarg);
                time_val = atoi(optarg);
                flags++;
                break;
            case ':': // error - missing operand
                fprintf(stderr, "Option -%c requires an operand\n", optopt);
                exit(1);
            default: // '?'
                fprintf(stderr, "Usage: %s [-t secs] -s size\n",
                        argv[0]);
                exit(1);
        }
    }

    if (flags > 2 || optind < argc) {
        fprintf(stderr, "Usage: %s [-t secs] -s size\n",
        argv[0]);
        exit(1);
    }

    printf("PID: %d\n", getpid());

    int *arr = (int*) calloc(size, sizeof(int));
    if (arr == NULL) {
        fprintf(stderr, "memory allocation failed.\n");
        exit(1);
    }

    struct timespec start, end;

    if (clock_gettime(CLOCK_MONOTONIC, &start) == -1) {
        fprintf(stderr, "clock_gettime() failed.\n");
        exit(1);
    }

    if (flags == 2) { // with specified amount of time
        while(1)
        {
            if(clock_gettime(CLOCK_MONOTONIC, &end) == -1)
            {
                fprintf(stderr, "clock_gettime() failed.\n");
                exit(1);
            }
            
            long int time_passed = end.tv_sec - start.tv_sec;
            if (time_passed >= time_val) {
                break;
            }

            for (size_t i = 0; i < size; i += sizeof(int)) 
            {
                arr[i] = 0;
            }
        }
    } else { // indefinitely
        while (1)
        {
            for (size_t i = 0; i < size; i+= sizeof(int)) {
                arr[i] = 0;
            }
            if (clock_gettime(CLOCK_MONOTONIC, &end) == -1)
            {
                fprintf(stderr, "clock_gettime() failed.\n");
                exit(1);
            }
        }
    }
    free(arr);
    return 0;
}