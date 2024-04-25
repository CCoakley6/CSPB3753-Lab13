# Makefile for compiling Matrix Multiplication and Markov Chain programs

CC=gcc                      # Compiler to use
CFLAGS=-Wall -O2            # Compilation flags: Enable all warnings and optimization level 2
TARGET1=matrix_mult         # Target executable name for matrix multiplication
TARGET2=markov_chain        # Target executable name for Markov chain

all: $(TARGET1) $(TARGET2)

$(TARGET1): matrix_mult.c
	$(CC) $(CFLAGS) -o $(TARGET1) matrix_mult.c

$(TARGET2): markov_chain.c
	$(CC) $(CFLAGS) -o $(TARGET2) markov_chain.c

clean:
	rm -f $(TARGET1) $(TARGET2)

