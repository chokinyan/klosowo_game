CC = gcc
CFLAGS = -O3 -Wall -Wextra -g -Iinclude `pkg-config --cflags gtk4`
LIBS = `pkg-config --libs gtk4`

SRC_DIR = src
DOC_DIR = doc
DIST_DIR = dist
BIN_DIR = bin
OBJ_DIR = obj
BIN_DIR_PATH = $(DIST_DIR)/$(BIN_DIR)


DOC_TARGET = Doxyfile
BIN_TARGET = $(DIST_DIR)/$(BIN_DIR)/game

FILES := $(shell find $(SRC_DIR) -name '*.c')

all: $(BIN_TARGET)

$(BIN_TARGET): $(FILES)
	@mkdir -p $(BIN_DIR_PATH)
	$(CC) $(CFLAGS) $(FILES) -o $(BIN_TARGET) $(LIBS)

test:
	@echo "need to be added"

run : $(BIN_TARGET)
	./$(BIN_TARGET)

doc:
	@mkdir -p $(DOC_DIR)
	doxygen $(DOC_TARGET)

.PHONY: all clean

clean:
	rm -rf $(DIST_DIR)
	clear