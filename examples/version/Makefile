CC = gcc
CFLAGS = -Wall -Wextra -Wdouble-promotion -std=c99 -I../../include
LDFLAGS =

SRC_DIR = ../../src
SRC = $(SRC_DIR)/version.c

TARGET = example_version

all: $(TARGET)

$(TARGET): example_version.c $(SRC)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

clean:
	rm -f $(TARGET)

run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run
