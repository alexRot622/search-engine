CC = gcc
SRC = utils.c stack.c search.c parse.c main.c
EXEC = search
FLAGS = -Wall -Wextra -lm -o

all:
	$(CC) $(FLAGS) $(EXEC) $(SRC)
clean:
	rm $(EXEC)
