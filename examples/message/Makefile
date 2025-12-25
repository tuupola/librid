CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -I../../include
LDFLAGS =

SRC_DIR = ../../src
SRC = $(SRC_DIR)/message.c

TARGET = message

all: $(TARGET)

$(TARGET): message.c $(SRC)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

clean:
	rm -f $(TARGET)

run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run
