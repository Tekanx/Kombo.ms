#ifndef hash_h
#define hash_h


typedef struct HT_Prop HT_Prop;

typedef struct HashTable HashTable;

/**
 *createHashTable inicializa la tabla con un tamaño ya indicado como parametro
 @param size indica el tamaño que el mapa debe tener una vez que se crea
 @return retorna el mapa con el tamaño ingresado
*/
HashTable *createHashTable(long size);

/**
 *
 @param llave del mapa
 @param Valores correspondiente de la llave
 @return Valores del Mapa
*/
HT_Prop *crearValores(const char *llave, void *valor);

/**

 @param
 @return
*/
unsigned long stringHash(const char * key);

/**

 @param
 @return
*/
long linearProbing(HashTable *tabla, const char *key);

void insertHashTable(HashTable *tabla, const char *llave, void *valor);

void enlarge(HashTable *tabla);

/**

 @param
 @return
*/
void *searchHashTable(HashTable *tabla, const char * llave);

/**

 @param
 @return
*/
void *eraseValueAndSearchKeyHashTable(HashTable *tabla, const char *llave);

/**

 @param
 @return
*/
void *firstHashTable(HashTable *tabla);

/**

 @param
 @return
*/
void *nextHashTable(HashTable * tabla);

#endif
