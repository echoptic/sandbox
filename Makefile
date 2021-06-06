CC = gcc
FLAGS = -g -Wall

INCLUDES = -I include/
LIBS = -L lib/ -lSDL2main -lSDL2

SOURCES = $(wildcard src/*.c)
OBJECTS = $(SOURCES:.c=.o)

BIN = bin/main

all: $(OBJECTS)
	$(CC) $(FLAGS) $(INCLUDES) $(SOURCES) $(LIBS) -o $(BIN)

$(OBJECTS):
	$(CC) -c $(SOURCES) $(INCLUDES)

.PHONY: clean
clean:
	rm -rf *.o

.PHONY: run
run: all
	$(BIN)