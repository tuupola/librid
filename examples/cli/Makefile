CC = gcc
CFLAGS = -Wall -Wextra -Wdouble-promotion -std=c99 -I../../include
LDFLAGS =

SRC_DIR = ../../src
SRC = $(SRC_DIR)/message.c $(SRC_DIR)/basic_id.c $(SRC_DIR)/location.c \
      $(SRC_DIR)/self_id.c $(SRC_DIR)/system.c $(SRC_DIR)/operator_id.c \
      $(SRC_DIR)/message_pack.c $(SRC_DIR)/auth_page.c $(SRC_DIR)/auth.c \
      $(SRC_DIR)/transport.c

TARGET = rid

all: $(TARGET)

$(TARGET): example_cli.c $(SRC)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

clean:
	rm -f $(TARGET)

run: $(TARGET)
	@./$(TARGET) --decode 12202d3e0420bd5c25401c190d0000c10834084a0339300100 | jq

.PHONY: all clean run
