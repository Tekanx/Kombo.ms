/*
    Roberto Isla & Matias Garcia
    20.184.001-5 &
*/
#include <stdio.h>
#include <stdlib.h>
#include "lista.h"
#include "hash.h"
#include <stdbool.h>

typedef struct{
    char nombreArtista[101];
    List *Albums;
    List *Canciones;
    
} Artista;

typedef struct{
    char nombreAlbum[201];
    char nombreArtista[101];
    char generoAlbum[101];
    int fechaAlbum;
    List *Canciones;

} Album;

typedef struct{
    char nombreCancion[101];
    char nombreAlbum[102];
    char nombreArtista[101];
    char genero[101];
    int duracion;               //En segundos;
} Cancion;

Artista *getLinea(char linea[1024], HashTable artistaHT);

bool cargarArchivo(char nombre[301], HashTable artistaHT, HashTable albumHT, HashTable cancionHT);

int main()
{
    HashTable *artistaHT = createHashTable(1);
    HashTable *albumHT = createHashTable(1);
    HashTable *cancionHT = createHashTable(1);
    Artista *artistaAux;
    char linea[1024];
    char nombre[301];
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
        scanf("%d", &opcion);
        getchar();
        switch(opcion){
        case 1:
            printf("\nIngrese el nombre del archivo sin su extension :");
            scanf("%s", &nombre);
            strcat(nombre, ".csv");
            if(cargarArchivo(nombre, artistaHT, albumHT, cancionHT) == true) printf("Musica cargada ! \n");
            else printf("El archivo .csv no existe...\n");
            break;
        case 2:

            break;
        case 3:
            
            break;
        case 4:
            printf("Ingrese la cancion con el siguiente formato...\n");
            printf("Nombre,Artista,Minutos:Segundos,Album \n");
            fgets(linea, 1023, stdin);
            strtok(linea, "\n");
            artistaAux = getLinea(linea, artistaHT);

            /**
             * Buscar primero si el artista existe, si no existe crearlo
             * Buscar segundo si el album existe, si no existe crearlo
             * Buscar si en el Album la cancion ya existe, sino no agregarla
             * */
            break;
        case 5:

            break;
        case 6:

            break;
        case 7:

            break;
        case 8:

            break;
        default : printf("Opcion Invalida! \n");
        }
    }while(opcion != 9);
    return 0;
}


Artista *getLinea(char linea[1024], HashTable *artistaHT){
    Artista *new;
    char cancion[101];
    char artista[101];
    int minutos;
    char auxMin[3];
    int segundos;
    char auxSeg[3];
    char album[201];
    strcpy(cancion, strtok(linea, ","));
    strcpy(artista, strtok(NULL, ","));
    strcpy(auxMin, strtok(NULL, ":"));
    strcpy(auxSeg, strtok(NULL, ","));
    strcpy(album, strtok(NULL, "\n"));
    minutos = atoi(auxMin) * 60;
    segundos = atoi(auxSeg);
    strcpy(new -> nombreArtista, artista);
    pushBack(new ->Canciones, cancion);
    pushBack(new ->Albums, album);
    /** searchArtista()
     * 
        if(searchHashTable(artistaHT, new ->nombreArtista) == NULL){        //Artista no existe

        }
        else{                               //Artista existe

        }
     * 
     * */
    //searchAlbum();
    //searchCancion();
}

bool cargarArchivo(char nombre[], HashTable *artistaHT, HashTable *albumHT, HashTable *cancionHT){
    FILE *nombreArchivo = fopen(nombre, "r");  
    Artista *artistaAux;  
    char linea[1024];
    if(nombreArchivo != NULL){
        fgets(linea, 1023, nombreArchivo);
        strtok(linea, "\n");
        while((fgets(linea, 1023, nombreArchivo)) != EOF){
            artistaAux = getLinea(linea, artistaHT);
        }
    }else return false;

}