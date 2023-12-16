//Programa para las recomendaciones de las peliculas 

#include<stdio.h>
#include<stdlib.h>
#include"TablasHash.h" //Libreria propia con toda la informacion correspondiente a las tablas de Hash y las peliculas

//Estructura para almacenar las preferencias del usuario 
typedef struct{
   char *genero;
   char *director;
   char *actor1;
   char *actor2;
   char *anno;
}Usuario;

	//Prototipos de las Funciones
//Funcion para mostrar el menu de preguntas para recomendaciones
void Preferencias(Usuario *preferencia);
//Funcion para que el usuario pueda calificar una pelicula
void CalificarPelicula();
//Funcion para recomendar pelicula
void Recomendacion(Usuario *preferencia);

int main(){
    FILE *arc = NULL;
   
   //inicializar TablaHash
   InicializarTabla();
    
   //LLenado de la tabla mediante la lectura del archivo.
   leerarchivo(arc);
    
   //crear registro de preferencias de usuario
   Usuario *preferencia = (Usuario *)malloc(sizeof(Usuario));
   preferencia -> genero =  preferencia -> director = preferencia -> actor1 = preferencia -> actor2 = NULL;
   preferencia -> anno = NULL;
   
   Preferencias(preferencia);
  /* 
   //Mostrar si los datos se guardaron correctamente
   printf("%s",preferencia -> genero);
   printf("%s",preferencia -> director);
   printf("%s",preferencia -> actor1);
   printf("%s",preferencia -> anno);    */
   
   Recomendacion(preferencia);		
   

//   CalificarPelicula();

  return 0;
}

//Funcion para mostrar el menu de preguntas para recomendaciones
void Preferencias(Usuario *preferencia){
  int opc = 1, seleccion;
  
   while(opc != 2){
   
      printf("	Estimado Usuario, por favor reponda las siguientes preguntas para poder obtener recomendaciones segun sus preferencias:\n");
      printf("1. Genero Favorito\n");
      printf("2. Año de Lanzamiento especifico\n");
      printf("3. Director Favorito\n");	
      printf("4. Actores\n");
      printf("Seleccion: ");
      scanf("%i",&seleccion);
      getchar();   //limpiar buffer
      
     if ((seleccion < 1) || (seleccion > 4)){  //validacion de las entradas
         system("clear");
         printf("\nLa opcion ingresada no es valida. Por favor ingrese suevamente\n");  
     }else{
         //mostrar todas las peliculas disponibles para elegir
         printf("\n-----Peliculas Disponibles-----\n");
         imprimir_tabla_hash();
         
         //pedir datos
         switch(seleccion){
           case 1:
              preferencia -> genero = (char*)malloc(sizeof(char)*20);
              printf("\nIngrese su genero favorito: ");
              fgets(preferencia->genero,20,stdin);
              break;
           case 2:
              preferencia -> anno = (char*)malloc(sizeof(char)*6);
              printf("\nIngrese un año referencial para su eleccion de  peliculas: ");
              fgets(preferencia->anno,6,stdin);
              break;
           case 3:
              preferencia -> director = (char*)malloc(sizeof(char)*20);
              printf("\nIngrese su director favorito: ");
              fgets(preferencia->director,20,stdin);
              break;
           case 4:
              preferencia -> actor1 = (char*)malloc(sizeof(char)*20);
              preferencia -> actor2 = (char*)malloc(sizeof(char)*20);
              printf("\nIngrese su actor favorito: ");
              fgets(preferencia->actor1,20,stdin);
              printf("\nIngrese su segundo actor favorito: ");
              fgets(preferencia->actor2,20,stdin);
              break;
         }
         
         printf("\nDesea ingresar otra preferencia (Si = 1 / No = 2): ");
         scanf("%i",&opc);
         
         while (opc != 1 && opc != 2){
           printf("La opcion ingresada no es valida. Por favor ingrese suevamente\n");
           printf("Desea ingresar otra preferencia? (Si = 1 / No = 2): ");
           scanf("%i",&opc);
         }
         system("clear");
         fflush(stdin);  //limpiar buffer
      }
      
   }
   
}

//Funcion para que el usuario pueda calificar una pelicula
void CalificarPelicula(){
   char *pelicula; 
   
   //reservar espacio para la cadena
   pelicula = (char*)malloc(sizeof(char)*20);
   
   //mostrar peliculas disponibles
   ListarPeliculas();
   printf("Ingrese el nombre de la pelicula que desea calificar (Escribir como se muestra en la lista): ");
   getchar();
   fgets(pelicula,20,stdin);
   pelicula[strlen(pelicula)-1] = '\0';
   Calificar(pelicula);
}

//Funcion para recomendar pelicula
void Recomendacion(Usuario *preferencia){
   int acertado = 0; //determina la cantidad preferencias acertadas
   int disponibles = 0; //determina la cantidad de preferencias disponibles
   int recomendado = 0;  //determina si se pudieron recomendar peliculas
   Pelicula *temp = NULL;
   
   //eliminar el salto de linea que agrega la funcion fgets
   if (preferencia -> genero != NULL)
       preferencia -> genero[strlen(preferencia -> genero)-1] = '\0'; 
   if (preferencia -> actor1 != NULL)
      preferencia -> actor1[strlen(preferencia -> actor1)-1] = '\0';
   if (preferencia -> actor2 != NULL)
     preferencia -> actor2[strlen(preferencia -> actor2)-1] = '\0';   
   if (preferencia -> director != NULL)
     preferencia -> director[strlen(preferencia -> director)-1] = '\0'; 
   
   printf("-----Recomendaciones-------\n");
   for (int i = 0; i < capacidad; i++){
      temp = TablaHash[i];
      while (temp != NULL){
         
         //buscar pelicula con respecto al genero
         if (preferencia -> genero != NULL){
            disponibles++;
            if(strcasecmp(temp -> genero,preferencia -> genero) == 0){
               acertado++;
            }
         }
         
         //buscar pelicula con respecto al actor 1
         if (preferencia -> actor1 != NULL){
            disponibles++; 
            if(strcasecmp(temp -> actor1,preferencia -> actor1) == 0){
               acertado++;
            }
         }
         
         //buscar pelicula con respecto al actor 2
         if (preferencia -> actor2 != NULL){ 
            disponibles++;
            if(strcasecmp(temp -> actor2,preferencia -> actor2) == 0){
               acertado++;
            }
         }
         
         //buscar pelicula con respecto al director
         if (preferencia -> director != NULL){ 
            disponibles++;
            if(strcasecmp(temp -> director,preferencia -> director) == 0){
               acertado++;
            }
         }
         
       /*  //buscar las peliculas con calificaciones altas
         if (temp -> calificacion > 3)
            acertado++;*/
            
         //determinar si la pelicula es valida para recomendacion
         if(acertado == disponibles){
             printf("*%s\n",temp -> titulo);
             recomendado = 1;
         }
         
         temp = temp -> next;
         disponibles = 0;
         acertado = 0;
      }
   }
   if (recomendado == 0)
      printf("No se encontraron peliculas que cumplen con sus preferencias :( \n");
        
}

/*
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

