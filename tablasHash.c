#include <stdio.h>
#include<stdlib.h>
#include<string.h>

#define capacidad 5

typedef struct nodo{
   int calificacion;
   char *clasificacion;
   char *sinopsis;  
   char *titulo;
   char *director;
   int anno;
   char *genero;
   int duracion;  
   struct nodo *next;
}Pelicula;

//Crear TablaHash
Pelicula *TablaHash[capacidad];

//inicializar tabla
void InicializarTabla(){
   for (int i = 0; i < capacidad; i++){
      TablaHash[i] = NULL;
   }
}

//Funcion que determina el indice de la pelicula por su nombre
int FuncionHash(char *titulo){
   int longitud;
   int hash = 0;
   
   longitud = strlen(titulo);
   for (int i = 0; i < longitud; i++){
      hash += titulo[i];
      hash = (hash * titulo[i]) % capacidad;
   }
   return hash;
}

void insertar_elemento(char *titulo, int calificacion, char *clasificacion, char *sinopsis, char *director, int anno, 
                        char *genero, int duracion) {
    int indice = FuncionHash(titulo);
    Pelicula *newnodo;
    
        printf("INDICE: %i\n",indice);
    
    //se reserva espacio de memoria para el nodo
    newnodo = (Pelicula *)malloc(sizeof(Pelicula));
    //se reserva espacio de memoria para las cadenas
    newnodo -> titulo = (char*)malloc(sizeof(char)*strlen(titulo)+1);
    newnodo -> clasificacion = (char*)malloc(sizeof(char)*strlen(clasificacion)+1);
    newnodo -> sinopsis = (char*)malloc(sizeof(char)*strlen(sinopsis)+1);
    newnodo -> director = (char*)malloc(sizeof(char)*strlen(director)+1);
    newnodo -> genero = (char*)malloc(sizeof(char)*strlen(genero)+1);
    //se guardan los datos
    strcpy(newnodo -> titulo , titulo);
    strcpy(newnodo -> clasificacion , clasificacion);
    strcpy(newnodo -> sinopsis , sinopsis);
    strcpy(newnodo -> director , director);
    strcpy(newnodo -> genero , genero);
    newnodo -> calificacion = calificacion;
    newnodo -> anno = anno;
    newnodo -> duracion = duracion;
    newnodo -> next = NULL;
    
    if (TablaHash[indice] == NULL){  
       TablaHash[indice] = newnodo;
    }else{   //de estar ocupado ese indice se enlaza con el siguiente
       Pelicula *temp = TablaHash[indice];
       while(temp -> next != NULL){
           temp = temp -> next;
       }
       temp -> next = newnodo;
    }
}

//Funcion Buscar y mostrar la informacion de una pelicula
int Mostrar_Informacion(char *titulo) {
    int indice = FuncionHash(titulo);
    Pelicula *temp = NULL;
    
    temp = TablaHash[indice];
    while(temp != NULL){
       if (strcmp(temp -> titulo,titulo) == 0){
           break;
       }else{
          temp = temp -> next;
       }
    }
    if (temp != NULL){
      printf(" Informacion de la pelicula: %s\n",titulo);
      printf("Titulo: %s, Sinopsis: %s, Clasificacion %s, Director: %s, Genero: %s, Anno: %i, Duracion: %i, 	Calificacion : %i\n",
                   temp-> titulo, temp-> sinopsis, temp -> clasificacion,temp -> director, temp -> genero, temp -> anno,
                   temp -> duracion, temp -> calificacion);
            temp = temp -> next;
       return 1;
    }else{
       return 0;
    }
}

void eliminar_elemento(char *titulo) {
    int indice = FuncionHash(titulo);

    Pelicula *temp = TablaHash[indice];
    Pelicula *prev = NULL;
    
    while((temp != NULL) && (strcmp(temp -> titulo,titulo) != 0)){
       prev = temp;
       temp = temp -> next;
    }
    
    if (prev == NULL){   //el elemento a eliminar fue  el primero
       TablaHash[indice] = temp -> next;
    }else{
       prev -> next = temp -> next;
    }
    free(temp);
}

//Funcion que imprime toda la tabla
void imprimir_tabla_hash() {
    Pelicula *temp = NULL;
    
    for (int i = 0; i < capacidad; i++) {
        temp = TablaHash[i];
        while (temp != NULL) {
            printf("Titulo: %s, Sinopsis: %s, Clasificacion %s, Director: %s, Genero: %s, Anno: %i, Duracion: %i, Calificacion : %i\n",
                   temp-> titulo, temp-> sinopsis, temp -> clasificacion,temp -> director, temp -> genero, temp -> anno,
                   temp -> duracion, temp -> calificacion);
            temp = temp -> next;
        }
    }
}

//Funcion que lista todas las peliculas
void ListarPeliculas(){
   Pelicula *temp = NULL;
   int j = 1;
   
   printf("    Lista de Peliculas\n");
   for (int i  = 0; i < capacidad; i++){
      temp = TablaHash[i];
      while(temp != NULL){
         printf("%i. %s\n",j++,temp -> titulo);
         temp = temp -> next;
      }
   }
}

int main() {

    //inicializar TablaHash
    InicializarTabla();

    insertar_elemento("Moana", 3, "A", "Una chica aventurera","Natalia",2012,"Infantil",123);
    insertar_elemento("La Sirenita",2, "A","Una Sirena","Natalia",2012,"Infantil",123);
    insertar_elemento("Barbie", 5,"A","Una chica inspiradora","Natalia",2012,"Infantil",123);
    
    //llamado a la funcion que muestra informacion de una pelicula
    Mostrar_Informacion("Barbie");
    
    //llamado a la funcion que lista todas las peliculas
    ListarPeliculas();
/*
    printf("Buscar pelicula Barbie: %s\n", buscar_elemento("Barbie"));
    printf("Buscar pelicula La Sirenita: %s\n", buscar_elemento("La Sirenita"));
    printf("Buscar pelicula Enredados: %s\n", buscar_elemento("Enredados"));

    imprimir_tabla_hash();
*/
    return 0;
}
