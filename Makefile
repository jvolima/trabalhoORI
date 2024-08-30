# Define the compiler
CC = gcc

# Define the compiler flags
CFLAGS = -Wall -Wextra -Werror

# Define the target executable
TARGET = programa

# Define the source files
SRCS = main.c hash/lista.c hash/hash.c set/set.c set/arvoreAvl.c utilitarios.c

# Default rule to build the target
all: $(TARGET)

# Rule to build the target executable
$(TARGET):
	$(CC) $(CFLAGS) -o $(TARGET) $(SRCS)

# Rule to clean up the directory
clean:
	rm -f $(TARGET)

# Phony targets to avoid conflicts with files named 'clean' or 'all'
.PHONY: all clean
