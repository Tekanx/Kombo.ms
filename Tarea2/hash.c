#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include "hash.h"

typedef struct HT_Prop HT_Prop;

typedef struct HashTable HashTable;

void enlarge(HashTable *tabla);

typedef struct HT_Prop{
    /** Cadena llave */
    const char *llave;
    /** Puntero al Valor */
    void *valor;

}HT_Prop;

typedef struct HashTable{
    /** Arreglo de punteros a Valores*/
    HT_Prop **valores;
    /** Cantidad de datos no nulos en el HT*/
    long cont;
    /** Tama�o del Arreglo*/
    long size;
    /** Variable para poder recorrer el Arreglo*/
    long current;
    /** Factor de carga actual del Arreglo*/
    long factorCarga;
}
}HashTable;

HashTable *createHashTable(long size) {
    HashTable *tabla =(HashTable *) calloc(1, sizeof(HashTable));
    assert(tabla != NULL);                              //Si no hay memoria para reservar la Tabla
    tabla -> valores =(HT_Prop **) calloc(size, sizeof(HT_Prop));
    tabla -> cont = 0;
    tabla -> size = size;
    tabla -> current = -1;
    tabla -> factorCarga = (long)ceil(size * 0.77);
    return tabla;
}

HT_Prop *crearValores(const char *llave, void *valor){
    HT_Prop *newValor;
    newValor = calloc(1, sizeof(HT_Prop));
    newValor -> llave = strdup(llave);
    newValor -> valor = strdup(valor);
    if(newValor == NULL) return NULL;
    if(newValor -> llave == NULL) return NULL;
    if(newValor -> valor == NULL) return NULL;
    return newValor;
}

unsigned long stringHash(const char * key) {
    unsigned long var = 5381;
    long max = strlen(key);
    long auxKey;
    for(int i = 0 ; i < max ; i++){
        var *= 33;
        auxKey = key[i];
        var += auxKey;
    }
    return var;
}

long linearProbing(HashTable *tabla, const char *key) {
    unsigned long i;
    i = stringHash(key);
    i %= tabla -> size;
    while((tabla -> valores[i] != NULL) && (strcasecmp(key, tabla -> valores[i] -> llave) == 0)){
        i ++;
        if(i % tabla -> size == 0) i %= tabla -> size; //Modulo a la posicion al avanzar
    }
    return i;
}

void insertHashTable(HashTable *tabla, const char *llave, void *valor) {
    HT_Prop *V = calloc(1, sizeof(HT_Prop));
    V = crearValores(llave, valor);
    long posicionllave;
    posicionllave = linearProbing(tabla, llave) % tabla -> size;
    if((tabla -> cont / tabla -> size) > (tabla -> factorCarga)) enlarge(tabla);
    if((tabla -> valores[posicionllave] == NULL)
    ||(tabla -> valores[posicionllave] -> valor == NULL)){
        tabla -> valores[posicionllave] = V;
        tabla -> cont ++;
    }
}

void enlarge(HashTable *tabla) {
    long oldsize;
    HT_Prop **old = tabla -> valores;
    oldsize = tabla -> size;
    tabla -> valores = calloc(oldsize * 2, sizeof(HT_Prop));
    tabla -> cont = 0;
    tabla -> size = oldsize * 2;
    tabla -> factorCarga = (long) ceil((oldsize * 2) * 0.77);
    for(int i = 0 ; i < oldsize ; i++){                                         //Se usa el tama�o antiguo y no el nuevo
        if(old[i] != NULL){
            insertHashTable(tabla, old[i] -> llave, old[i] -> valor);
            free(old[i]);
        }
    }
}

void *searchHashTable(HashTable *tabla, const char * llave) {
    long posicionLlave = linearProbing(tabla, llave);
    long i = posicionLlave % tabla -> size;
    if(tabla -> valores[i] == NULL) return NULL;
    tabla -> current = posicionLlave;
    return tabla -> valores[i] -> valor;
}

void *eraseValueAndSearchKeyHashTable(HashTable *tabla, const char *llave) {
    if (tabla == NULL) return NULL;
    long i = linearProbing(tabla, llave) % tabla -> size;
    void *dato = NULL;
    if((tabla -> valores[i] == NULL) && (tabla -> valores[i] -> valor != NULL)){
        dato = tabla -> valores[i] -> valor;
        tabla -> valores[i] -> valor = NULL;
        return dato;
    }
    return dato;
}

void *firstHashTable(HashTable *tabla){
    if(tabla == NULL
    || tabla -> valores == NULL) return NULL;
    long max;
    max = tabla -> size;
    for(long i = 0 ; i < max ; i++) {
        if(tabla -> valores[i] != NULL
        && tabla -> valores[i] -> valor != NULL) {
            tabla -> current = i;
            return tabla -> valores[i] -> valor;
        }
    }
    return NULL;
}

void *nextHashTable(HashTable * tabla) {
    if(tabla == NULL
    || tabla -> valores == NULL) return NULL;
    long max;
    max = tabla -> size;
    for(long i = ((tabla -> current) + 1) ; i < max ; i++) {
        if(tabla -> valores[i] != NULL
        && tabla -> valores[i] -> valor != NULL) {
            tabla -> current = i;
            return tabla -> valores[i] -> valor;
        }
    }
    return NULL;
}
void removeAllMap(HashTable *map) {
    assert(map != NULL); // El mapa no puede ser NULL.
    long i;
    for (i = 0; i < map -> size; i++) {
        if (map -> valores[i] != NULL) free(map -> valores[i]);
    }
    free(map -> valores);
    map -> cont = 0;
    map -> current = -1;
    map -> size = 1;
    map -> factorCarga = (long) ceil((map -> size) * 0.77);
    map -> valores =(HT_Prop **) calloc(map -> size, sizeof(HT_Prop));


}