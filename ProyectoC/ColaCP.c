#include <stdio.h>
#include <stdlib.h>
#include "ColaCP.h"
#define CP_VAC 3
#define POS_NULA NULL
#define ELE_NULO NULL

/**Atributo del comparador**/
int (*fc)(TEntrada, TEntrada);

///Intercambio entre nodos y entradas
void reemplazar(TEntrada a, TEntrada b){
    TClave ca = a->clave;
    TValor va = a->valor;
    a->clave=b->clave;
    a->valor=b->valor;
    b->clave=ca;
    b->valor=va;
}
void intercambio(TNodo x, TNodo y){
    TEntrada temp=x->entrada;
    reemplazar(x->entrada, y->entrada);
    reemplazar (y->entrada, temp);
}

///Ordenamientos heap
void upHeap(TColaCP cola, TNodo v){
    TNodo u;
    while (v->entrada->clave!=cola->raiz->entrada->clave){
        u=v->padre;
        if (fc(u->entrada, v->entrada)<=0)
            break;
        intercambio(u,v);
        v=u;
    }
}
void downHeap(TColaCP cola, TNodo r){
    while (r->hijo_izquierdo!=POS_NULA){
        TNodo s;
        if (r->hijo_derecho==POS_NULA)
            s=r->hijo_izquierdo;
        else if (fc(r->hijo_izquierdo->entrada, r->hijo_derecho->entrada)<=0)
                s=r->hijo_izquierdo;
        else
                s=r->hijo_derecho;
        if (fc(s->entrada, r->entrada)<0){
            intercambio(r,s);
            r=s;
            }
        else
            break;
    }
}

///Creacion de la cola
TColaCP crear_cola_cp(TColaCP cola, int (*f)(TEntrada,TEntrada)){
    cola =(TColaCP) malloc(sizeof(struct cola_con_prioridad));
    cola->raiz=POS_NULA;
    cola->cantidad_elementos=(int) malloc(sizeof(int)*4);
    cola->cantidad_elementos=0;
    fc=f;
    return cola;
}

///Metodo auxiliar para insercion
TNodo pos_a_insertar(TColaCP cola, int size){
    TNodo aux;
    if(size==1){
        aux= cola->raiz;
    }
    else{
        aux=pos_a_insertar(cola ,size/2);
        if(size%2==0){
            aux=aux->hijo_izquierdo;
        }
        else {
            aux=aux->hijo_derecho;
        }
    }
    return aux;
}

///Agrega al final
TNodo add(TColaCP cola, TEntrada entr){
    TNodo nuevo = (TNodo) malloc(sizeof(struct nodo));
    nuevo->entrada=entr;
    nuevo->hijo_derecho=POS_NULA;
    nuevo->hijo_izquierdo=POS_NULA;
   if (cola->cantidad_elementos==1){
        cola->raiz=nuevo;
        nuevo->padre=POS_NULA;
        }
    else{
        TNodo padre= pos_a_insertar(cola,cola->cantidad_elementos/2);
        nuevo->padre=padre;
        if(padre->hijo_izquierdo==POS_NULA)
            padre->hijo_izquierdo=nuevo;
        else
            padre->hijo_derecho=nuevo;
           //printf(" hijo %i padre %i  \n ",a(A_insertar),a(padre));
        }
    return nuevo;
}

///Agrega la entrada entr en la cola. Retorna verdadero si procede con  exito, falso en caso contrario.
int cp_insertar(TColaCP cola, TEntrada entr){
    cola->cantidad_elementos++;
    upHeap(cola, add(cola, entr));
    return 1;
    //En que caso falla ?
}

///Elimina y retorna la entrada con mayor prioridad de la cola. Reacomoda la estructura heap de forma consistente.
//Si la cola es vacia, retorna ELE NULO.
TEntrada remov(TColaCP cola){
    TEntrada toRet=cola->raiz->entrada;
    if(cola->cantidad_elementos==1){
        free(cola->raiz);
        cola->raiz=POS_NULA;
    }
    else{
        TNodo padre = pos_a_insertar(cola,cola->cantidad_elementos/2);
        TEntrada aux;
        if(padre->hijo_derecho!=POS_NULA){
             aux= padre->hijo_derecho->entrada;
            free(padre->hijo_derecho);
            padre->hijo_derecho=POS_NULA;
        }
        else{
             aux= padre->hijo_izquierdo->entrada;
            free(padre->hijo_izquierdo);
            padre->hijo_izquierdo=POS_NULA;
        }
        cola->raiz->entrada=aux;
    }
 //   cola->cantidad_elementos=cola->cantidad_elementos-1;
    return toRet;
}

TEntrada cp_eliminar(TColaCP cola){
    if (cola->cantidad_elementos==0)
        return ELE_NULO;
    TEntrada min = cola->raiz->entrada;
    if (cola->cantidad_elementos==1)        //Para liberar espacio en memoria, guardo el remov(cola) para luego hacerle free ?
        remov(cola);
    else{
        reemplazar(cola->raiz->entrada, remov(cola));
        downHeap(cola, cola->raiz);
        }
    cola->cantidad_elementos--;
    return min;
}

///Retorna la cantidad de entradas de la cola.
int cp_size(TColaCP cola){
    return cola->cantidad_elementos;
}

///Elimina todos los elementos y libera toda la memoria utilizada por la cola .
//Retorna verdadero si procede con  exito, falso en caso contrario.
int cp_destruir(TColaCP cola){
    while (cola->cantidad_elementos>0)
        cp_eliminar(cola);
    free(cola);
    return 1;
}

///Retorna la entrada con mayor prioridad
TEntrada min(TColaCP cola){
    if (cola->cantidad_elementos==0)
        return POS_NULA;
    return cola->raiz->entrada;
}
