#include <stdio.h>
#include <omp.h>
#include <unistd.h>  

void funcion_tiempo_1() {
    printf("Ejecutando funcion_tiempo_1\n");
    sleep(1);  //Pausa de 1 segundo
    printf("Funcion_tiempo_1 ha terminado\n");
}

void funcion_tiempo_2() {
    printf("Ejecutando funcion_tiempo_2\n");
    sleep(2);  //Pausa de 2 segundos
    printf("Funcion_tiempo_2 ha terminado\n");
}

int main() {
    double inicio, fin, tiempo_total;

    //Iniciar el cronómetro
    inicio = omp_get_wtime();

    //Bloque paralelo con secciones
    #pragma omp parallel sections
    {
        #pragma omp section
        {
            funcion_tiempo_1();
        }

        #pragma omp section
        {
            funcion_tiempo_2();
        }
    }

    //Detener cronómetro
    fin = omp_get_wtime();

    //Calcular el tiempo total de ejecución
    tiempo_total = fin - inicio;

    printf("El tiempo total de ejecución fue: %f segundos\n", tiempo_total);

    return 0;
}
