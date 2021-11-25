TARGET = 1 2 3 4 5 6 7 8 84

CC = gcc
CFLAGS = -Wall -Wextra -Wpedantic -std=$(STD)
STD = gnu11

.PHONY: all clean

all: $(TARGET)

clean:
	$(RM) $(TARGET)

%: %.c
	$(CC) $^ -o $@ $(CFLAGS) 

