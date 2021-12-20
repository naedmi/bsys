#ifndef __linked_list_h__
#define __linked_list_h__

#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "common_threads.h"

// basic node structure
typedef struct __node_t {
    int               key;
    struct __node_t   *next;
    pthread_mutex_t   lock;
} node_t;

// basic list structure (one used per list)
typedef struct __list_t {
  node_t            *head;
  pthread_mutex_t   lock;
} list_t;

void List_Init(list_t *L) {
  L->head = NULL;
  Pthread_mutex_init(&L->lock, NULL);
}

void List_Insert(list_t *L, int key) {
  // synchronization not needed
  node_t *new = (node_t*) malloc(sizeof(node_t));
  if (new == NULL) {
    fprintf(stderr, "malloc failed.\n");
    exit(1);
  }
  new->key = key;
  Pthread_mutex_init(&new->lock, NULL);

  // just lock critical section
  Pthread_mutex_lock(&L->lock);  
  new->next = L->head;
  L->head = new;
  Pthread_mutex_unlock(&L->lock);
}

static int List_Lookup(list_t *L, int key) {
  int rv = -1;
  Pthread_mutex_lock(&L->lock);
  node_t *curr = L->head;

  while (curr) {
    if (curr->key == key) {
      rv = 0;
      break;
    }

    curr = curr->next;
  }
  Pthread_mutex_unlock(&L->lock);
  return rv; // now both success and failure
}

static void List_Free(list_t *L) {
  node_t *curr = L->head;
  if (!curr)
    return;
  Pthread_mutex_lock(&curr->lock);
  while (curr) {
    node_t *tempNode = curr;
    curr = curr->next;
    if (curr)
      Pthread_mutex_lock(&curr->lock);
    Pthread_mutex_unlock(&tempNode->lock);
    free(tempNode);
  }
  free(L);
}

#endif