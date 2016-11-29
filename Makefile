CC = gcc
CFLAGS = -g -Wall

FILES = main.c
OUT_EXE = main

build: $(FILES)
	$(CC) $(CFLAGS) $(FILES) -o $(OUT_EXE)
clean:
	-rm -f *.o $(OUT_EXE)
