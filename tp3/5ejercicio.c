#include <stdio.h>
#include <omp.h>

int main() {
    //4 hilos
    omp_set_num_threads(4);

    #pragma omp parallel
    {
        //obtengo el id del hilo
        int id_hilo = omp_get_thread_num();

        //seccion critica
        #pragma omp critical
        {
            printf("Hilo ID: %d\n", id_hilo);
        }

        // barrera
        #pragma omp barrier

        #pragma omp critical
        {
            printf("Hilo %d ha terminado su ejecución.\n", id_hilo);
        }
    }

    return 0;
}

