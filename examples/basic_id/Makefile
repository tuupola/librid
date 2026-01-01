CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -I../../include
LDFLAGS =

SRC_DIR = ../../src
SRC = $(SRC_DIR)/message.c $(SRC_DIR)/basic_id.c

TARGET = basic_id

all: $(TARGET)

$(TARGET): example_basic_id.c $(SRC)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

clean:
	rm -f $(TARGET)

run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run
