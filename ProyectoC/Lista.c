#include <stdio.h>
#include <stdlib.h>
#include "Lista.h"
// Valores para finalizacion inesperada o en error del programa
#define LST_VAC 2
#define POS_NULA 3
#define ELE_NULO 4

void crear_lista(TLista *lista){
    *lista = NULL;
}

int l_size(TLista lista){
    TPosicion reader = lista;
    int tot = 0;
    while (!(reader == NULL)){
        tot++;
        reader = reader->celda_siguiente;
    }
    return tot;
}

int l_insertar(TLista *lista, TPosicion pos, TElemento elem){
    TPosicion toAdd;
    toAdd = (struct celda*) malloc(sizeof(struct celda));
    toAdd->elemento = elem;
    if (pos == NULL){ // Insertar al principio
        toAdd->celda_anterior = NULL;
        toAdd->celda_siguiente = (*lista);
        *lista = toAdd;
    }
    else{
        if (pos->celda_anterior == NULL){ // Insertar en la posicion del primer lugar (analogo al caso anterior, lo pide el enunciado)
            toAdd->celda_siguiente = pos;
            toAdd->celda_anterior = NULL;
            pos->celda_anterior = toAdd;
            *lista = toAdd;
        }
        else{ // Caso general de insercion
            toAdd->celda_anterior = pos->celda_anterior;
            toAdd->celda_siguiente = pos;
            pos->celda_anterior->celda_siguiente = toAdd;
            pos->celda_anterior = toAdd;
        }
    }
    return 1;
}

TPosicion l_primera(TLista lista){
    if (lista == NULL)
        exit(LST_VAC);
    TPosicion toRet = lista;
    return toRet;
}

TPosicion l_ultima(TLista lista){
    if (lista == NULL)
        exit(LST_VAC);
    TPosicion aux = lista;
    while (aux->celda_siguiente != NULL){ // Ciclo que busca la ultima posicion
        aux = aux->celda_siguiente;
    }
    return aux;
}

int l_eliminar(TLista *lista, TPosicion pos){
    if (*lista == NULL)
        exit(LST_VAC);
    if ((pos->celda_anterior) == NULL){ // Caso de eleminacion para el primer elemento de la lista
        *lista = pos->celda_siguiente;
        (*lista)->celda_anterior = NULL;
    }
    else{
        if((pos->celda_siguiente) == NULL){ // Caso de eliminacion para el ultimo elemento de la lista
            pos->celda_anterior->celda_siguiente = NULL;
        }
        else{ // Caso general de eliminacion
            pos->celda_anterior->celda_siguiente = pos->celda_siguiente;
            pos->celda_siguiente->celda_anterior = pos->celda_anterior;
        }
    }
    pos->celda_siguiente = NULL;
    pos->celda_anterior = NULL;
    return 1;
}

TPosicion l_anterior(TLista lista, TPosicion pos){
    if (lista == NULL)
        exit(LST_VAC);
    if (pos == l_primera(lista))
        exit(POS_NULA);
    return pos->celda_anterior;
}

TPosicion l_siguiente(TLista lista, TPosicion pos){
    if (lista == NULL)
        exit(LST_VAC);
    if (pos == l_ultima(lista))
        exit(POS_NULA);
    return pos->celda_siguiente;
}

TElemento l_recuperar(TLista lista, TPosicion pos){
    if (pos == NULL)
        exit(LST_VAC);
    if (pos == NULL)
        exit(ELE_NULO);
    return pos->elemento;
}

int l_destruir(TLista *lista){
    if (*lista == NULL)
        return 1;
    TPosicion reader = l_primera(*lista); // Variable usada para recorrer la estructura
    TPosicion aux = NULL; // Variable usada para no perder el lugar en la estructura al liberar memoria
    while (!(reader == NULL)){
        aux = reader->celda_siguiente;
        free(reader->celda_anterior);
        free(reader->elemento);
        reader = aux;
    }
    *lista = NULL;
    return 1;
}
