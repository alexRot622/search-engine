CC = gcc
SRC = utils.c stack.c search.c parse.c main.c
EXEC = search
FLAGS = -Wall -Wextra -o

all:
	$(CC) $(FLAGS) $(EXEC) $(SRC) -lm
clean:
	rm $(EXEC)
