# Nombre del ejecutable
TARGET = programa

# Compilador
CC = gcc

# Flags de compilación
CFLAGS = -Wall -pthread

# Archivos fuente
SRC = ej3.c

# Archivos objeto
OBJ = $(SRC:.c=.o)

# Regla principal
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)

# Regla para compilar los archivos fuente
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Limpiar los archivos objeto y ejecutables
clean:
	rm -f $(OBJ) $(TARGET)

