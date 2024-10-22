#include <stdio.h>
#include <omp.h>

int main() {
    int i;
    int num_hilos;

    //Establecer la cantidad de hilos o cambiar el numero 
    omp_set_num_threads(4);  //Establecer numero hilos a 4 para este ejercicio

    #pragma omp parallel private(i)  //Bloque paralelo
    {
        num_hilos = omp_get_num_threads();  //Obtener la cantidad de hilos

        #pragma omp for schedule(dynamic, 15)  //Distribuir iteraciones en bloques de 15
        for (i = 0; i < 100; i++) {
            int id_hilo = omp_get_thread_num();  //Obtener el ID del hilo
            printf("Hilo %d ejecutando iteración %d\n", id_hilo, i);
        }
    }

    return 0;
}
