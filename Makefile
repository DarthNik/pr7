CC = gcc
CFLAGS = -Wall

all: dir

dir: dir.c
	$(CC) $(CFLAGS) dir.c -o dir
clean:
	rm -rf dir
