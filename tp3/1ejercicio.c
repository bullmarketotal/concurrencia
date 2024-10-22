#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main(int argc, char *argv[]) {
    int num_hilos = 1;  

   
    if (argc > 1) {
        num_hilos = atoi(argv[1]);
    }

    if (num_hilos < 2) {
        printf("Ejecutando en modo secuencial (1 hilo)\n");
        num_hilos = 1;  //modo secuencial
    }

    //Primer bloque paralelo
    omp_set_num_threads(num_hilos);  //funcion para establecer la cantidad de hilos

    #pragma omp parallel
    {
        int id = omp_get_thread_num();
        int total_hilos = omp_get_num_threads();
        printf("Soy el hilo %d de %d hilos y pertenezco al primer bloque\n", id + 1, total_hilos);
    }

    //Segundo bloquue
    #pragma omp parallel num_threads(num_hilos)
    {
        int id = omp_get_thread_num();
        int total_hilos = omp_get_num_threads();
        printf("Soy el hilo %d de %d hilos y pertenezco al segundo bloque\n", id + 1, total_hilos);
    }

    return 0;
}
