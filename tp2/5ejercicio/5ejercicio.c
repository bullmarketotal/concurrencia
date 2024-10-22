#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <time.h>

sem_t puente, mutex;    
int autos_en_puente = 0;  
int direccion = -1;       // 0 para norte, 1 para sur, -1 para no definido

void* cruzar_auto(void* arg, int direccion_auto) 
{
    int id = *((int*) arg);
    free(arg);

    int tiempo_espera = rand() % 30 + 1;
    sleep(tiempo_espera); 

    if (direccion_auto == 0) 
    {
        printf("Auto %d del norte quiere cruzar.\n", id);
    } else {
        printf("Auto %d del sur quiere cruzar.\n", id);
        }   

    sem_wait(&mutex);
    if (autos_en_puente == 0) 
    {
        direccion = direccion_auto;
    }

    while (direccion != direccion_auto) 
    {
        sem_post(&mutex);
        sem_wait(&puente);
        sem_wait(&mutex); 
    }

    autos_en_puente++;
    sem_post(&mutex);

    if (direccion_auto == 0) 
    {
        printf("Auto %d del norte está cruzando el puente.\n", id);
    } else {
        printf("Auto %d del sur está cruzando el puente.\n", id);
        }

    usleep(400000);  

    sem_wait(&mutex);
    autos_en_puente--;

    if (autos_en_puente == 0)
     {
        direccion = -1;
        for (int i = 0; i < 3; i++) 
        {
            sem_post(&puente);
        }
    }
    sem_post(&mutex);

    if (direccion_auto == 0)
     {
        printf("Auto %d del norte cruzp el puente.\n", id);
    } 
    else {
        printf("Auto %d del sur cruzo el puente.\n", id);
        }
    pthread_exit(NULL);
}
void* auto_norte(void* arg) 
{

    return cruzar_auto(arg, 0);  // 0 para norte

}

void* auto_sur(void* arg) 
{

    return cruzar_auto(arg, 1);  // 1 para sur
    
}

int main(int argc, char* argv[]) 
{
    if (argc != 2)
    {
        printf("Uso: %s <cantidad de autos>\n", argv[0]);
        return 1;
    }

    int cantidad_autos = atoi(argv[1]);
    srand(time(NULL));  
    sem_init(&puente, 0, 0);
    sem_init(&mutex, 0, 1);

    pthread_t hilos[cantidad_autos * 2];
    

    for (int i = 0; i < cantidad_autos; i++) 
    {
        int* id_norte = malloc(sizeof(int));
        *id_norte = i + 1;
        pthread_create(&hilos[i], NULL, auto_norte, id_norte);
        int* id_sur = malloc(sizeof(int));
        *id_sur = i + 1;
        pthread_create(&hilos[cantidad_autos + i], NULL, auto_sur, id_sur);
    }

    for (int i = 0; i < cantidad_autos * 2; i++) 
    {
        pthread_join(hilos[i], NULL);
    }

    sem_destroy(&puente);
    sem_destroy(&mutex);

    return 0;
}
