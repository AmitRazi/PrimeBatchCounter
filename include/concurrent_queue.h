
#pragma once

#ifndef PRIMESCOUNTER_CONCURRENT_QUEUE_H
#define PRIMESCOUNTER_CONCURRENT_QUEUE_H

#include <stdint.h>
#include <pthread.h>

// Queue capacity
#define QUEUE_SIZE 100000

// Sentinel value for termination signaling
#define SENTINEL -1

// Concurrent queue structure
typedef struct {
    int data[QUEUE_SIZE];  // Queue storage

    int head __attribute__((aligned(64)));  // Head index
    int tail __attribute__((aligned(64)));  // Tail index
    int size __attribute__((aligned(64)));  // Current size

    pthread_mutex_t mutex;    // Mutex for synchronization
    pthread_cond_t is_empty;  // Condition variable for empty queue
    pthread_cond_t is_full;   // Condition variable for full queue
} concurrent_queue;

// Function prototypes for queue operations
void queue_init(concurrent_queue *queue);
void enqueue_batch(concurrent_queue* queue, int* data, int batch_size);
int dequeue_batch(concurrent_queue* queue, int *buffer, int batch_size);
void queue_destroy(concurrent_queue* queue);

#endif // PRIMESCOUNTER_CONCURRENT_QUEUE_H