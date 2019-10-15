/*
    Roberto Isla & Matias Garcia
    20.184.001-5 &
*/
#include <stdio.h>
#include <stdlib.h>
#include "lista.h"
#include "hash.h"
#include <stdbool.h>
/*
typedef struct{
    char nombreArtista[101];
    List *Albums;
    List *Canciones;
} Artista;

typedef struct{
    char nombreAlbum[201];
    Artista *artista;
    char generoAlbum[101];
    int fechaAlbum;
    List *Canciones;

} Album;
*/
typedef struct{
    char nombreCancion[101];
    char nombreAlbum[101];
    char nombreArtista[101];
    char duracion[10];
} Cancion;

void importar(char linea[1024], HashTable artista, HashTable album, HashTable cancion);

Cancion *getLinea(char linea[1024], HashTable artistaHT);

bool cargarArchivo(char nombre[301], HashTable artistaHT, HashTable albumHT, HashTable cancionHT);

int main()
{
    HashTable *artistaHT = createHashTable(1);
    HashTable *albumHT = createHashTable(1);
    HashTable *cancionHT = createHashTable(1);
    Cancion *cancionAux =(Cancion *) calloc(1, sizeof(Cancion));
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
            printf("Se importará todas las canciones actuales a un csv nuevo \n");
            printf("ingrese nombre del archivo nuevo: ");
            scanf("%s", &linea);
            importar(linea, artistaHT, albumHT, cancionHT);
            break;
        case 3:
            
            break;.
        case 4:
            printf("Ingrese la cancion con el siguiente formato...\n");
            printf("Nombre,Artista,Minutos:Segundos,Album \n");
            fgets(linea, 1023, stdin);
            strtok(linea, "\n");
            cancionAux = getLinea(linea);

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


void importar(char linea[1024], HashTable *artista, HashTable *album, HashTable *cancion){
    FILE *archivo;
    if(archivo != NULL){
         printf("EL ARCHIVO YA CONTIENE MUSICA! \n");
         printf("Ingrese un archivo que no contenga musica... \n");
         return;
    }
    else{
        linea = strcat(linea,".csv");
        archivo = fopen(linea, "w");
        fprintf(archivo, "Nombre,Artista,Minutos:Segundos,Album");
        Cancion *aux = firstHashTable(cancion);
        while(aux != NULL){
            fprintf(archivo, aux ->nombreArtista, aux -> nombreArtista, aux ->duracion, aux ->nombreAlbum);
            aux = nextHashTable(cancion);
        }
        fclose(archivo);
        printf("Musicas guardadas! \n");
    }
}

Cancion *getLinea(char linea[1024]){
    Cancion *aux = (Cancion *) calloc(1, sizeof(Cancion)); 
    /* 
    char cancion[101];
    char artista[101];
    char duracion[10];
    char album[201];
    */
    strcpy(aux -> nombreCancion, strtok(linea, ","));
    strcpy(aux -> nombreArtista, strtok(NULL, ","));
    strcpy(aux -> duracion, strtok(NULL, ","));
    strcpy(aux -> nombreAlbum, strtok(NULL, "\n"));
    return aux;
}

bool cargarArchivo(char nombre[301], HashTable *artistaHT, HashTable *albumHT, HashTable *cancionHT){
    FILE *nombreArchivo = fopen(nombre, "r");  
    Cancion *cancionAux =(Cancion *) calloc(1, sizeof(Cancion));  
    HashTable *mapAux = createHashTable(1);
    char linea[1024];
    if(nombreArchivo != NULL){
        fgets(linea, 1023, nombreArchivo);
        strtok(linea, "\n");
        while((fgets(linea, 1023, nombreArchivo)) != EOF){
            cancionAux = getLinea(linea);
            if(searchHashTable(cancionHT, cancionAux ->nombreCancion) == NULL){         //La Cancion no existe en el mapa de Canciones
                insertHashTable(cancionHT, cancionAux ->nombreCancion, cancionAux);
            }
            if(searchHashTable(artistaHT, cancionAux ->nombreArtista) == NULL){         //El Artista no existe en el Mapa de Artistas
                insertHashTable(mapAux, cancionAux ->nombreArtista, cancionAux);
                insertHashTable(artistaHT, cancionAux ->nombreArtista, mapAux);
                removeAllMap(mapAux);                                                   //El Mapa auxiliar se limpia para evitar colisiones por usar el mismo mapa
            }
            if(searchHashTable(albumHT, cancionAux ->nombreAlbum) == NULL){             //El Album no existe en el Mapa de Albums
                insertHashTable(mapAux, cancionAux -> nombreAlbum, cancionAux);
                insertHashTable(albumHT, cancionAux -> nombreAlbum, mapAux);
                removeAllMap(mapAux);                                                   //El Mapa auxiliar se limpia para evitar colisiones por usar el mismo mapa
            }
        }
    }else printf("Archivo Vacío... Ingrese uno con musica \n");
}