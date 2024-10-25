#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

int A = 0, B = 0;

pthread_mutex_t mutex_A, mutex_B, mutex_AB; 

void *h1(void *arg) 
{
    while (1) 
    {
        pthread_mutex_lock(&mutex_A);  
        A += 1;
        printf("H1 - Valor de A: %d\n", A);
        pthread_mutex_unlock(&mutex_A); 
        sleep(1);
    }
    return NULL;
}

void *h2(void *arg)
 {
    while (1) 
    {
        pthread_mutex_lock(&mutex_B);  
        B += 20;
        printf("H2 - Valor de B: %d\n", B);
        pthread_mutex_unlock(&mutex_B); 
        sleep(1);
    }
    return NULL;
}

void *h3(void *arg) 
{
    while (1)
     {
        pthread_mutex_lock(&mutex_AB);  
        pthread_mutex_lock(&mutex_A);   
        pthread_mutex_lock(&mutex_B);   

        A += 100;
        B += 100;
        printf("H3 - Valor de A: %d\n", A);
        printf("H3 - Valor de B: %d\n", B);

        pthread_mutex_unlock(&mutex_B);  
        pthread_mutex_unlock(&mutex_A);  
        pthread_mutex_unlock(&mutex_AB); 
        sleep(1);
    }
    return NULL;
}

int main() 
{
    pthread_t threads_h1[6], threads_h2[6], threads_h3[6];

    pthread_mutex_init(&mutex_A, NULL);
    pthread_mutex_init(&mutex_B, NULL);
    pthread_mutex_init(&mutex_AB, NULL);

    for (int i = 0; i < 6; i++) 
    {
        pthread_create(&threads_h1[i], NULL, h1, NULL);
        pthread_create(&threads_h2[i], NULL, h2, NULL);
        pthread_create(&threads_h3[i], NULL, h3, NULL);
    }

    for (int i = 0; i < 6; i++) 
    {
        pthread_join(threads_h1[i], NULL);
        pthread_join(threads_h2[i], NULL);
        pthread_join(threads_h3[i], NULL);
    }

    pthread_mutex_destroy(&mutex_A);
    pthread_mutex_destroy(&mutex_B);
    pthread_mutex_destroy(&mutex_AB);

    return 0;
}
