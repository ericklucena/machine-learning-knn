CC=gcc
CPPFLAGS=
CFLAGS= -std=c99 -Wall -pedantic -Iinclude -lm -g
LDFLAGS=

knn: src/knn.c src/knn_main.c 
	$(CC) $^ $(CFLAGS) $(LDFLAGS) -o bin/knn

vdm: src/vdm.c src/vdm_main.c 
	$(CC) $^ $(CFLAGS) $(LDFLAGS) -o bin/vdm

clean: 
	rm bin/knn
	rm bin/vdm
