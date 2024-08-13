BINARY = programa
OBJ = ej1.o
LIBS = pthread.h

all: $(BINARY)

$(BINARY): $(OBJ)
	gcc -o $(BINARY) $(OBJ) -pthread

ej1.o: ej1.c 
	gcc -c ej1.c -Wall

clean:
	rm -rf $(BINARY) $(OBJ)

