#ifndef AVLTREE_H
#define AVLTREE_H

#include <vector>
#include "Nodo.h"

class AVLTree {
private:
    Nodo* raiz;

    // Funciones internas recursivas
    Nodo* insertar(Nodo* nodo, int valor);
    Nodo* eliminar(Nodo* nodo, int valor);
    Nodo* rotacionIzquierda(Nodo* nodo);
    Nodo* rotacionDerecha(Nodo* nodo);
    Nodo* rotacionIzquierdaDerecha(Nodo* nodo);
    Nodo* rotacionDerechaIzquierda(Nodo* nodo);

    int altura(Nodo* nodo);
    int balance(Nodo* nodo);
    int max(int a, int b);

    void inOrden(Nodo* nodo, std::vector<int>& resultado);
    int obtenerNivel(Nodo* nodo, int valor, int nivel);

public:
    AVLTree();
    ~AVLTree();
    
    void insertar(int valor);
    void eliminar(int valor);
    void inOrden(std::vector<int>& resultado);
    int obtenerNivel(int valor);
};

#endif

