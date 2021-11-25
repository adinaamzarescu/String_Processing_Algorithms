CC=gcc
CFLAGS=-std=c99 -Wall -Wextra -g
RK=Rabin_Karp
KMP=Knuth_Morris_Pratt

build: rk kmp

run-best:
	./kmp
run-p1:
	./kmp
run-p2:
	./rk

rk:  $(RK).o
	$(CC) $^ -o $@

kmp: $(KMP).o
	$(CC) $^ -o $@

$(RK).o: $(RK).c
	$(CC) $(CFLAGS) $^ -c

$(KMP).o: $(KMP).c
	$(CC) $(CFLAGS) $^ -c

.PHONY: build clean

clean:
	rm -f *.o kmp rk