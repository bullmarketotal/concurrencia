
BINARY = ej2
OBJ = ej2.o

all: $(BINARY)

$(BINARY): $(OBJ)
	gcc -o $(BINARY) $(OBJ) -pthread

ej2.o: ej2.c
	gcc -c ej2.c -Wall -pthread

clean:
	rm -rf $(BINARY) $(OBJ)

 
