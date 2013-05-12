CFLAGS = -Wall -g
CC = g++

all: encrypt decrypt

encrypt: encrypt.o
	$(CC) $(CFLAGS) $^ -o $@

decrypt: decrypt.o
	$(CC) $(CFLAGS) $^ -o $@

%.o: src/%.c
	$(CC) -c $(CFLAGS) $< -o $@

.PHONY: clean

clean:
	rm -f encrypt decrypt *.o
