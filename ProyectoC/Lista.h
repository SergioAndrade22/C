#ifndef LISTA_H_INCLUDED
#define LISTA_H_INCLUDED
/// Puntero a elemento
typedef void *TElemento;

/// Puntero a registro de una estructura tipo celda, conteniendo la celda anterior y siguiente, ademas de su elemento
typedef struct celda {
    struct celda *celda_anterior;
    struct celda *celda_siguiente;
    TElemento elemento;
} *TLista;

/// Puntero a celda
typedef struct celda *TPosicion;

/** Crea una lista vacía.
@param Lista a crear
**/
void crear_lista(TLista *lista);

/** Inserta un elemento en la lista
    inserta el elemento en el lugar que ocupa la posicion dada por parametro
    inserta al principio si la posicion dada es NULL
@param Puntero a la lista
@param Posicion a insertar
@param Elemento a contener
@return Devuelve si se inserto correctamente o no
**/
int l_insertar(TLista *lista, TPosicion pos, TElemento elem);

/** Elimina una posicion dada de la lista
    finaliza con exit status (2) su la lista pasada como parametro esta vacia
@param Puntero a la lista
@param Posicion a eliminar
@return Devuelve si se elimino correctamente
**/
int l_eliminar(TLista *lista, TPosicion pos);

/** Devuelve la primer posicion de la lista
    finaliza con exit status (2) si la lista dada por parametro esta vacia
@param Lista
@return Primera posicion de la lista
**/
TPosicion l_primera(TLista lista);

/** Devuelve la primer posicion de la lista
    finaliza con exit status (2) si la lista dad por parametro esta vacia
@param Lista
@param Ultima posicion de la lista
**/
TPosicion l_ultima(TLista lista);

/** Devuelve la posicion anterior a la posicion dada
    finaliza con exit status (2) si la lista pasada por parametro esta vacia
    finaliza con exit status (3) si la posicion pasada por parametro es la primera
@param Lista
@param Posicion
@return Retorna la posicion anterior a la pasada por parametro
**/
TPosicion l_anterior(TLista lista, TPosicion pos);

/** Devuelve la posicion siguiente a la dada
    finaliza con exit status (2) si la lista pasada por parametro esta vacia
    finaliza con exit status (3) si la posicion pasada por parametro es la ultima
@param Lista
@param Posicion
@return Posicion siguiente de la pasada por parametro
**/
TPosicion l_siguiente(TLista lista, TPosicion pos);


/** Devuelve el elemento almacenado en la posicion dada
    finaliza con exit status (2) si la lista pasada por parametro esta vacia
    finaliza con exit status (4) si la posicion pasada por parametro es NULL
@param Lista
@param Posicion
@return Devuelve el elemento en la posicion del elemento
**/
TElemento l_recuperar(TLista lista, TPosicion pos);

/** Da el tamaño de la lista
    devuelve 0 si la lista está vacía.
@param Lista
@return Tamaño de la lista
**/
int l_size(TLista lista);

/** Destruye la lista
    finaliza con exit status (2) si la lista pasada por parametro esta vacia
@param Puntero a la lista
@return Devuelve si se destruyo correctamente la lista o no
**/
int l_destruir(TLista *lista);

#endif // LISTA_H_INCLUDED
