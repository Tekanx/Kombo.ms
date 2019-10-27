/*
    Roberto Isla & Matias Garcia
    20.184.001-5 & 20.181.753-6
*/
#include <stdio.h>
#include <stdlib.h>
#include "lista.h"
#include "hash.h"
#include <stdbool.h>

typedef struct{
    char *nombre;
    List *canciones;
    HashTable *Canciones;
} Album;

typedef struct{
    char *nombre;
    List *canciones;
    HashTable *Canciones
}artista;

typedef struct{
    char *nombreCancion;
    char *nombreAlbum;
    char *nombreArtista;
    char *duracion;
    int fecha;
} Cancion;

void importar(char linea[1024], HashTable *artista, HashTable *album);

Cancion *crearCancion(char *nombre, char *artista, char *duracion, char *album, int fecha);

bool cargarArchivo(char nombre[301], HashTable *artistaHT, HashTable *albumHT);

const char *get_csv_field (char * tmp, int i);

int main(){
    HashTable *artistaHT = createHashTable(40);
    HashTable *albumHT = createHashTable(40);
    Cancion *cancionAux =(Cancion *) calloc(1, sizeof(Cancion));
    char linea[1024];
    char nombre[301];
    char albumAux[301];
    char artistaAux[301];
    char *CancionAux;
    int opcion;
    do{
        printf(" _____________________________________________\n");
        printf("|       Gestionador de Musica de Rodolfo      |\n");
        printf("|---------------------------------------------|\n");
        printf("| 1.- Importar musica desde un archivo '.csv' |\n");
        printf("| 2.- Exportar musica a un '.csv'             |\n");
        printf("| 3.- Agregar album                           |\n");
        printf("| 4.- Agregar cancion                         |\n");
        printf("| 5.- Eliminar canciones de un artista        |\n");
        printf("| 6.- Buscar cancion                          |\n");
        printf("| 7.- Buscar canciones de un Artista          |\n");
        printf("| 8.- Buscar album                            |\n");
        printf("| 9.- Salir del Gestionador                   |\n");
        printf("|_____________________________________________|\n");
        printf("    Ingrese opcion: ");
        scanf("%d", &opcion);
        printf("\n");
        getchar();
        switch(opcion){
        case 1:
            printf("\nIngrese el nombre del archivo sin su extension :");
            scanf("%s", &nombre);
            strcat(nombre, ".csv");
            if(cargarArchivo(nombre, artistaHT, albumHT) == true) printf("Musica cargada ! \n");
            else printf("El archivo .csv no existe...\n");
            break;
        case 2:
            printf("Se importara todas las canciones actuales a un csv nuevo !\n");
            printf("ingrese nombre del archivo nuevo: ");
            scanf("%s", &linea);
            importar(linea, artistaHT, albumHT);
            break;
        case 3:
            printf("Se ingresara el album solo si no existe, caso opuesto no se creara \n");
            printf("Ingrese nombre del Album : ");
            fgets(albumAux, 300, stdin);
            strtok(albumAux, "\n");
            if(searchHashTable(albumHT, albumAux) == NULL){
                insertHashTable(albumHT, albumAux, NULL);
                printf("Desea ingresar canciones al album? : (''si'' o ''no'')");
                scanf("%s", &linea);
                while(strcasecmp(linea, "si") == 0){
                    /*
                    printf("Ingrese la cancion con el mismo formato  ");
                    printf("Nombre,Artista,Minutos:Segundos,Album : \n");
                    fgets(linea, 1023, stdin);
                    nombre = get_csv_field(linea, 1);
                    artista = get_csv_field(linea, 2);
                    duracion = get_csv_field(linea, 3);
                    album = get_csv_field(linea, 4);
                    fecha = atoi(get_csv_field(linea, 5));
            cancionAux = crearCancion(nombre, artista, duracion, album, fecha);
            */
                    printf("Desea ingresar canciones al album %s? : (''si'' o ''no'')", albumAux);
                    scanf("%s", &linea);
                    if(strcasecmp(linea, "no") == 0) {
                        //insertHashTable();

                        break;
                    }
                    else if(strcasecmp(linea, "si") != 0){
                        printf("Error de Input... \n");
                        break;
                    }
                }
            }
            else printf("El Album %s ya existe... \n", albumAux);
            break;
        case 4:
            printf("Ingrese la cancion con el siguiente formato...\n");
            printf("Nombre,Artista,Minutos:Segundos,Album : \n");
            fgets(linea, 1023, stdin);
            strtok(linea, "\n");
            cancionAux = getLinea(linea);
             //* Buscar primero si el artista existe, si no existe crearlo
            if(searchHashTable(artistaHT,artistaAux)== NULL){

            }else{

            }
             //* Buscar segundo si el album existe, si no existe crearlo
            if(searchHashTable(artistaHT,artistaAux)== NULL){

            }else{

            }
             //* Buscar si en el Album la cancion ya existe, sino nox agregarla
            if(searchHashTable(artistaHT,artistaAux)== NULL){

            }else{

            }
            break;
        case 5:
            printf("ingrese Artista a borrar\n");
            printf("Artista: ");
            fgets(artistaAux, 300, stdin);
            if(searchHashTable(artistaHT,artistaAux)== NULL){
                   printf("\n");
                   printf("El artista no existe en el sistema\n")//* De no existir el artista debe mostrar un mensaje al usuario
            }else{
            //* Eliminarcancionesdeunartista(char[]artista)

            //* ​La aplicación elimina el artista y todas sus canciones asociadas.
            }




            break;
        case 6:
            printf("Ingrese cancion a buscar\n");
            printf("Cancion: ");
            fgets(nombre, 300, stdin);
            if(searchHashTable(,)== NULL){
                printf("La cancion ingresada no existe \n");//* De no existir el artista debe mostrar un mensaje al usuario.
                break;
            }else{
         //* Buscarcanción(char[]nombre_cancion)

         //* ​La aplicación busca y muestra por pantalla la canción

         //* correspondiente(con su respectiva información).

            break;
        case 7:
            printf("ingrese nombre del Artista \n");
            printf("autor: ");
            fgets(artistaAux, 300, stdin);
         //* Buscarcancionesdeunartista(char[]artista)
            if(searchHashTable(artistaHT,artistaAux)== NULL){
                printf("El Artista ingresado no existe \n");//* De no existir el artista debe mostrar un mensaje al usuario.
                break;
            }else{
                CancionAux = searchHashTable(artistaHT,artistaAux)
                = first(artistaHT->canciones);//se
                while(1){
                    cancionAux
                    printf("Cancion: %s\n",searchHashTable(artistaHT,artistaAux));//* La aplicación busca y muestra por pantalla todas las canciones realizadas por el artista
                    printf("-Duracion: %s\n",searchHashTable(artistaHT,artistaAux));//* con su respectiva información.
                }
            }
         //* De no existir el artista debe mostrar un mensaje al usuario.

            break;
        case 8:
            printf("Ingrese el Album que quiere ver\n");
            printf("Album: ");
            fgets(albumAux, 300, stdin);
            printf("\n");
         //* Buscarálbum(char[]nombre_album)
            if(searchHashTable(albumHT,albumAux)== NULL){//* De no existir debe mostrar un mensaje al usuario.
                printf("El Album ingresado no existe \n");
                break;
            }else{
                CancionAux = first(albumHT->canciones);
                printf("Album: %s\n",&albumAux);
                while(1){//* ​La aplicación busca y muestra por pantalla el álbum y sus canciones.
                    cancionAux
                    printf("Cancion: %s\n",searchHashTable(albumHT  ,artistaAux));
                    printf("-Duracion: %s\n",searchHashTable(albumHT,artistaAux));
                }
            }
            break;
        case 9:
            printf("            Hasta luego!!");
            break;
        default : printf("Opcion Invalida! Intente nuevamente\n");
        }
    }while(opcion != 9);
    return 0;
}


void importar(char linea[1024], HashTable *artista, HashTable *album){
    FILE *archivo;
    Cancion *aux = calloc(1, sizeof(Cancion));
    linea = strcat(linea,".csv");
    archivo = fopen(linea, "w");
    if(archivo != NULL){
         printf("EL ARCHIVO YA CONTIENE MUSICA! \n");
         printf("Ingrese un archivo que no contenga musica... \n");
         return;
    }
    else{
        fprintf(archivo, "Nombre,Artista,Minutos:Segundos,Album \r");
        //first
        while(aux != NULL){
            fprintf(archivo, "%s,%s,%s,%s \n", aux ->nombreCancion, aux ->nombreArtista, aux ->duracion, aux ->nombreAlbum);
        //next
        }
        printf("Canciones guardadas en (''%s'')! \n", linea);
    }
    fclose(archivo);
}

Cancion *crearCancion(char *nombre, char *artista, char *duracion, char *album, int fecha){
    Cancion *c =(Cancion *) calloc(1, sizeof(Cancion));
    c -> nombreCancion = nombre;
    c -> nombreArtista = artista;
    c -> duracion = duracion;
    c -> nombreAlbum = album;
    c -> fecha = fecha;
    return c;
}

const char *get_csv_field (char * tmp, int i) {
    //se crea una copia del string tmp
    char * line = _strdup (tmp);
    const char * tok;
    for (tok = strtok (line, ","); tok && *tok; tok = strtok (NULL, ",\n")) {
        if (!--i) {
            return tok;
        }
    }
    return NULL;
}

bool cargarArchivo(char nombre[301], HashTable *artistaHT, HashTable *albumHT){
    char *nombre;
    char *album;
    char *artista;
    char *duracion;
    int fecha;
    FILE *nombreArchivo = fopen(nombre, "r");
    Cancion *cancionAux =(Cancion *) calloc(1, sizeof(Cancion));
    char linea[1024];
    if(nombreArchivo != NULL){
        fgets(linea, 1023, nombreArchivo);
        strtok(linea, "\n");
        while((fgets(linea, 1023, nombreArchivo)) != EOF){
            nombre = get_csv_field(linea, 1);
            artista = get_csv_field(linea, 2);
            duracion = get_csv_field(linea, 3);
            album = get_csv_field(linea, 4);
            fecha = atoi(get_csv_field(linea, 5));
            cancionAux = crearCancion(nombre, artista, duracion, album, fecha);
            if(searchHashTable() == NULL){

            }
            else{

            }

        }
    }else return false;
    return true;
}/*
char *nombre;
    char *album;
    char *artista;
    char *duracion;
    int fecha;
nombre = get_csv_field(linea, 1);
            artista = get_csv_field(linea, 2);
            duracion = get_csv_field(linea, 3);
            album = get_csv_field(linea, 4);
            fecha = atoi(get_csv_field(linea, 5));
            cancionAux = crearCancion(nombre, artista, duracion, album, fecha);
            */
