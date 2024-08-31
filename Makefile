CC = gcc

CFLAGS = -Wall -Wextra -Werror

TARGET = programa

SRCS = main.c hash/lista.c hash/hash.c set/set.c set/arvoreAvl.c utilitarios.c

all: $(TARGET)

$(TARGET):
	$(CC) $(CFLAGS) -o $(TARGET) $(SRCS)

clean:
	rm -f $(TARGET)

.PHONY: all clean
