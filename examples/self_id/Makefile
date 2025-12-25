CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -I../../include
LDFLAGS =

SRC_DIR = ../../src
SRC = $(SRC_DIR)/message.c $(SRC_DIR)/self_id.c

TARGET = self_id

all: $(TARGET)

$(TARGET): self_id.c $(SRC)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

clean:
	rm -f $(TARGET)

run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run
