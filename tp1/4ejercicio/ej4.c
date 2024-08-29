#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

/*
 Cree un programa llamado ej4.c el cual genere dos hilos. Uno será el hilo productor y el
otro será el consumidor. EL hilo productor debe generar caracteres aleatorios y
guardarlos en un buffer. El hilo consumidor tiene que leer los valores del buffer y
mostrarlos por consola. Cuando se habla de buffer, se puede representar con un arreglo.
Como detalle a tener en cuenta:
a. Cuando el productor quiere generar un carácter y el buffer está lleno.
b. Cuando el consumidor quiere leer un carácter del buffer y el mismo está vacío.

EJERCICIO 4
 */

#define MAX_BUFFER 20
int buffer[MAX_BUFFER];
int contador = 0;

char caracter_random() // devuelve un caracter alfabetico  basado en la tabla ASCII
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

void *generar_caracteres(void *arg)
{
	while(1)
	{
		if(contador < MAX_BUFFER)
		{
			char c = caracter_random();
			buffer[contador] = c;
			contador ++;


		}
		else
		{
			printf("BUFFER LLENO \n");
		}
		sleep(1);
			
	}
	return NULL;
}

void *leer_caracteres(void *arg)
{
	while(1)
	{
		if(contador > 0)
		{
			char c = buffer[contador -  1];
			printf("Caracter leido: %c\n",c);
			contador--;

		}
		else
		{
			printf("BUFFER VACIO \n");
		}
		sleep(2);
	}
	return NULL;
}

int main()
{
	pthread_t hproductor, hconsumidor;

	pthread_create(&hproductor,NULL,generar_caracteres,NULL);
	pthread_create(&hconsumidor,NULL,leer_caracteres,NULL);	

	pthread_join(hproductor,NULL);
	pthread_join(hconsumidor,NULL);

	return 0;
}
