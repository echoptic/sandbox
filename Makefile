CC = gcc
FLAGS = -g -Wall

INCLUDE = -I include/
LIBS = -L lib/ -lSDL2main -lSDL2

SOURCES = $(wildcard src/*.c) $(wildcard src/**/*.c)
OBJECTS = $(SOURCES:.c=.o)

BIN = bin/main

.PHONY: all clean run

all: $(OBJECTS)
	$(CC) $(FLAGS) $(INCLUDE) $(OBJECTS) $(LIBS) -o $(BIN)

$(OBJECTS): src/%.o: src/%.c
	$(CC) $(FLAGS) $(INCLUDE) -c $< -o $@

clean:
	rm -rf src/*.o src/**/*.o

run: all
	$(BIN)
