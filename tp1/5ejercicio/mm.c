/* Introducción a la Concurrencia
 *
 * Ejemplo de multiplicación de matrices.
 * Programa concurrente.
 * Probar distintas ejecuciones cambiando la constante N y
 * habilitando o deshabilitando los printf.
 *
 * Compilar con:
 *
 * make
 *
 * Ejecutar con:
 *
 * ./mm
 *
 * Para medir tiempo completo de ejecución:

 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <errno.h>

// Hasta N = 381 funciona bien en esta VERSION CONCURRENTE del programa en mi notebook 32bits,
// usando el tamaño por defecto para la pila de los hilos (8192, ver ulimits -s). Este
// tamaño se puede reducir utilizando pthread_attr_setstacksize()
//
// En una PC 64 bits, cuad core, con 6GB de RAM, el limite es mucho mas grande. Por ejemplo, con 1024 funcionó bien, y tardó unos 6,7 segundos en resolver correctamente la multiplicación.
#define N 1024
//#define N 8
//#define N 381

double a[N][N];
double b[N][N];
double c[N][N];

pthread_t hilos[N];

typedef struct
{
	int init_fila;
	int end_fila;

} HilosData;

void iniMat(double mat[][N], int len, double iniVal)
{
        int i, j;

        for(i = 0; i < len; ++i)
                for(j = 0; j < len; ++j)
                        mat[i][j] = iniVal;
}

/* Check1Mat: Chequea que la matriz resultante quede con
 *            el mismo valor en todas sus celdas.
 * Es un chequeo básico para el caso particular en que
 * se sabe de ante mano que el resultado tendrá esa forma.
 * Retorna: 0 en caso correcto (todas las celdas contiene
 *          finVal. 1 En caso de error (al menos una celda
 * contiene un valor diferente de finVal).
 */
int Check1Mat(double mat[][N], int len, double finVal)
{
        int i, j;

        for(i = 0; i < len; ++i)
                for(j = 0; j < len; ++j)
                        if(mat[i][j] != finVal)
                                return 1;
        return 0;
}

void printMat(double mat[][N], int len)
{
        int i, j;

        for(i = 0; i < len; ++i)
        {
                for(j = 0; j < len; ++j)
                        printf( "%.1f ", mat[i][j]);
                printf("\n");
        }
}

void *worker(void *arg)
{
	HilosData *data = (HilosData *) arg;
        int init_fila = (*data).init_fila;
	int end_fila = (*data).end_fila;
	int i,j,k;

	for(i = init_fila; i < end_fila; ++i)
	{
		for ( j = 0; j < N; ++j)
		{
			for(k = 0; k < N; k++)
			{
				c[i][j] = a[i][k] * b[k][j];
			}
		}
	}
	return NULL;
}

void mm(int H) {
    pthread_t hilos[H];
    HilosData hilo_data[H];
    int filas_hilo = N / H;
    int i, retval;

    for(i = 0; i < H; ++i) 
    {
        hilo_data[i].init_fila = i * filas_hilo;
        hilo_data[i].end_fila = (i + 1) * filas_hilo;

        retval = pthread_create(&hilos[i], NULL, worker, (void *)&hilo_data[i]);
        if(retval != 0)
       	{
            perror("pthread_create");
            exit(1);
        }
    }

    for(i = 0; i < H; ++i) 
    {
        pthread_join(hilos[i], NULL);
    }
}

int main(int argc, char *argv[])
{
	if( argc != 2)
	{
		printf("Error en parametros");
		exit(1);	
	}
	int H = atoi(argv[1]);
	
	if(N%H != 0) 
	{
		printf("El parametro debe ser un divisor entero de %d\n",N);
		exit(1);
	}


        printf("Comienzo ...\n");
        iniMat(a, N, 1.0);
        iniMat(b, N, 1.0);
        iniMat(c, N, 0.0);

        printf("Multiplicando ...\n");

        mm(H);

        if(Check1Mat(c, N, N) == 0)
                printf("Fin Multiplicación (Resultado correcto)\n");
        else
                printf("Fin Multiplicación (Resultado INCORRECTO!)\n");

/*
        printf("Matriz a:\n");
        printMat(a, N);
        printf("Matriz b:\n");
        printMat(b, N);

        printf("Matriz c:\n");
        printMat(c, N);

	if(Check1Mat(c, N, N) == 0)
                printf("Fin Multiplicación (Resultado correcto)\n");
        else
                printf("Fin Multiplicación (Resultado INCORRECTO!)\n");

*/
        printf("Fin del programa\n");

}	
