CC = gcc
CFLAGS = -Wall -Wextra -pthread -g
SRC = main.c config/mod.c config/cli.c config/utils.c file/mod.c file/utils.c file/input_processing.c mutations/mod.c $(wildcard mutations/functions/*.c)
OBJ_DIR = build
OBJ = $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))
EXEC = evo

all: build $(EXEC)

build:
	@mkdir -p $(OBJ_DIR)/config $(OBJ_DIR)/file $(OBJ_DIR)/mutations/functions

$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) -o $(EXEC) $(OBJ)

$(OBJ_DIR)/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/config/%.o: src/config/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/file/%.o: src/file/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/mutations/functions/%.o: src/mutations/functions/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR) $(EXEC)

.PHONY: all clean
