#include "../include/prime_check_worker.h"
#include "../include/concurrent_queue.h"
#include "../include/prime_checker.h"
#include "../include/config.h"

void* prime_checker_worker(void* arg) {
    thread_arg* t_arg = (thread_arg*)arg;
    concurrent_queue* queue = t_arg->queue;
    int* prime_count = t_arg->prime_count;
    int thread_index = t_arg->thread_index;
    int batch[BATCH_SIZE];
    int num_dequeued = 0;

    while (1) {
        num_dequeued = dequeue_batch(queue, batch, BATCH_SIZE);

        for (int i = 0; i < num_dequeued; i++) {
            if (batch[i] == SENTINEL) {
                return NULL;
            }
            if (is_prime(batch[i])) {
                prime_count[thread_index]++;
            }
        }
    }
}
