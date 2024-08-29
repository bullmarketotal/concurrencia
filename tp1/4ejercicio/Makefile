CC = gcc

CFLAGS = -Wall -pthread

TARGET = ej4

$(TARGET): ej4.o
	$(CC) $(CFLAGS) -o $(TARGET) ej4.o

ej4.o: ej4.c
	$(CC) $(CFLAGS) -c ej4.c

clean:
	rm -f *.o $(TARGET)


