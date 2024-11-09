#include <mpi.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MESSAGE_SIZE 100

//cadena a mayusc
void to_uppercase(char *str) {
    for (int i = 0; str[i]; i++) {
        str[i] = toupper(str[i]);
    }
}

int main(int argc, char *argv[]) {
    int rank, size;
    char message[MESSAGE_SIZE];


    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // compruebo si hay 20 proc
    if (size < 20) {
        if (rank == 0) {
            printf("Se requieren al menos 20 procesos.\n");
        }
        MPI_Finalize();
        return 0;
    }

    if (rank % 2 == 0) {
        //procesos pares envían un mensaje a su proceso impar consecutivo
        snprintf(message, MESSAGE_SIZE, "Mensaje desde el proceso %d", rank);
        MPI_Send(message, MESSAGE_SIZE, MPI_CHAR, rank + 1, 0, MPI_COMM_WORLD);
        printf("Proceso %d envió: %s\n", rank, message);

        //  recibir la respuesta en mayusculas del proceso impar
        MPI_Recv(message, MESSAGE_SIZE, MPI_CHAR, rank + 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Proceso %d recibió respuesta: %s\n", rank, message);

    } else {
        // los impares reciben el mensaje, lo convierten a mayusculas y lo envían de vuelta
        MPI_Recv(message, MESSAGE_SIZE, MPI_CHAR, rank - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Proceso %d recibió: %s\n", rank, message);

        // convertir mensaje a mayusculas
        to_uppercase(message);
        MPI_Send(message, MESSAGE_SIZE, MPI_CHAR, rank - 1, 0, MPI_COMM_WORLD);
        printf("Proceso %d envió respuesta: %s\n", rank, message);
    }

    
    MPI_Finalize();
    return 0;
}
