/*
Una empresa necesita simular la producción de los próximos 5 años para tal fin necesita
generar una matriz (estática) de 5x12 donde cada fila corresponde a un año y cada columna
es un mes. Ud. debe realizar las siguientes tareas:
a. Cargue dicha matriz con valores aleatorios entre 10000 y 50000.
b. Muestre por pantalla los valores cargados
c. Saque el promedio de ganancia por año y muestrelos por pantalla
d. Obtenga el valor máximo y el valor mínimo obtenido informando el “año” y el “mes” de
cuándo ocurrió.
*/

#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define ANIO 5
#define MES 12

void cargarMatriz(int matriz[ANIO][MES]);
void mostrarMatriz(int matriz[ANIO][MES]);
void calcularPromedio(int matriz[ANIO][MES]);
void maxYmin(int matriz[ANIO][MES]);


int main(){
    srand(time(NULL));
    
    int matriz[ANIO][MES];

    cargarMatriz(matriz);
    mostrarMatriz(matriz);
    calcularPromedio(matriz);
    maxYmin(matriz);

    return 0;
}

void cargarMatriz(int matriz[ANIO][MES]){

    for (int i = 0; i < ANIO; i++)
    {
        for (int j = 0; j < MES; j++)
        {
            matriz[i][j]= rand()%(50000-10000+1)+10000; //Num entre 10000 y 50000
        }
        
    }
}

void mostrarMatriz(int matriz[ANIO][MES]){

    for (int i = 0; i < ANIO; i++)
    {
        for (int j = 0; j < MES; j++)
        {
            printf("ELEMENTO [%d][%d]: %d\n", i,j, matriz[i][j]);
        }
        
    }
}

void calcularPromedio(int matriz[ANIO][MES]){
    int promedio = 0;
    for (int i = 0; i < ANIO; i++)
    {
        for (int j = 0; j < MES; j++)
        {
            promedio+= matriz[i][j];
        }
        promedio/=MES;
        printf("El promedio del anio %d es: %d\n", i+1, promedio);
        promedio = 0;
    }
}

void maxYmin(int matriz[ANIO][MES]){
    int max = matriz[0][0];
    int min = matriz[0][0];
    int mesMax = 0;
    int anioMax = 0;
    int mesMin = 0;
    int anioMin = 0;

    for (int i = 0; i < ANIO; i++)
    {
        for (int j = 0; j < MES; j++)
        {
            if(max < matriz[i][j]){
                max=matriz[i][j];
                anioMax=i;
                mesMax=j;
            }
            if(matriz[i][j] <min){
                min=matriz[i][j];
                anioMin=i;
                mesMin=j;
            }
        }
    }
    printf("El maximo es: %d\n", max);
    printf("El anio del maximo es: %d\n", anioMax+1); //le sumo 1 xq el anio es de 1 a 5, no de 0 a 4
    printf("El mes del maximo es: %d\n", mesMax+1);
    printf("El minimo es: %d\n", min);
    printf("El anio del minimo es: %d\n", anioMin+1);
    printf("El mes del minimo es: %d\n", mesMin+1);
}