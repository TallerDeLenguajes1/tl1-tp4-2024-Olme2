#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Tarea{
    int TareaID;//Numérico autoincremental comenzando en 1000
    char *Descripcion; //
    int Duracion; // entre 10 – 100
}Tarea;

typedef struct Nodo{
    Tarea T;
    Nodo *Siguiente;
} Nodo;

Nodo*crearListaVacia();
Nodo *crearTarea(char *descripcion, int duracion, int id);
void insertarAlInicio(Nodo **start,Nodo *nuevoNodo);
void insertarNodoF(Nodo **start, Nodo *nuevoNodo);
Nodo *buscarTarea(Nodo *start, int idBuscado);
void eliminarTarea(Nodo **start, int idBuscado);

int main(){
    Nodo *startPendientes, *startRealizadas;
    char *buff=(char*)malloc(100*sizeof(char));
    char *descripcion;
    int duracion;
    int id=1000;
    int seguir=1;
    startPendientes=crearListaVacia();
    startRealizadas=crearListaVacia();
    while(seguir==1){
        printf("Escriba la descripcion de la tarea: ");
        gets(buff);
        descripcion=(char*)malloc(strlen(buff)*sizeof(char)+1);
        strcpy(descripcion,buff);
        printf("Escriba la duracion de la tarea: ");
        scanf("%d",&duracion);
        Nodo *nuevaTarea= crearTarea(descripcion,duracion,id);
        insertarNodoF(&startPendientes, nuevaTarea);
        printf("Desea agregar otra tarea?\n0:NO\n1:SI\n");
        scanf("%d",&seguir);
        getchar();
        id++;
    }
    seguir=1;
    int contador=0;
    while(seguir==1){
        printf("Escriba el id de la tarea que quiera marcar como realizada: ");
        scanf("%d",&id);
        Nodo *tareaRealizada=buscarTarea(startPendientes,id);
        if(tareaRealizada==NULL){
            printf("La tarea que solicito no se encuentra\n");
        }else{
            insertarNodoF(&startRealizadas, tareaRealizada);
            eliminarTarea(&startPendientes, id);
        }
        printf("Tarea transferida, quiere seguir agregando tareas a realizadas?\n0:NO\n1:SI\n");
        scanf("%d",&seguir);
        contador++;
    }
    free(buff);
    return 0;
}

Nodo*crearListaVacia(){
    return NULL;
}

Nodo *crearTarea(char *descripcion, int duracion, int id){
    Nodo *nuevaTarea=(Nodo*)malloc(sizeof(Nodo));
    nuevaTarea->T.TareaID=id;
    nuevaTarea->T.Duracion=rand()%91+10;
    nuevaTarea->T.Descripcion=descripcion;
    nuevaTarea->Siguiente=NULL;
    return nuevaTarea;
}

void insertarNodoF(Nodo **Start, Nodo *nuevoNodo){
    if (*Start == NULL) {
        *Start = nuevoNodo;
    } else {
        Nodo *aux = *Start;
        while(aux->Siguiente != NULL){
            aux = aux->Siguiente;
        }
        aux->Siguiente = nuevoNodo;
        }
}

Nodo *buscarTarea(Nodo *start, int idBuscado){
    Nodo *aux=start;
    while(aux && aux->T.TareaID!=idBuscado){
        aux=aux->Siguiente;
    }
    return aux;
}

void eliminarTarea(Nodo **start, int idBuscado){
    Nodo **aux=start;
    while(*aux != NULL && (*aux)->T.TareaID != idBuscado){
        aux=&(*aux)->Siguiente;
    }
    if(*aux){
        Nodo *temp=*aux;
        *aux=(*aux)->Siguiente;
        free(temp);
    }
}