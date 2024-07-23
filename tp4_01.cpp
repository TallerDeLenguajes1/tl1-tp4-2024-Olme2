#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct Tarea{
    int TareaID;//Numérico autoincremental comenzando en 1000
    char *Descripcion; //
    int Duracion; // entre 10 – 100
}Tarea;


typedef struct Nodo{
    Tarea T;
    Nodo *Siguiente;
} Nodo;

typedef struct Nodo* ListaDeTareas;

ListaDeTareas crearListaVacia();
bool esListaVacia(ListaDeTareas listaDeTareas);
void listarTareas(ListaDeTareas listaDeTareas);
ListaDeTareas insertar(ListaDeTareas listaDeTareas, Tarea tarea);
void marcarTareaComoRealizada(ListaDeTareas* tareasPendientes,ListaDeTareas* tareasRealizadas,int id);
Tarea crearTarea(int id, char* descripcion, int duracion);
void mostrarTareaPorId(ListaDeTareas tareasPendientes, ListaDeTareas tareasRealizadas, int id);
void mostrarTareaPorPalabraClave(ListaDeTareas tareasPendientes, ListaDeTareas tareasRealizadas, char* palabraClave);


int main(){
    int duracion, id=1000, seguir;
    char *descripcion=(char*)malloc(sizeof(char)*100);
    ListaDeTareas tareasPendientes=crearListaVacia();
    ListaDeTareas tareasRealizadas=crearListaVacia();
    Tarea nuevaTarea;
    srand(time(NULL));
    //PUNTO 1
    do{
        printf("\n// Tarea n°%d //\n", id);
        printf("Escriba la descripcion de la tarea: ");
        gets(descripcion);
        duracion=10+rand()%(91);
        printf("La duracion de la tarea es de %d\n",duracion);
        nuevaTarea=crearTarea(id, descripcion, duracion);
        tareasPendientes=insertar(tareasPendientes, nuevaTarea);
        printf("¿Desea ingresar una nueva tarea o finalizar la carga?\n");
        printf("0: Finalizar la carga\n1: Ingresar una nueva tarea\n");
        do{
            if(seguir<0 || seguir>1){
                printf("Escriba una opcion correcta\n");
            }
            scanf("%d", &seguir);
        }while(seguir<0 || seguir>1);
        id++;
        getchar();
    }while(seguir==1);
    //PUNTO 2
    seguir=1;
    while(seguir==1 && !esListaVacia(tareasPendientes)){
        printf("Seleccione una tarea para marcarla como realizada: ID=");
        scanf("%d", &id);
        marcarTareaComoRealizada(&tareasPendientes, &tareasRealizadas, id);
        printf("¿Desea marcar otra tarea como realizada?\n");
        printf("0: Finalizar\n1: Marcar nueva tarea\n");
        do{
            if(seguir<0 || seguir>1){
                printf("Escriba una opcion correcta\n");
            }
            scanf("%d", &seguir);
        }while(seguir<0 || seguir>1);
    }
    if(esListaVacia(tareasPendientes)){
        printf("No quedan mas tareas pendientes\n");
    }
    //PUNTO 3
    printf("// Tareas Pendientes //\n\n");
    listarTareas(tareasPendientes);
    printf("// Tareas Realizadas //\n\n");
    listarTareas(tareasRealizadas);
    //PUNTO 4
    do{
        printf("¿Quiere buscar una tarea por id o por palabra clave?\n");
        printf("1: Id\n2: Palabra clave\n");
        do{
            if(seguir<1 || seguir>2){
                printf("Seleccione una opcion correcta\n");
            }
            scanf("%d", &seguir);
        }while(seguir<1 || seguir>2);
        if(seguir==1){
            printf("Seleccione un id para buscar una tarea: ID=");
            scanf("%d", &id);
            mostrarTareaPorId(tareasPendientes, tareasRealizadas, id);
        }else{
            printf("Escriba una palabra clave para buscar una tarea: ");
            getchar();
            gets(descripcion);
            mostrarTareaPorPalabraClave(tareasPendientes, tareasRealizadas, descripcion);
        }
        seguir=1;
        printf("\n¿Desea buscar otra tarea?\n");
        printf("0: Finalizar\n1: Buscar nueva tarea\n");
        do{
            if(seguir<0 || seguir>1){
                printf("Escriba una opcion correcta\n");
            }
            scanf("%d", &seguir);
        }while(seguir<0 || seguir>1);
    }while(seguir==1);
    return 0;
}

ListaDeTareas crearListaVacia(){
    ListaDeTareas L;
    L=NULL;
    return L;
}

bool esListaVacia(ListaDeTareas listaDeTareas)
{
    return listaDeTareas==NULL;
}

Tarea crearTarea(int id, char* descripcion, int duracion){
    Tarea nueva;
    nueva.Descripcion=(char*)malloc(sizeof(char)*100);
    nueva.TareaID=id;
    strcpy(nueva.Descripcion, descripcion);
    nueva.Duracion=duracion;
    return nueva;
}

ListaDeTareas insertar(ListaDeTareas listaDeTareas,Tarea tarea){
    Nodo* nuevo=(Nodo*)malloc(sizeof(Nodo));
    nuevo->T=tarea;
    if(esListaVacia(listaDeTareas)){
        nuevo->Siguiente=listaDeTareas;
        listaDeTareas=nuevo;
    }else{
        Nodo* actual=listaDeTareas;
        while(actual->Siguiente!=NULL){
            actual=actual->Siguiente;  
        }
        nuevo->Siguiente=actual->Siguiente;
        actual->Siguiente=nuevo;
    }
    return listaDeTareas;
}

void marcarTareaComoRealizada(ListaDeTareas* tareasPendientes,ListaDeTareas* tareasRealizadas,int id){
    Nodo** auxP=tareasPendientes;
    while(*auxP!=NULL && id!=(*auxP)->T.TareaID){
        auxP=&(*auxP)->Siguiente;
    }
    if(*auxP==NULL){
        printf("No se encontro la tarea\n");
    }else{
        *tareasRealizadas=insertar(*tareasRealizadas, (*auxP)->T);
        Nodo *temp=*auxP;
        printf("Se marco la tarea %d como realizada correctamente\n", (*auxP)->T.TareaID);
        *auxP=(*auxP)->Siguiente;
        free(temp);
    }
}

void listarTareas(ListaDeTareas listaDeTareas){
    if(esListaVacia(listaDeTareas)){
        printf("La lista no contiene tareas\n");
    }else{
        Nodo* aux=listaDeTareas;
        while(aux!=NULL){
            printf("|| Tarea n°%d ||\n", aux->T.TareaID);
            printf("Descripcion: %s\n", aux->T.Descripcion);
            printf("Duracion: %d\n\n", aux->T.Duracion);
            aux=aux->Siguiente;
        }
    }
}

void mostrarTareaPorId(ListaDeTareas tareasPendientes, ListaDeTareas tareasRealizadas, int id){
    Nodo* auxP=tareasPendientes;
    Nodo* auxR=tareasRealizadas;
    while(auxP!=NULL && id!=auxP->T.TareaID){
        auxP=auxP->Siguiente;
    }
    if(auxP==NULL){
        while(auxR!=NULL && id!=auxR->T.TareaID){
            auxR=auxR->Siguiente;
        }
        if(auxR==NULL){
            printf("Tarea no encontrada\n");
        }else{
            printf("\n|| Tarea n°%d ||\n", auxR->T.TareaID);
            printf("Descripcion: %s\n", auxR->T.Descripcion);
            printf("Duracion: %d\n", auxR->T.Duracion);
            printf("Esta tarea esta realizada\n");    
        }   
    }else{
        printf("\n|| Tarea n°%d ||\n", auxP->T.TareaID);
        printf("Descripcion: %s\n", auxP->T.Descripcion);
        printf("Duracion: %d\n", auxP->T.Duracion);
        printf("Esta tarea esta pendiente\n");
    }
}

void mostrarTareaPorPalabraClave(ListaDeTareas tareasPendientes, ListaDeTareas tareasRealizadas, char* palabraClave){
    Nodo* auxP=tareasPendientes;
    Nodo* auxR=tareasRealizadas;
    int bandera=0;
    while(auxP!=NULL){
        if(auxP!=NULL && strstr(auxP->T.Descripcion, palabraClave)){
            bandera=1;
            printf("\n|| Tarea n°%d ||\n", auxP->T.TareaID);
            printf("Descripcion: %s\n", auxP->T.Descripcion);
            printf("Duracion: %d\n", auxP->T.Duracion);
            printf("Esta tarea esta pendiente\n");
        }
        auxP=auxP->Siguiente;
    }
    while(auxR!=NULL){
        if(auxR!=NULL && strstr(auxR->T.Descripcion, palabraClave)){
            bandera=1;
            printf("\n|| Tarea n°%d ||\n", auxR->T.TareaID);
            printf("Descripcion: %s\n", auxR->T.Descripcion);
            printf("Duracion: %d\n", auxR->T.Duracion);    
            printf("Esta tarea esta realizada\n");
        }
        auxR=auxR->Siguiente;
    }
    if(bandera==0){
        printf("\nNo se encontro ninguna tarea que contenga esa palabra clave\n");
    }
}