#ifndef PRIMESCOUNTER_PRIME_CHECKER_WORKER_H
#define PRIMESCOUNTER_PRIME_CHECKER_WORKER_H

#include "concurrent_queue.h"

typedef struct {
    concurrent_queue* queue;
    int* prime_count;
    int thread_index;
} thread_arg;

void* prime_checker_worker(void* arg);

#endif // PRIMESCOUNTER_PRIME_CHECKER_WORKER_H
