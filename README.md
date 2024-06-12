# PrimeBatchCounter

## Overview

PrimesCounter is a high-performance program designed to read a large stream of integers, determine which ones are prime, and count them. It efficiently utilizes modern multi-core processors and adheres to strict memory limits.

## Features

- Efficient prime checking using precomputed small primes.
- Multi-threaded processing for concurrent prime checking.
- Batch processing to minimize synchronization overhead.
- Memory-efficient implementation using fixed-size data structures.

## Implementation Strategy

### Prime Checking

- **Precomputed Small Primes**: Uses a precomputed list of small prime numbers to quickly eliminate non-prime numbers, reducing the number of divisions needed.

### Concurrent Processing

- **Multi-threading**: Utilizes multiple threads to concurrently check prime numbers, effectively using multi-core processors. The number of threads is set to half the available CPU cores to balance workload and minimize context switching.

### Batch Processing

- **Batch Enqueueing and Dequeueing**: Processes numbers in batches of fixed size to reduce the frequency of locking and unlocking operations on the queue, improving overall throughput.

### Memory Management

- **Fixed-size Data Structures**: Uses fixed-size arrays for the queue and small primes to ensure memory usage remains within the 2MB limit.

## Files

- `main.c`: The main program that initializes the queue, spawns worker threads, and manages the input and output.
- `concurrent_queue.c` & `concurrent_queue.h`: Implements the thread-safe concurrent queue.
- `prime_checker.c` & `prime_checker.h`: Contains the prime-checking logic.
- `prime_check_worker.c` & `prime_check_worker.h`: Implements the worker thread function.
- `generator.c`: Generates a stream of random integers for testing the PrimesCounter.
- `config.h`: Configuration file for constants like `BATCH_SIZE` and `SENTINEL`.

## How to Use

### Compile the Project

Use the provided Makefile to compile the project:
```sh
make
```

### Generate Random Numbers

Use the `generator` program to generate a stream of random numbers:
```sh
./generator <seed> <count> | ./PrimesCounter
```

### Run PrimesCounter

The PrimesCounter program reads the generated numbers, processes them to count primes, and outputs the total count:
```sh
./generator 42 1000000 | ./PrimesCounter
```

### Clean Up

Remove the compiled object files and executables:
```sh
make clean
```

## Example Workflow

1. **Compile the project**:
   ```sh
   make
   ```

2. **Generate random numbers and count primes**:
   ```sh
   ./generator 42 1000000 | ./PrimesCounter
   ```

3. **Clean up**:
   ```sh
   make clean
   ```

## License

This project is licensed under the MIT License - see the LICENSE file for details.

---

By combining efficient prime checking, multi-threading, batch processing, and a thread-safe concurrent queue, PrimesCounter achieves high performance and effective utilization of modern multi-core processors while adhering to memory constraints.
