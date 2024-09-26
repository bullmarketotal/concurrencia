#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

#define MAX 500
#define MAX_HILOS 20

pthread_mutex_t mutex;
pthread_cond_t cond;

int contador = 0;

void* sumar(void* arg)

{
    for(int i =0; i< MAX; i++)
    {
        pthread_mutex_lock(&mutex);
        contador++;
        printf("SUMA: %d\n",contador);
        pthread_cond_signal(&cond);
        pthread_mutex_unlock(&mutex);
    }
    pthread_exit(NULL);
}

void* restar(void* arg)
{
    for(int i = 0; i < MAX; i++)
    {
        pthread_mutex_lock(&mutex);
        
        while (contador <= 0)
        {
            pthread_cond_wait(&cond,&mutex);
        }
        
        contador--;
        printf("RESTA: %d\n",contador),
        pthread_mutex_unlock(&mutex);   
    }
    pthread_exit(NULL);

}

int main()
{
    pthread_t sumadores[MAX_HILOS];
    pthread_t restadores[MAX_HILOS];

    for(int i = 0; i < MAX_HILOS; i++)
    {
        pthread_create(&sumadores[i],NULL, sumar, NULL);
        pthread_create(&restadores[i],NULL, restar, NULL);

    /*

    Aca probe creando los hilos en el mismo for, tenia un compoartmiento distnto pero igual el resultado era 0
    
    */
    }
 

    for(int i = 0; i < MAX_HILOS; i++)
    {
        pthread_join(sumadores[i], NULL);
        pthread_join(restadores[i], NULL);

    }


    printf("Contador: %d:", contador);
}