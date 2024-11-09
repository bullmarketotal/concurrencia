#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    int rank, size;
    int n = 1000000;  // cantidad de intervalos
    double h, local_sum = 0.0;
    double total_sum = 0.0;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // vrificar que n es divisible por el numero de procesos
    if (n % size != 0) {
        if (rank == 0) {
            printf("Error: el número de intervalos debe ser divisible por el número de procesos.\n");
        }
        MPI_Finalize();
        return 1;
    }

    //calcular el ancho de cada intervalo
    h = 1.0 / (double)n;

    //cividir el trabajo
    int local_n = n / size;  // Cada proceso calcula local_n intervalos
    int start_idx = rank * local_n;
    int end_idx = start_idx + local_n;

    //calcular la suma local
    for (int i = start_idx; i < end_idx; i++) {
        double x = (i + 0.5) * h;
        local_sum += 4.0 / (1.0 + x * x);
    }
    local_sum *= h;

    //printf("proceso %d: local_sum = %.16f\n", rank, local_sum);

    // arrayy para recolectar resultados parciales en el proceso raiz
    double* all_sums = NULL;
    if (rank == 0) {
        all_sums = (double*) malloc(size * sizeof(double));
    }

    // el proc raiz recolecta datos parciales
    MPI_Gather(&local_sum, 1, MPI_DOUBLE, all_sums, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    // luego el proceso raiz suma los resultados para obtener el valor final o aprox de PI
    if (rank == 0) {
        for (int i = 0; i < size; i++) {
            total_sum += all_sums[i];
        }
        printf("Valor aproximado de PI: %.16f\n", total_sum);
        free(all_sums);  // Liberar memoria
    }

    //qepd
    MPI_Finalize();
    return 0;
}

