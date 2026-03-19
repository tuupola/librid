CC = gcc
CFLAGS = -Wall -Wextra -Wdouble-promotion -std=c99 -I../../include
LDFLAGS =

SRC_DIR = ../../src
SRC = $(SRC_DIR)/message.c $(SRC_DIR)/basic_id.c $(SRC_DIR)/location.c \
      $(SRC_DIR)/self_id.c $(SRC_DIR)/system.c $(SRC_DIR)/operator_id.c \
      $(SRC_DIR)/message_pack.c $(SRC_DIR)/auth_page.c $(SRC_DIR)/auth.c

# Set MAVLINK_DIR to your mavlink/c_library_v2 checkout, for example:
#   make MAVLINK_DIR=/path/to/c_library_v2
MAVLINK_DIR ?= ../../build/_deps/mavlink-src
CFLAGS += -I$(MAVLINK_DIR)

TARGET = example_mavlink

all: $(TARGET)

$(TARGET): example_mavlink.c $(SRC)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

clean:
	rm -f $(TARGET)

run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run
