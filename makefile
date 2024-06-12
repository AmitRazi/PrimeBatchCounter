# Define compilers and flags
CC = gcc
CFLAGS = -Wall -pthread -O2 -g -Iinclude

# Define targets
TARGETS = PrimesCounter generator

# Define directories
SRCDIR = sources
INCDIR = include
OBJDIR = objects

# Define source files
PRIMES_SOURCES = $(SRCDIR)/main.c $(SRCDIR)/concurrent_queue.c $(SRCDIR)/prime_checker.c $(SRCDIR)/prime_check_worker.c
GENERATOR_SOURCES = $(SRCDIR)/generator.c

# Define object files
PRIMES_OBJECTS = $(addprefix $(OBJDIR)/, $(notdir $(PRIMES_SOURCES:.c=.o)))
GENERATOR_OBJECTS = $(addprefix $(OBJDIR)/, $(notdir $(GENERATOR_SOURCES:.c=.o)))

# Default target
all: $(OBJDIR) $(TARGETS)

# PrimesCounter target
PrimesCounter: $(PRIMES_OBJECTS)
	$(CC) $(CFLAGS) -o PrimesCounter $(PRIMES_OBJECTS) -lm

# Generator target
generator: $(GENERATOR_OBJECTS)
	$(CC) $(CFLAGS) -o generator $(GENERATOR_OBJECTS)

# Create objects directory
$(OBJDIR):
	mkdir -p $(OBJDIR)

# Clean target to remove object files and executables
clean:
	rm -f $(OBJDIR)/*.o PrimesCounter generator
	rm -rf $(OBJDIR)

# Object file rules
$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Phony targets
.PHONY: all clean
