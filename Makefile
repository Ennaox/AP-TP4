CC = gcc
CFLAGS = -O3 -Wall -Wextra -g

.PHONY: clean all

all: main

debug: main
	gbd ./main

run: main
ifndef BYTES
	@echo "BYTES is not defined"
else 
	 ./$< $(BYTES)
endif

bench: main
	./bench.sh

main:
	$(CC) $(CFLAGS) $^ -o $@ -lm

clean: 
	rm -f main