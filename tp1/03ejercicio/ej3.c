#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

/*EJERCICIO 3
 * Escriba un programa llamado ej3.c que genere N cantidad de hilos, siendo N una
constante (al menos mayor a 10). Cree un arreglo de enteros de N posiciones, el cual se
va a inicializar con valores aleatorios. El proceso principal dispone de una variable
global. Cada hilo tiene que sumarle a esa variable global, el valor correspondiente de su
posición en el arreglo. Por ejemplo si se está ejecutando el hilo número tres, usara el
valor del arreglo que este en la posición 3. Tenga en cuenta que los arreglos se inician en
la posición cero. El proceso debe esperar la finalización de todos los hilos y mostrar el
valor resultante en la variable global
*/

#define CANT_HILOS  15
int contador = 0;
int h_array[CANT_HILOS];

void *suma_contador(void *arg)
{
	int index = *(int *)arg;
	int value = h_array[index];

	contador += value;
	pthread_exit(NULL);	

}
int main()
{
	pthread_t hilos[CANT_HILOS];
	int indices[CANT_HILOS];

	for(int i = 0; i < CANT_HILOS; i++)
	{
		h_array[i] = rand()% 100;
		printf("valor: %d\n", h_array[i]);
		indices[i] = i;
	}
	
	for(int i = 0; i < CANT_HILOS;i++)
	{
		pthread_create(&hilos[i], NULL, suma_contador,&indices[i]);

	}

	for(int i = 0; i < CANT_HILOS; i++)
	{
		pthread_join(hilos[i], NULL);
	}

	
	printf("Valor del contador %d\n: ", contador);
	return 0;
}

