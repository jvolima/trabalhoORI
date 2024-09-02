CC = gcc

CFLAGS = -Wall -Wextra -Werror

TARGET = programa

SRCS = main.c utilitarios.c estruturas/arvoreAvl.c estruturas/arvoreRb.c estruturas/hash.c estruturas/set.c

all: $(TARGET)

$(TARGET):
	$(CC) $(CFLAGS) -o $(TARGET) $(SRCS)

clean:
	rm -f $(TARGET)

.PHONY: all clean
