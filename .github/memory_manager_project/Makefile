CC = gcc
CFLAGS = -Wall -g

# Source files
SRC = memory_manager.c test_memory_manager.c
OBJ = $(SRC:.c=.o)
OUT = test_program

# Build the program
$(OUT): $(OBJ)
	$(CC) $(CFLAGS) -o $(OUT) $(OBJ)

# Clean up
clean:
	rm -f $(OBJ) $(OUT)
