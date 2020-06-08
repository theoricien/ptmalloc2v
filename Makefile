CC		= gcc
CFLAGS	= -Wall -O3 -g
EXEC	= ptmalloc2v

OBJ_DIR = obj
BIN_DIR = bin
SRC_DIR = src
INC_DIR	= include

all: setup objects $(EXEC)

setup:
	-mkdir $(OBJ_DIR) 2>/dev/null
	-mkdir $(BIN_DIR) 2>/dev/null

$(EXEC):
	$(CC) -I$(INC_DIR) $(CFLAGS) $(OBJ_DIR)/* tests/main.c -o $(BIN_DIR)/$(EXEC)

objects:
	$(CC) -I$(INC_DIR) -c $(SRC_DIR)/structs.c  -o $(OBJ_DIR)/structs.o
	$(CC) -I$(INC_DIR) -c $(SRC_DIR)/ptassert.c -o $(OBJ_DIR)/ptassert.o
	$(CC) -I$(INC_DIR) -c $(SRC_DIR)/printer.c  -o $(OBJ_DIR)/printer.o
	$(CC) -I$(INC_DIR) -c $(SRC_DIR)/heapview.c -o $(OBJ_DIR)/heapview.o

clean:
	-rm -r $(BIN_DIR) 2>/dev/null
	-rm -r $(OBJ_DIR) 2>/dev/null
