#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>


#define MAX_BUFFER 100

pthread_mutex_t mutex;
pthread_cond_t no_vacio,no_lleno; 

char buffer[100];
int contador = 0, pos_escritura = 0, pos_lectura = 0;


char caracter_random() 
{
	static int contador_ = 65;
	char c = (char)contador_;
	contador_++;

	if(contador_ == 91)
	{
		contador_ = 97;
	}
    
	if(contador_ == 123)
	{
		contador_ = 65;
	}

	return c; 


}

void *productor(void *arg) 
{
    while (1) 
    {
        char item = caracter_random(); 
        pthread_mutex_lock(&mutex);    
        
        while (contador == MAX_BUFFER) 
        {
            pthread_cond_wait(&no_lleno, &mutex);  
        }
        
        
        buffer[pos_escritura] = item;
        pos_escritura = (pos_escritura + 1) % MAX_BUFFER;  
        contador++;
        printf("Productor %ld escribio: %c, contador: %d\n", (long)arg, item, contador);
        
        pthread_cond_signal(&no_vacio);  
        pthread_mutex_unlock(&mutex);    
        sleep(1);      
    }
    return NULL;
}

void *consumidor_a(void *arg) {
    sleep(10);  
    while (1) 
    {
        pthread_mutex_lock(&mutex);  
        
        while (contador == 0)
        {
            pthread_cond_wait(&no_vacio, &mutex);
        }
        
        
        char caracter = buffer[pos_lectura];
        pos_lectura = (pos_lectura + 1) % MAX_BUFFER;
        contador--;
        printf("Consumidor A leyo: %c, contador: : %d\n", caracter, contador);
        
        pthread_cond_signal(&no_lleno);
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

void *consumidor_b(void *arg) 
{
    sleep(10);
    while (1) 
    {
        pthread_mutex_lock(&mutex);  
        
        while (contador < 10) 
        {
            pthread_cond_wait(&no_vacio, &mutex);  
        }
        
        char caracter = buffer[pos_lectura];
        pos_lectura = (pos_lectura + 1) % MAX_BUFFER;
        contador--;
        printf("Consumidor B leyo: %c, contador: %d\n", caracter, contador);
        
        pthread_cond_signal(&no_lleno); 
        pthread_mutex_unlock(&mutex);        
    }
    return NULL;
}

int main()
{
    printf("INICIO \n" );
    pthread_t h_productor[2], h_consumidor[2];
    pthread_create(&h_productor[0], NULL, productor,(void*)1);
    pthread_create(&h_productor[1], NULL, productor,(void*)2);

    pthread_create(&h_consumidor[0], NULL, consumidor_a,NULL);
    pthread_create(&h_consumidor[1], NULL, consumidor_b,NULL);

    pthread_join(h_productor[0],NULL);
    pthread_join(h_productor[1],NULL);
    pthread_join(h_consumidor[0],NULL);
    pthread_join(h_consumidor[1],NULL);

    return 0;
}