TARGET = memory-user

CC = gcc
CFLAGS = -Wall -Wextra -Wpedantic -std=$(STD)
STD = gnu11

.PHONY: all clean

all: $(TARGET)

clean:
	$(RM) $(TARGET)

%: %.c
	$(CC) $^ -o $@ $(CFLAGS) 

