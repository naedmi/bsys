#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include "common_threads.h"

//
// Here, you have to write (almost) ALL the code. Oh no!
// How can you show that a thread does not starve
// when attempting to acquire this mutex you build?
//

// two phases:

// phase 1          threads check into room 1, increment counter1, and then cascade into room 2 one at a time. 
//                  turnstile to room 2 stays locked until finite number of threads have entered
// then             turnstile to room 1 closes and turnstile to room 2 opens
// phase 2          threads cascade into room 2. no new threads can enter as long as room 1 is not empty.
// then             turnstile to room 2 closes and turnstile to room 1 opens

typedef struct __ns_mutex_t {
    sem_t lock; // protects counters
    sem_t qu1;
    sem_t qu2;
    int counter1;
    int counter2;
} ns_mutex_t;

void ns_mutex_init(ns_mutex_t *m) {
    Sem_init(&m->lock, 1);
    Sem_init(&m->qu1, 1); // open in first phase
    Sem_init(&m->qu2, 0); // opens in second phase
    m->counter1 = 0;
    m->counter2 = 0;
}

void ns_mutex_acquire(ns_mutex_t *m) {
    Sem_wait(&m->lock);
    m->counter1++; // enter room1
    Sem_post(&m->lock);
    
    // first phase
    Sem_wait(&m->qu1);
    m->counter2++; // enter room2
    Sem_wait(&m->lock);
    m->counter1--; // leave room1

    // which semaphore is held?
    if (m->counter1 == 0) { // first one in room2
        Sem_post(&m->lock);
        Sem_post(&m->qu2); // signal queue 2. open second turnstile
    } else {
        Sem_post(&m->lock);
        Sem_post(&m->qu1); // wake from queue 1
    }    
    
    // second phase
    Sem_wait(&m->qu2); // mutex acquired
    m->counter2--;

    // critical section
}

void ns_mutex_release(ns_mutex_t *m) {
    // which semaphore is held?
    if (m->counter2 == 0) {
        Sem_post(&m->qu1); // wake from queue 1
    } else {
        Sem_post(&m->qu2); // wake from queue 2
    }
}

ns_mutex_t m;
int value = 0;

void *worker(void *arg) {
    ns_mutex_acquire(&m);
    value++;
    ns_mutex_release(&m);
    return NULL;
}

int main(int argc, char *argv[]) {
    assert(argc == 2);
    int num_threads = atoi(argv[1]);

    ns_mutex_init(&m);
    pthread_t p[num_threads];

    printf("parent: begin\n");

    int i;
    for (i = 0; i < num_threads; i++)
	    Pthread_create(&p[i], NULL, worker, NULL);

    for (i = 0; i < num_threads; i++)
	    Pthread_join(p[i], NULL);
    
    printf("value: %d\n", value);
    printf("parent: end\n");
    return 0;
}