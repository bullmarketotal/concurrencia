#include <mpi.h>
#include <stdio.h>
#include <string.h>

#define MESSAGE_SIZE 100

int main(int argc, char *argv[]) {
    int rank, size;
    char message[MESSAGE_SIZE];


    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0) {
        // proc raiz
        for (int i = 1; i < size; i++) {
            snprintf(message, MESSAGE_SIZE, "Hola proceso %d, este es un mensaje personalizado para ti.", i);
            MPI_Send(message, MESSAGE_SIZE, MPI_CHAR, i, 0, MPI_COMM_WORLD);
            printf("Proceso 0 envió mensaje al proceso %d: %s\n", i, message);
        }
    } else {
        // procesos que reciben el msj
        MPI_Recv(message, MESSAGE_SIZE, MPI_CHAR, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Proceso %d recibió mensaje: '%s' de proceso 0\n", rank, message);
    }

    MPI_Finalize();
    return 0;

}
