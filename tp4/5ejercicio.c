#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>


#define N 12  //tamaño de la matriz
#define STEPS 10  


void imprimirMatrix(int matrix[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}


int contadorDeVecinos(int matrix[N][N], int i, int j) {
    int count = 0;
    for (int x = -1; x <= 1; x++) {
        for (int y = -1; y <= 1; y++) {
            if (x == 0 && y == 0) continue; 
            int ni = i + x;
            int nj = j + y;
            if (ni >= 0 && ni < N && nj >= 0 && nj < N && matrix[ni][nj] == 1) {
                count++;
            }
        }
    }
    return count;
}


void generadorDeVida(int matrix[N][N], int new_matrix[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            int vecinos = contadorDeVecinos(matrix, i, j);
            if (matrix[i][j] == 1) {
                new_matrix[i][j] = (vecinos == 2 || vecinos == 3) ? 1 : 0;
            } else {
                new_matrix[i][j] = (vecinos == 3) ? 1 : 0;
            }
        }
    }
}

int main(int argc, char *argv[]) {
    int rank, size;
    int matrix[N][N], new_matrix[N][N];
    int block_size;
    int start_row, end_row;


    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);


    if (N % size != 0) {
        if (rank == 0) {
            printf("El número de procesos debe dividir el tamaño de la matriz\n");
        }
        MPI_Finalize();
        return 0;
    }

    block_size = N / size; 


    int local_matrix[block_size][N];


    if (rank == 0) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                matrix[i][j] = rand() % 2;
            }
        }
        printf("Matriz inicial:\n");
        imprimirMatrix(matrix);
    }


    MPI_Scatter(matrix, block_size * N, MPI_INT, local_matrix, block_size * N, MPI_INT, 0, MPI_COMM_WORLD);


    for (int step = 0; step < STEPS; step++) {

        generadorDeVida(local_matrix, new_matrix);


        if (rank > 0) {
            MPI_Send(local_matrix + (block_size - 1) * N, N, MPI_INT, rank - 1, 0, MPI_COMM_WORLD);
        }
        if (rank < size - 1) {
            MPI_Recv(local_matrix + block_size * N, N, MPI_INT, rank + 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        }
        if (rank < size - 1) {
            MPI_Send(local_matrix + block_size * N, N, MPI_INT, rank + 1, 0, MPI_COMM_WORLD);
        }
        if (rank > 0) {
            MPI_Recv(local_matrix, N, MPI_INT, rank - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        }

        MPI_Barrier(MPI_COMM_WORLD);


        for (int i = 0; i < block_size; i++) {
            for (int j = 0; j < N; j++) {
                local_matrix[i + rank * block_size][j] = new_matrix[i + rank * block_size][j];
            }
        }

     
        if (rank == 0) {
            printf("Paso %d:\n", step + 1);
            imprimirMatrix(matrix);
        }

        MPI_Barrier(MPI_COMM_WORLD);  
    }

    MPI_Finalize();
    return 0;
}
