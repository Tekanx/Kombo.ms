#include <stdlib.h>
#include "lista.h"
#include <assert.h>

typedef struct Node Node;

typedef struct Node {
    /** Puntero al anterior Nodo*/
    Node *prev;
    /** Puntero al dato */
    void *data;
    /** Puntero al siguiente Nodo*/

    Node *next;
}Node;

typedef struct List{
/** Puntero al inicio de la lista*/
    Node *head;
/**Puntero al final de la lista*/
    Node *tail;
/** Puntero para poder recorrer la lista */
    Node *current;
}List;



 Node * createNode(void *data) {
    Node *new = (Node *)malloc(sizeof(Node));
    assert(new != NULL);                        // Si no hay memoria para el nodo, el programa se cierra.
    new -> data = data;
    new -> prev = NULL;
    new -> next = NULL;
    return new;
}

List * createList() {
    List *new = (List *)malloc(sizeof(List));
    assert(new != NULL);                        //Si no hay memoria para la Lista, el programa se cierra.
    new -> head = NULL;
    new -> tail = NULL;
    new -> current = NULL;
    return new;
}


void * list_no_vacia(List *list){
    if (list -> head == NULL) return NULL;
    return (void *) 1;
}


void * first(List *list) {
    assert(list != NULL); // list no puede ser NULL.
    if (list -> head == NULL) return NULL;
    list -> current = list -> head;
    return (void *)list -> current -> data;
}


void * next(List *list) {
    assert(list != NULL); // list no puede ser NULL.
    if (list -> head == NULL            ||
        list -> current == NULL         ||
        list -> current -> next == NULL) return NULL;   // El siguiente no puede ser null, sino crash
    list -> current = list -> current -> next;
    return (void *)list -> current -> data;
}


void * lastList(List *list) {
    assert(list != NULL); // list no puede ser NULL.
    if (list -> head == NULL) return NULL;
    list -> current = list -> tail;
    return (void *)list -> current -> data;
}


void pushFront(List *list, void *data) {
    assert(list != NULL); // list no puede ser NULL.
    Node *new = createNode(data);
    if (list -> head == NULL) list -> tail = new;
    else{
        new -> next = list -> head;
        list -> head -> prev = new;
    }
    list -> head = new;
}


void pushBack(List *list, void *data) {
    assert(list != NULL); // list no puede ser NULL.
    Node *new = createNode(data);
    if (list -> head == NULL)list->head = new;
    else{
        list -> tail -> next = new;
        new -> prev = list -> tail;
    }
    list -> tail = new;
}


void  popFront(List *list) {
    assert(list != NULL); // list no puede ser NULL.
    if (list -> head == NULL) return;
    Node *node = list -> head;
    if (list -> head == list -> tail) {
        list -> tail = NULL;
        list -> head = NULL;
    }
    else{
        list -> head = list -> head -> next;
        list -> head -> prev = NULL;
    }
    free(node);
    return;
}


void  popBack(List *list) {
    assert(list != NULL); // list no puede ser NULL.
    if (list -> head == NULL) return;
    Node * node = list -> tail;
    if (list -> tail == list -> head) {
        list -> tail = NULL;
        list -> head = NULL;
    }
    else{
        list -> tail = list -> tail -> prev;
        list -> tail -> next = NULL;
    }
    free(node);
    return;
}


void  popCurrent(List *list) {
    assert(list != NULL); // list no puede ser NULL.
    if (list -> head == NULL     ||
        list -> current == NULL) return ;

    Node *node = list -> current;
    if (list -> current == list -> head) return popFront(list);
    else if (list -> current == list -> tail) return popBack(list);
    else {
        if (node -> next != NULL) node -> next -> prev = node -> prev;
        if (node -> prev != NULL) node -> prev -> next = node -> next;
    }
    list -> current = node -> next;
    free(node);
    return;
}

void Vaciar (List *list) {
    assert(list != NULL); // list no puede ser NULL.
    while ((list -> head) != NULL) popFront(list);
    free(list);
}

