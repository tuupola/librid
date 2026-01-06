CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -I../../include
LDFLAGS =

SRC_DIR = ../../src
SRC = $(SRC_DIR)/message.c $(SRC_DIR)/location.c

TARGET = example_location

all: $(TARGET)

$(TARGET): example_location.c $(SRC)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

clean:
	rm -f $(TARGET)

run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run
