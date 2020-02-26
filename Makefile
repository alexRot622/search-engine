CC = gcc
SRC = utils.c stack.c search.c parse.c main.c
EXEC = search.out
CHK = checker.sh
FLAGS = -Wall -Wextra -lm -o

all:
	$(CC) $(FLAGS) $(EXEC) $(SRC)
clean:
	rm $(EXEC)
run:
	./$(EXEC)
test:
	$(CC) $(FLAGS) $(EXEC) $(SRC)
	chmod u+x $(CHK)
	./$(CHK) $(EXEC)
	rm $(EXEC)
