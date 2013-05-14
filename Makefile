CFLAGS = -Wall -g
CC = g++
LFLAGS = -I/usr/include/botan-1.10/
LDFLAGS = -lbotan-1.10 -lgcrypt -lcryptopp

all: process test

test: test.o botan.o gcrypt.o cryptopp.o util.o
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

process: process.o botan.o gcrypt.o cryptopp.o util.o
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

%.o: src/%.c
	$(CC) -c $(CFLAGS) $(LFLAGS) $< -o $@

.PHONY: clean

clean:
	rm -f process test *.o
