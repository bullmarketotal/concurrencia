#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#define MAX 100
/* 
 EJERCICIO 2

Cree un programa llamado ej2.c que defina un arreglo de enteros. Genere un hilo que
inicialice el arreglo con valores aleatorios. Al finalizar, el proceso principal debe mostrar por consola los valores del arreglo de forma secuencial. El tamaño del arreglo será
suministrado por medio de un argumento al programa. */

int *array;
int size;

void* llenar_array(void* arg)
{
	for( int i = 0; i < size; i++)
	{
		array[i] = rand() % MAX; 
	
	}

	return NULL;


}
int main(int argc, char *argv[])
{

	pthread_t hilo;
	size = atoi(argv[1]);
	if (size <= 0)
	 {
        	printf("El tamaño del arreglo tiene que ser mayor a 0. \n");
        	return 1;
   	 }

	array = malloc(size * sizeof(int));

	pthread_create(&hilo,NULL,llenar_array, NULL);
	pthread_join(hilo,NULL);

	for(int i = 0; i < size; i++)
	{
		printf("%d\n", array[i]);
	}

	free(array);

	return 0;

}
