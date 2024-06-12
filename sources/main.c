#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "../include/concurrent_queue.h"
#include "../include/prime_checker.h"
#include "../include/prime_check_worker.h"
#include "../include/config.h"


#if defined(_WIN32) || defined(_WIN64)
#include <windows.h>

int get_cpu_count() {
    SYSTEM_INFO sysinfo;
    GetSystemInfo(&sysinfo);
    return sysinfo.dwNumberOfProcessors;
}

#elif defined(__linux__) || defined(__unix__) || defined(__APPLE__)
#include <unistd.h>

int get_cpu_count() {
    return sysconf(_SC_NPROCESSORS_ONLN);
}

#else
#error "Unsupported platform"
#endif

int main() {
    concurrent_queue queue;
    int num_threads = get_cpu_count() / 2;

    pthread_t* consumers = malloc(num_threads * sizeof(pthread_t));
    thread_arg* args = malloc(num_threads * sizeof(thread_arg));
    int* prime_counts = calloc(num_threads, sizeof(int));
    int batch[BATCH_SIZE];
    int batch_count = 0;

    queue_init(&queue);

    for (int i = 0; i < num_threads; i++) {
        args[i].queue = &queue;
        args[i].prime_count = prime_counts;
        args[i].thread_index = i;

        if (pthread_create(&consumers[i], NULL, prime_checker_worker, &args[i])) {
            perror("Failed to create worker thread");
            return EXIT_FAILURE;
        }
    }

    int num = 0;

    while (scanf("%d", &num) != EOF) {
        batch[batch_count++] = num;

        if (batch_count == BATCH_SIZE) {
            enqueue_batch(&queue, batch, BATCH_SIZE);
            batch_count = 0;
        }
    }

    if (batch_count > 0) {
        enqueue_batch(&queue, batch, batch_count);
    }

    for (int i = 0; i < num_threads; i++) {
        int sentinel = SENTINEL;
        enqueue_batch(&queue, &sentinel, 1);
    }

    for (int i = 0; i < num_threads; i++) {
        pthread_join(consumers[i], NULL);
    }

    int primes_found = 0;
    for (int i = 0; i < num_threads; i++) {
        primes_found += prime_counts[i];
    }
    printf("Threads found %d prime numbers\n", primes_found);

    queue_destroy(&queue);
    free(consumers);
    free(args);
    free(prime_counts);

    return EXIT_SUCCESS;
}
