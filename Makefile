CC=gcc
CPPFLAGS=
CFLAGS= -std=c99 -Wall -pedantic -Iinclude -lm -g
LDFLAGS=

all: src/*.c
	$(CC) $^ $(CFLAGS) $(LDFLAGS) -o bin/knn

clean: 
	rm bin/knn
