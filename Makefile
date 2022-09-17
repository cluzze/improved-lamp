

CC=gcc
CFLAGS=-g -Wall -Wextra -Werror

main.o: main.c myassert.h
	$(CC) $(CFLAGS) -c $^

myapp: main.o
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm myapp *.o *.gch