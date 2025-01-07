CC = gcc
CFLAGS = -Wall -I./src/backend
LDFLAGS = -lsqlite3 -lmicrohttpd

SRC_DIR = src
OBJ_DIR = build/obj
BIN_DIR = build/bin

SOURCES = $(wildcard $(SRC_DIR)/backend/*.c) $(SRC_DIR)/main.c
OBJECTS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SOURCES))
EXECUTABLE = $(BIN_DIR)/fourm

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	@mkdir -p $(BIN_DIR)
	$(CC) $(OBJECTS) -o $@ $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)/backend
	$(CC) $(CFLAGS) -c $< -o $@
	$(info Put the contents of frontend into the same localtion as the executable)
clean:
	rm -rf build

frontend:
	@cp -r src/frontend $(BIN_DIR)

.PHONY: all clean frontend