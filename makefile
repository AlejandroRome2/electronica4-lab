CC = gcc
CFLAGS = -Wall -Wextra -pedantic -std=c90 -Iinc
TARGET = build/bin/laboratorio2.exe
OBJ = build/obj/main.o build/obj/alumno.o

.PHONY: all doc clean

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET)

build/obj/main.o: src/main.c inc/alumno.h
	$(CC) $(CFLAGS) -c src/main.c -o build/obj/main.o

build/obj/alumno.o: src/alumno.c inc/alumno.h
	$(CC) $(CFLAGS) -c src/alumno.c -o build/obj/alumno.o

doc:
	doxygen Doxyfile

clean:
	rm -f build/obj/*.o build/bin/*.exe