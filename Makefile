gs = gs
FLAGS = -g3 -Wall
SOURCE = $(wildcard *.c)
OBJECT = $(subst .c,.o,$(SOURCE))
CC = gcc $(FLAGS) 
MAKE: $(OBJECT)
	$(CC) $(SOURCE) -o $(gs)
clean:
	rm *.o
	rm $(gs)

