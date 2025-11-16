CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -I../include -I.
LDFLAGS = -lm

# Source files
SRC_DIR = ../src
SRC = $(SRC_DIR)/header.c \
      $(SRC_DIR)/basic_id.c \
      $(SRC_DIR)/operator_id.c \
      $(SRC_DIR)/location.c \
      $(SRC_DIR)/self_id.c

# Test files
TEST_SRC = unit.c header.c basic_id.c operator_id.c location.c self_id.c

# Object files
OBJ = $(SRC:.c=.o)
TEST_OBJ = $(TEST_SRC:.c=.o)

# Target executable
TARGET = test_runner

all: $(TARGET)

$(TARGET): $(OBJ) $(TEST_OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

# Compile source files
$(SRC_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Compile test files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TEST_OBJ) $(TARGET)

test: $(TARGET)
	./$(TARGET)

.PHONY: all clean test