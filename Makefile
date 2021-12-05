CC = gcc
CFLAGS = -O3 -funroll-loops -Wall -Wextra -g

.PHONY: clean all

all: main

bench: main
	./main 100000

debug: main
	gbd ./main

run: main
ifndef BYTES
	@echo "BYTES is not defined"
else 
	 ./$< $(BYTES)
endif

main: main.c
	$(CC) $(CFLAGS) $^ -o $@ -lm

clean: 
	rm -f main
