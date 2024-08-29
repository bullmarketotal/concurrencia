# Nombre del compilador
CC = gcc

# Opciones de compilación
CFLAGS = -Wall -pthread

# Nombre del archivo ejecutable
TARGET = ej4

# Comandos para construir el ejecutable
$(TARGET): ej4.o
	$(CC) $(CFLAGS) -o $(TARGET) ej4.o

# Comando para compilar el archivo fuente en un archivo objeto
ej4.o: ej4.c
	$(CC) $(CFLAGS) -c ej4.c

# Comando para limpiar archivos generados durante la compilación
clean:
	rm -f *.o $(TARGET)

# Comando "phony" para evitar conflictos con archivos que puedan tener el mismo nombre
.PHONY: clean

