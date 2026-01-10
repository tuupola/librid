CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -I../../include
LDFLAGS =

SRC_DIR = ../../src
SRC = $(SRC_DIR)/message.c $(SRC_DIR)/basic_id.c $(SRC_DIR)/location.c \
      $(SRC_DIR)/self_id.c $(SRC_DIR)/system.c $(SRC_DIR)/operator_id.c \
      $(SRC_DIR)/message_pack.c $(SRC_DIR)/auth_page.c $(SRC_DIR)/auth.c

TARGET = example_json

all: $(TARGET)

$(TARGET): example_json.c $(SRC)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

clean:
	rm -f $(TARGET)

run: $(TARGET)
	@./$(TARGET)

.PHONY: all clean run
