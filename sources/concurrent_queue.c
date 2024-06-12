#include "../include/concurrent_queue.h"

// Initializes the concurrent queue
void queue_init(concurrent_queue* queue) {
    queue->head = 0;
    queue->tail = 0;
    queue->size = 0;
    pthread_mutex_init(&queue->mutex, NULL);
    pthread_cond_init(&queue->is_empty, NULL);
    pthread_cond_init(&queue->is_full, NULL);
}

// Enqueues a batch of elements into the queue
void enqueue_batch(concurrent_queue* queue, int* data, int batch_size) {
    pthread_mutex_lock(&queue->mutex);

    for (int i = 0; i < batch_size; i++) {
        // Wait if the queue is full
        while (queue->size == QUEUE_SIZE) {
            pthread_cond_wait(&queue->is_full, &queue->mutex);
        }
        // Add data to the queue
        queue->data[queue->tail] = data[i];
        queue->tail = (queue->tail + 1) % QUEUE_SIZE;
        queue->size++;
    }

    pthread_cond_signal(&queue->is_empty);
    pthread_mutex_unlock(&queue->mutex);
}

// Dequeues a batch of elements from the queue
int dequeue_batch(concurrent_queue* queue, int *buffer, int batch_size) {
    int counter = 0;
    pthread_mutex_lock(&queue->mutex);

    while (counter < batch_size) {
        // Wait if the queue is empty
        while (queue->size == 0) {
            pthread_cond_wait(&queue->is_empty, &queue->mutex);
        }

        // Retrieve data from the queue
        buffer[counter] = queue->data[queue->head];
        queue->head = (queue->head + 1) % QUEUE_SIZE;
        queue->size--;

        // Check for sentinel value
        if (buffer[counter] == SENTINEL) {
            counter++;
            pthread_mutex_unlock(&queue->mutex);
            return counter;
        }

        counter++;
    }

    pthread_cond_broadcast(&queue->is_full);
    pthread_mutex_unlock(&queue->mutex);

    return counter;
}

// Destroys the concurrent queue
void queue_destroy(concurrent_queue* queue) {
    pthread_mutex_destroy(&queue->mutex);
    pthread_cond_destroy(&queue->is_full);
    pthread_cond_destroy(&queue->is_empty);
}