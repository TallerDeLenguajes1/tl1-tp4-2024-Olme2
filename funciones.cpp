#include <stdlib.h>

//Estructura nodo
typedef struct Tnodo{
    int valor; //Dato
    Tnodo * sig; //Duntero al siguiente nodo
}Tnodo;

//Funcion crear nuevo nodo
Tnodo * crearNodo(int valor){
    Tnodo * NNodo = (Tnodo*)malloc(sizeof(Tnodo));
    NNodo->valor=valor;
    NNodo->sig= NULL;
    return NNodo;
}

//Funcion lista vacia
Tnodo*crearListaVacia(){
    return NULL;
}
int main(){
    Tnodo *start;

    start=crearListaVacia();
}

//Funcion insercion al inicio de la lista
void insertarAlInicio(Tnodo **start,Tnodo *nuevoNodo){ //Como parametro pasa la direccion de memoria de start (&start)
    nuevoNodo->sig= *start;
    *start=nuevoNodo;
}

//Funcion insercion al final de la lista
void insertarAlFinal(Tnodo *start, Tnodo *nuevoNodo){
    Tnodo *aux=start;
    while(aux->sig){
        aux=aux->sig;
    }
    aux->sig=nuevoNodo;
}

//Funcion buscar un nodo de la lista
Tnodo *buscarNodo(Tnodo *start, int idBuscado){
    Tnodo *aux=start;
    while(aux && aux -> id!=idBuscado){
        aux=aux->sig;
    }
    return aux;
}

//Funcion eliminar un nodo
void eliminarNodo(Tnodo **start, int dato){
    Tnodo **aux=start;
    //Iteramos sobre la lista hasta encontrar el dato o alcanzar el final de la lista
    while(*aux != NULL && (*aux)->valor != dato){
        aux=&(*aux)->sig;
    }
    //Si encontramos el nodo con el dato especificado, lo eliminamos
    if(*aux){
        Tnodo *temp=*aux; //Guardamos el nodo a eliminar en una variable temporal
        *aux=(*aux)->sig; //Desvinculamos el nodo de la lista
        free(temp); //Liberamos la memoria ocupada por el nodo
    }
}