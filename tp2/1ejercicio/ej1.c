#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

#define MAX_N 100  // Tamaño máximo de la matriz

int matriz[MAX_N][MAX_N];  // Matriz cuadrada estática de tamaño máximo
pthread_mutex_t mutex;
pthread_cond_t cond;
int fila_actual = 0;
int N;  // Tamaño real de la matriz que se ingresará por el usuario

void* imprimir_fila(void* arg) {
    int fila = *(int*)arg;

    pthread_mutex_lock(&mutex);
    while (fila != fila_actual) {
        pthread_cond_wait(&cond, &mutex);
    }

    // Imprime la fila correspondiente
    printf("Hilo %d: ", fila + 1);
    for (int j = 0; j < N; j++) {
        printf("%d ", matriz[fila][j]);
    }
    printf("\n");

    fila_actual++;
    pthread_cond_broadcast(&cond);
    pthread_mutex_unlock(&mutex);

    pthread_exit(NULL);
}

int main() {
    printf("Ingrese el tamaño de la matriz (N x N, max %d): ", MAX_N);
    scanf("%d", &N);

    if (N > MAX_N) {
        printf("El tamaño excede el límite máximo permitido de %d.\n", MAX_N);
        return 1;
    }

    pthread_t hilos[N];
    int indices[N];  // Arreglo de índices para pasar a los hilos

    // Inicializar la matriz con algunos valores
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            matriz[i][j] = i + j;
        }
    }

    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&cond, NULL);

    // Crear los hilos
    for (int i = 0; i < N; i++) {
        indices[i] = i;
        pthread_create(&hilos[i], NULL, imprimir_fila, &indices[i]);
    }

    // Esperar a que todos los hilos terminen
    for (int i = 0; i < N; i++) {
        pthread_join(hilos[i], NULL);
    }

    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond);

    return 0;
}
