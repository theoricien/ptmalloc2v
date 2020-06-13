CC		= gcc
CFLAGS	= -Wall -O3 -g
EXEC	= test

STATIC_LIB	= libptm2v.a
LIB_FLAGS 	= -ldl
PTM2V_FLAG 	= -lptm2v

OBJ_DIR = obj
BIN_DIR = bin
SRC_DIR = src
LIB_DIR = libs
INC_DIR	= include
TST_DIR = tests

all: setup objects static_lib

setup:
	-mkdir $(OBJ_DIR) 2>/dev/null
	-mkdir $(BIN_DIR) 2>/dev/null
	-mkdir $(LIB_DIR) 2>/dev/null

static_lib:
	ar rcs $(LIB_DIR)/$(STATIC_LIB) $(OBJ_DIR)/*.o

$(EXEC): all
	$(CC) -I$(INC_DIR) $(CFLAGS) $(LIB_FLAGS) $(TST_DIR)/main.c -L$(LIB_DIR) $(PTM2V_FLAG) -o $(BIN_DIR)/$(EXEC)

objects:
	$(CC) -I$(INC_DIR) $(CFLAGS) $(LIB_FLAGS) -c $(SRC_DIR)/structs.c  -o $(OBJ_DIR)/structs.o
	$(CC) -I$(INC_DIR) $(CFLAGS) $(LIB_FLAGS) -c $(SRC_DIR)/utils.c  -o $(OBJ_DIR)/utils.o
	$(CC) -I$(INC_DIR) $(CFLAGS) $(LIB_FLAGS) -c $(SRC_DIR)/ptassert.c -o $(OBJ_DIR)/ptassert.o
	$(CC) -I$(INC_DIR) $(CFLAGS) $(LIB_FLAGS) -c $(SRC_DIR)/printer.c  -o $(OBJ_DIR)/printer.o
	$(CC) -I$(INC_DIR) $(CFLAGS) $(LIB_FLAGS) -c $(SRC_DIR)/heapview.c -o $(OBJ_DIR)/heapview.o

clean:
	-rm -r $(BIN_DIR) 2>/dev/null
	-rm -r $(OBJ_DIR) 2>/dev/null
	-rm -r $(LIB_DIR) 2>/dev/null
