CC=gcc
CFLAGS=-std=c99 -Wall -Wextra -g
RK=Rabin_Karp
KMP=Knuth_Morris_Pratt

.PHONY: build clean

build: rk kmp
rk:  $(RK).o
	$(CC) $^ -o $@

kmp: $(KMP).o
	$(CC) $^ -o $@

$(RK).o: $(RK).c
	$(CC) $(CFLAGS) $^ -c

$(KMP).o: $(KMP).c
	$(CC) $(CFLAGS) $^ -c

clean:
	rm -f *.o kmp rk