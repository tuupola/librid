CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -I../include -I.
LDFLAGS =

# Source files
SRC_DIR = ../src
SRC = $(SRC_DIR)/message.c \
      $(SRC_DIR)/basic_id.c \
      $(SRC_DIR)/operator_id.c \
      $(SRC_DIR)/location.c \
      $(SRC_DIR)/self_id.c \
      $(SRC_DIR)/system.c \
      $(SRC_DIR)/message_pack.c \
      $(SRC_DIR)/auth_page.c \
      $(SRC_DIR)/auth.c \
      $(SRC_DIR)/transport.c

# Test files
TEST_SRC = unit.c test_message.c test_basic_id.c test_operator_id.c test_location.c test_self_id.c test_system.c test_message_pack.c test_auth_page.c test_auth.c test_transport.c

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