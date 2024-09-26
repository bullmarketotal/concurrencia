#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

#define MAX_N 100  

pthread_mutex_t mutex;
pthread_cond_t cond;  

int fila_actual = 0, N, matriz[MAX_N][MAX_N];

void* imprimir_fila(void* arg) 
{
    int fila = *(int*)arg;

    pthread_mutex_lock(&mutex);
    while (fila != fila_actual) 
    {
        pthread_cond_wait(&cond, &mutex);
    }
    
    printf("Hilo %d: ", fila + 1);
    for (int j = 0; j < N; j++)
    {
        printf("%d ", matriz[fila][j]);
    }
    printf("\n");

    fila_actual++;
    pthread_cond_broadcast(&cond);
    pthread_mutex_unlock(&mutex);

    pthread_exit(NULL);
}


int main() 
{
    printf("Ingrese el tamaño de la matriz (NxN): ");
    scanf("%d", &N);

    if (N > MAX_N) 
    {
        printf("El tamaño excede el maximo permitido de %d.\n", MAX_N);
        return 1;
    }

    pthread_t hilos[N];
    int indices[N];  

    for (int i = 0; i < N; i++) 
    {
        for (int j = 0; j < N; j++) 
        {
            matriz[i][j] = i + j;
        }
    }

    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&cond, NULL);

    for (int i = 0; i < N; i++) 
    {
        indices[i] = i;
        pthread_create(&hilos[i], NULL, imprimir_fila, &indices[i]);
    }

    for (int i = 0; i < N; i++) 
    {
        pthread_join(hilos[i], NULL);
    }

    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond);

    return 0;
}
