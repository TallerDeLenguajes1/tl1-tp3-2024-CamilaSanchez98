#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TAMA 100 //tamanio de cada palabra

void solicitarNombres(char *Buff[], int cantidadNombres);
void mostrarNombres(char *Buff[],int cantidadNombres);
void reservarDinamicamente(char *Buff[],int cantidadNombres);
void liberar(char *Buff[],int cantidadNombres);

int main(){

    int totalNombres;
    printf("nombres a cargar: %d\n", totalNombres);
    printf("Ingrese la cantidad de nombres a cargar:\n");
    scanf("%d", &totalNombres);
    printf("nombres a cargar: %d\n", totalNombres);

    //un arreglo es un puntero y un puntero que apunta a un arrglo es un puntero doble
    char *Buff[totalNombres]; // Buff es un puntero que apunta a un arreglo estatico de punteros que apuntan a cadenas de caracteres
    reservarDinamicamente(Buff,totalNombres); //como quiero trabajar con el areglo que tiene las cadenas, paso el puntero que me apunta al arreglo
    solicitarNombres(Buff,totalNombres);
    mostrarNombres(Buff,totalNombres);
    liberar(Buff,totalNombres);
    return 0;
}

void solicitarNombres(char *Buff[],int cantidadNombres){ //recibe un puntero doble, y que *Buff[] apunta a 
    printf("---------------Cargar------------------\n");
    for (int i = 0; i < cantidadNombres; i++)
    {
        fflush(stdin);
        printf("Ingrese el nombre:");
        gets(Buff[i]);
    }
    
}
void mostrarNombres(char *Buff[],int cantidadNombres){
    printf("-------------Mostrar--------------------\n");
    for (int i = 0; i < cantidadNombres; i++)
    {
        printf("Nombre[%d]:\n", i);
        puts(Buff[i]);
    }
    
}
void reservarDinamicamente(char *Buff[],int cantidadNombres){
    printf("--------------Reservar-------------------\n");
    for (int i = 0; i < cantidadNombres; i++)
    {
        Buff[i]= (char*)malloc(TAMA*sizeof(char));
    }
    
}
void liberar(char *Buff[],int cantidadNombres){
    printf("---------------Liberar------------------\n");
    for (int i = 0; i < cantidadNombres; i++)
    {
        free(Buff[i]);
    }
    free(Buff);
}
