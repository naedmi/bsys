TARGET = fork-join rendezvous barrier reader-writer reader-writer-nostarve mutex-nostarve

CC = gcc
CFLAGS = -pthread -Wall -Wextra -Wpedantic -std=$(STD)
STD = gnu11

.PHONY: all clean

all: $(TARGET)

clean:
	$(RM) $(TARGET)