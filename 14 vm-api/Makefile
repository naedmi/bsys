TARGET = null memory-leak array_100 array_free invalid-free vector

CC = gcc
CFLAGS = -Wall -Wextra -Wpedantic -std=$(STD)
STD = gnu11

.PHONY: all clean

all: $(TARGET)

clean:
	$(RM) $(TARGET)

%: %.c
	$(CC) $^ -o $@ $(CFLAGS) 
