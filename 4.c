#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXCLIENTE 100 // cantidad de clientes maximo que puede atender cada PREVENTISTA
#define MAXPRODUCTO 5  // cantidad de productos maximo que puede tener cada cliente

struct
{
    int productoID;       // Numerado en ciclo iterativo
    int cantidad;         // entre 1 y 10
    char *tipoProducto;   // Algún valor del arreglo TiposProductos
    float precioUnitario; // entre 10 - 100
} typedef Producto;

struct
{
    int clienteID;               // Numerado en el ciclo iterativo
    char *NombreCliente;         // Ingresado por usuario
    int cantidadProductosAPedir; // (aleatorio entre 1 y 5)
    Producto **productos;         // El tamaño de este arreglo depende de la variable "CantidadProductosAPedir”
}typedef Cliente;

struct{
    int cantidadClientesTotal;
    Cliente **clientes;
}typedef Preventista;

int reservarPreventistas(Preventista **preventistas);
void reservarClientes(Preventista **preventistas, int cantidadPrev);
void reservarProductos(Preventista **preventistas, int cantidadPrev);

int main()
{
    Preventista **preventistas;
    int cantidadPrev= reservarPreventistas(preventistas);
    reservarClientes(preventistas, cantidadPrev);
    // reservarProductos(preventistas, cantidadPrev);
    // cargarpreventistas(preventistas, cantidadPrev);
    // char *TiposProductos[] = {"Galletas", "Snack", "Cigarrillos", "Caramelos", "Bebidas"};

    // printf("Ingrese la cantidad de clientes: \n");

    return 0;
}

int reservarPreventistas(Preventista **preventistas){
    printf("------------------Reservar Preventistas------------------------\n");
    int cantidadPreventistas;
    printf("Ingrese la cantidad de preventistas: \n");
    fflush(stdin);
    scanf("%d", &cantidadPreventistas);
    preventistas= (Preventista**)malloc(cantidadPreventistas*sizeof(Preventista*));
    for (int i=0; i < cantidadPreventistas; i++)
    {
        preventistas[i]= (Preventista*)malloc(sizeof(Preventista));
    }
    printf("....preventistas reservados.");

    if(preventistas==NULL){
        printf("Preventistas es nulo.\n");
    }else{
        printf("Preventistas NO es nulo.\n");
    }
    for (int l = 0; l < cantidadPreventistas; l++)
    {
        if(preventistas[l]==NULL){
            printf("Preventista[%d] es nulo.\n",l);
        }else{
            printf("Preventista[%d] NO es nulo.\n",l);
        }
    }

    return cantidadPreventistas;
}

void reservarClientes(Preventista **preventistas, int cantidadPrev){
    printf("------------------Reservar Clientes------------------------\n");
    int cantidadClientes;
     if(preventistas==NULL){
        printf("Preventistas es nulo.\n");
    }else{
        printf("Preventistas NO es nulo.\n");
    }
    for (int l = 0; l < cantidadPrev; l++)
    {
        if(preventistas[l]==NULL){
            printf("Preventista[%d] es nulo.\n",l);
        }else{
            printf("Preventista[%d] NO es nulo.\n",l);
        }
    }
    for (int i = 0; i < cantidadPrev; i++)
    {
        printf("Ingrese la cantidad de clientes asociados al preventista [%d]:\n ", i);
        fflush(stdin);
        scanf("%d", &cantidadClientes);
        if (preventistas[i] != NULL) {
            printf("no soy null");
        }
        preventistas[i]->cantidadClientesTotal = cantidadClientes;
        preventistas[i]->clientes = (Cliente**)malloc(cantidadClientes*sizeof(Cliente*));
        for (int j = 0; j < cantidadClientes; j++)
        {
            preventistas[i]->clientes[j] = (Cliente*)malloc(sizeof(Cliente));
        }
    }
    printf("....clientes reservados.");
}
// void reservarProductos(Preventista **preventistas, int cantidadPrev){
//     printf("------------------Reservar Productos------------------------\n");
//     for (int i = 0; i < cantidadPrev; i++)
//     {
//         printf("----->Preventista [%d]", i);
//         int cantidadClientes = preventistas[i]->cantidadClientesTotal;
//         Cliente **aux = preventistas[i]->clientes;
//         for (int j = 0; j < cantidadClientes; j++)
//         {
//             int cantidadProductos;
//             printf("Ingrese la cantidad de productos a cargar para el cliente [%d]: \n", j);
//             fflush(stdin);
//             scanf("%d", &cantidadProductos);

//             aux[j]->cantidadProductosAPedir = cantidadProductos;
//             aux[j]->productos = (Producto*)malloc(cantidadProductos*sizeof(Producto));
//             for (int k = 0; k < cantidadProductos; k++)
//             {
//                 aux[j]->productos[k] = (Producto*)malloc(sizeof(Producto));
//             }
//         }  
//     }
//     printf("....productos reservados.");
// }
