TARGET=build

# Compiler
CC=/usr/bin/gcc

# Compilation flags
CFLAGS=-c -Wall -pedantic -std=c99

# Linker flags
LFLAGS= 

# Executable filename
EXECUTABLE=lab23

# Source code files
SOURCES=main.c logs.c tree.c enum.c

# Object files
OBJECTS=$(SOURCES:.c=.o)

all: $(TARGET)

build: $(OBJECTS)
	$(CC) $(LFLAGS) $(OBJECTS) -o $(EXECUTABLE) 

main.o: main.c
	$(CC) $(CFLAGS) main.c

enum.o: enum.c enum.h
	$(CC) $(CFLAGS) enum.c

logs.o: logs.c logs.h
	$(CC) $(CFLAGS) logs.c

tree.o: tree.c tree.h
	$(CC) $(CFLAGS) tree.c

clean:
	rm -f $(OBJECTS)

run: build
	./$(EXECUTABLE)