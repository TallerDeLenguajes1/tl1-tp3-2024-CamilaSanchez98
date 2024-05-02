#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#define MAXCLIENTE 100 // cantidad de clientes maximo que puede atender cada PREVENTISTA
#define MAXPRODUCTO 5  // cantidad de productos maximo que puede tener cada cliente
#define LONGNOMBRE 100

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
    Producto *productos;         // El tamaño de este arreglo depende de la variable "CantidadProductosAPedir”
}typedef Cliente;

struct{
    int cantidadClientesTotal;
    Cliente *clientes;
}typedef Preventista;

int reservarPreventistas(Preventista **pDoblePreventistas);
void reservarClientes(Preventista **pDoblePreventistas, int cantidadPrev);
void reservarProductos(Preventista **pDoblePreventistas, int cantidadPrev);
void cargarClientes(Preventista **pDoblePreventistas, int cantidadPrev);
Producto* buscarProducto(Preventista **pDoblePreventistas, int id, int cantidadPrev);//agrego para desde el main mandarle un id
float costoTotal(Producto **producto);
int costoFinalProductos(Preventista ** pDoblePreventistas,int cantidadPrev);
void mostrarTodo(Preventista **pDoblePreventistas, int cantidadPrev);
void liberar(Preventista **pDoblePreventistas, int cantidadPrev);

int main()
{
    srand(time(NULL));

    Preventista *pPreventistas = NULL; //es un puntero que me apunta a un arreglo que contentrá structs Preventistas
    int cantidadPrev= reservarPreventistas(&pPreventistas); //debo pasar una direccion de memoria del puntero que me apunta al arreglo de preventistas para poder hacerle la reserva al arreglo desde la funcion

    reservarClientes(&pPreventistas, cantidadPrev);
    reservarProductos(&pPreventistas, cantidadPrev);
    cargarClientes(&pPreventistas, cantidadPrev);
    mostrarTodo(&pPreventistas,cantidadPrev);

    printf("Ingresar el ID del producto que desea buscar:\n");
    int id;
    scanf("%d",&id);
    fflush(stdin);
    Producto *pProductoBuscado = buscarProducto(&pPreventistas,id,cantidadPrev);

    if(pProductoBuscado!=NULL){
        float costo= costoTotal(&pProductoBuscado);
        printf("El costo total del producto de ID:%d  es: $ %.2f\n", pProductoBuscado->productoID, costo); 
        //float con dos decimales
    }else{
        printf("ERROR. Producto no encontrado.\n");
    }

    liberar(&pPreventistas,cantidadPrev);
    return 0;
}

int reservarPreventistas(Preventista **pDoblePreventistas){
    //pido un puntero doble ya que el puntero éste me apuntará a la direccion en memoria del puntero
    //que me apunta al arreglo que tiene los struct preventistas.

    printf("------------------Reservar Preventistas------------------------\n");
    int cantidadPreventistas;
    printf("Ingrese la cantidad de preventistas: \n");
    scanf("%d", &cantidadPreventistas);
    fflush(stdin);
    *pDoblePreventistas= (Preventista*) malloc(cantidadPreventistas*sizeof(Preventista));
    //el contenido de mi pDoble es el puntero que apunta al arreglo
    printf("....preventistas reservados.\n");;

    return cantidadPreventistas;
}
void reservarClientes(Preventista **pDoblePreventistas, int cantidadPrev){
    printf("------------------Reservar Clientes------------------------\n");
    int cantidadClientes;
    //al contenido del pDoble, que es el puntero que me apunta al arreglo que tiene los preventistas, 
    //lo guardo en un puntero del mismo tipo auxiliar
    Preventista *aux = *pDoblePreventistas;

    for (int i = 0; i < cantidadPrev; i++)
    {
        printf("Ingrese la cantidad de clientes asociados al preventista [%d]:\n ", i);
        scanf("%d", &cantidadClientes);
        fflush(stdin);
        
        //aux apunta al arreglo, puedo indexarlo para recorrerlo
        Preventista *prevActual = &aux[i];
        prevActual->cantidadClientesTotal = cantidadClientes;
        prevActual->clientes = (Cliente*)malloc(cantidadClientes*sizeof(Cliente));    
    }
    printf("....clientes reservados.\n");
}

void reservarProductos(Preventista **pDoblePreventistas, int cantidadPrev){
    printf("------------------Reservar Productos------------------------\n");
    Preventista *aux = *pDoblePreventistas;
    int cantidadProductos;
    for (int i = 0; i < cantidadPrev; i++)
    {
        printf("----->Preventista [%d]: \n", i);
        Preventista *prevActual = &aux[i];
        int cantidadClientes= prevActual->cantidadClientesTotal;
        for (int j = 0; j < cantidadClientes; j++)
        {
            //cantidad de productos a pedir , num aleatorio entre 1 y 5
            cantidadProductos = rand()%5+1;

            Cliente *clienteActual = &(prevActual->clientes[j]);
            clienteActual->cantidadProductosAPedir = cantidadProductos;
            clienteActual->productos = (Producto*)malloc(cantidadProductos*sizeof(Producto));
        }  
    }
    printf("....productos reservados.\n");
}
void cargarClientes(Preventista **pDoblePreventistas, int cantidadPrev){
    printf("------------------Cargar Clientes------------------------\n");
    Preventista *aux = *pDoblePreventistas;
    int cantidadProductos;
    char *nombre; //puntero que apunta a ...
    char *Buff; //variable auxiliar
    Buff= (char *) malloc(LONGNOMBRE*sizeof(char));
    char *TiposProductos[] = {"Galletas","Snack","Cigarrillos","Caramelos","Bebidas"};
    int contadorCliente = 0;
    int contadorProd= 0;
    for (int i = 0; i < cantidadPrev; i++)
    {
        printf("----->Preventista [%d]: \n", i);
        Preventista *prevActual = &aux[i];
        //estás realizando una copia del elemento en la posición i del arreglo al objeto elementoActual pero los cambios que reciba se reflejaran en el elemento del arreglo tambien, sino solo sería una copia y no se reflejarian los cambios
        int cantidadClientes= prevActual->cantidadClientesTotal;
        for (int j = 0; j < cantidadClientes; j++)
        {
            Cliente *clienteActual = &(prevActual->clientes[j]);
            //Cliente *clienteActual = &prevActual->clientes[j]; //hace lo mismo que la linea anterior
            clienteActual->clienteID = contadorCliente;
            contadorCliente++;

            printf("Ingrese nombre del cliente: \n");
            gets(Buff);
            fflush(stdin);
            nombre= (char *) malloc((strlen(Buff)+1)*sizeof(char));
            strcpy(nombre,Buff);

            clienteActual->NombreCliente = nombre;
            cantidadProductos = clienteActual->cantidadProductosAPedir;
            for (int k = 0; k < cantidadProductos; k++)
            {
                Producto *prodActual = &(clienteActual->productos[k]);
                // Producto *prodActual = &clienteActual->productos[k]; //hace lo mismo que la linea anterior

                prodActual->productoID = contadorProd;
                prodActual->cantidad = rand()%10+1; //cantidad entre 1 y 10
                prodActual->precioUnitario = rand()%91+10; //entre 10 y 100

                int indiceTipoRandom = rand()%5;
                prodActual->tipoProducto= TiposProductos[indiceTipoRandom];

                contadorProd++;
            }
        }  
    }
    free(Buff);
    free(nombre);
    printf("....clientes y productos cargados.\n");
}
Producto* buscarProducto(Preventista **pDoblePrev, int id, int cantidadPrev){
    printf("------------------Buscar producto------------------------\n");
    Producto *prodBuscado = NULL;
    Preventista *aux = *pDoblePrev;
    int cantidadClientes;
    int cantidadProductos;
    bool encontrado = false;

    for (int i = 0; i < cantidadPrev; i++)
    {
        Preventista *prevActual = &aux[i];
        cantidadClientes = prevActual->cantidadClientesTotal;
        for (int j = 0; j < cantidadClientes; j++)
        {
            Cliente *clienteActual = &(prevActual->clientes[j]);
            cantidadProductos = clienteActual->cantidadProductosAPedir;
            for (int k = 0; k < cantidadProductos; k++)
            {
                Producto *prodActual = &(clienteActual->productos[k]);
                if(prodActual->productoID == id){
                    encontrado = true;
                    printf("Producto encontrado\n");
                    return prodActual;
                }
            }
        }  
    }
    printf("Producto NO encontrado\n");
    return prodBuscado;
}
float costoTotal(Producto **pDobleProducto){
    printf("------------------Calcular costo------------------------\n");
    float costo;
    Producto *punteroAlProducto = *pDobleProducto;
    costo= (punteroAlProducto->cantidad)*(punteroAlProducto->precioUnitario);
    printf("-Costo del producto de ID %d: $ %.2f\n", punteroAlProducto->productoID,costo);
    printf("--\n");
    return costo;
}
void mostrarTodo(Preventista **pDoblePreventistas, int cantidadPrev){
     printf("------------------Mostrar Preventistas con sus clientes y los productos comprados por c/cliente------------------------\n");
    Preventista *aux = *pDoblePreventistas;
    int cantidadProductos;

    for (int i = 0; i < cantidadPrev; i++)
    {
        printf("----->>>Preventista [%d]: \n", i);
        Preventista *prevActual = &aux[i];
        int cantidadClientes= prevActual->cantidadClientesTotal;
        for (int j = 0; j < cantidadClientes; j++)
        {
            float suma= 0;
            Cliente *clienteActual = &(prevActual->clientes[j]);
            printf("------ Cliente [%d]: \n", clienteActual->clienteID);
            printf("-ID: %d\n", clienteActual->clienteID);
            printf("-Nombre: %s\n", clienteActual->NombreCliente);
            printf("-Cantidad de productos DIFERENTES comprados: %d\n", clienteActual->cantidadProductosAPedir);
            printf("-Productos:\n");
            cantidadProductos = clienteActual->cantidadProductosAPedir;
            for (int k = 0; k < cantidadProductos; k++)
            {
                Producto *prodActual = &(clienteActual->productos[k]);
                printf("______ Producto ID: %d\n", prodActual->productoID);
                printf("______ Producto TIPO:");
                puts(prodActual->tipoProducto);
                printf("______ Producto CANTIDAD: %d\n", prodActual->cantidad);
                printf("______ Producto PRECIO UNITARIO: %.2f\n", prodActual->precioUnitario);
                suma+= costoTotal(&prodActual);
            }
            printf("-TOTAL a pagar por todos los productos comprados: $ %.2f\n", suma);
        }  
    }
}
void liberar(Preventista **pDoblePreventistas, int cantidadPrev){
    Preventista *aux = *pDoblePreventistas;
    int cantidadProductos;
    int cantidadClientes;
    for (int i = 0; i < cantidadPrev; i++)
    {
        printf("----->>>Preventista [%d]: \n", i);
        Preventista *prevActual = &aux[i];
        cantidadClientes= prevActual->cantidadClientesTotal;
        for (int j = 0; j < cantidadClientes; j++)
        {
            Cliente *clienteActual = &(prevActual->clientes[j]);
            free(clienteActual->productos);
        }
        free(prevActual->clientes);
    }
    free(*pDoblePreventistas);
    printf("...memoria liberada.\n");
}