CC = gcc
CFLAGS = -Wall -Wextra -pedantic -std=c90 -Iinc

SRC_DIR = src
OBJ_DIR = build/obj
BIN_DIR = build/bin

TARGET = $(BIN_DIR)/laboratorio2.exe

SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
OBJ_FILES = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC_FILES))

.PHONY: all clean doc

all: $(TARGET)

$(TARGET): $(OBJ_FILES)
	$(CC) $(OBJ_FILES) -o $(TARGET)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c inc/alumno.h
	$(CC) $(CFLAGS) -c $< -o $@

doc:
	doxygen Doxyfile

clean:
	rm -f $(OBJ_DIR)/*.o $(BIN_DIR)/*.exe