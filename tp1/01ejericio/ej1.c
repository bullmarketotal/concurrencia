#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

/*
 
 EJERICIO 1

 Escriba un programa llamado ej1.c que tenga un único contador y tres hilos para
modificar su valor. Uno de esos hilos, incrementa el contador en 2 en cada iteración y
muestra su valor en pantalla, mientras que los dos hilos restantes, lo decrementa en 1 y
muestra su valor en pantalla. Ejemplo “Hilo 1 incremento el contador al valor de 25”

*/
int contador = 0;
void* contadorr(void* arg)
{
	
	int hilo_num = *((int*)arg);
	for(int i = 0; i < 10; i++)
	{
		if(hilo_num == 0)
		{
			contador = contador + 2;
			printf("hilo %d incremento el contador en 2. Valor del contador %d\n",hilo_num + 1, contador);
			
		}
		else
		{
			contador = contador -1;
			printf("hilo %d descremento el contador en 1. Valor del contador: %d\n", hilo_num + 1,contador);
			
		}

	}
	
	return NULL;
}


int main(){
	pthread_t hilos[3];
	int indices[3];

	for(int i = 0; i < 3; i++){
		indices[i] = i;
	}

	pthread_create(&hilos[0],NULL, contadorr, &indices[0]);
	pthread_create(&hilos[1],NULL, contadorr, &indices[1]);
	pthread_create(&hilos[2],NULL, contadorr, &indices[2]);
	
	for(int i = 0; i < 3; i++)
       	{
        	pthread_join(hilos[i], NULL);
    	}

	return 0;
}



