#include "AVLTree.h"
#include <algorithm> // para std::max

AVLTree::AVLTree() {
    raiz = nullptr;
}

AVLTree::~AVLTree() {
    // TODO: liberar memoria recursivamente si se desea
}

int AVLTree::altura(Nodo* nodo) {
    return nodo ? nodo->altura : 0;
}

int AVLTree::balance(Nodo* nodo) {
    return nodo ? altura(nodo->izquierdo) - altura(nodo->derecho) : 0;
}

int AVLTree::max(int a, int b) {
    return (a > b) ? a : b;
}

Nodo* AVLTree::rotacionIzquierda(Nodo* x) {
    Nodo* y = x->derecho;
    Nodo* T2 = y->izquierdo;

    y->izquierdo = x;
    x->derecho = T2;

    x->altura = 1 + max(altura(x->izquierdo), altura(x->derecho));
    y->altura = 1 + max(altura(y->izquierdo), altura(y->derecho));

    return y;
}

Nodo* AVLTree::rotacionDerecha(Nodo* y) {
    Nodo* x = y->izquierdo;
    Nodo* T2 = x->derecho;

    x->derecho = y;
    y->izquierdo = T2;

    y->altura = 1 + max(altura(y->izquierdo), altura(y->derecho));
    x->altura = 1 + max(altura(x->izquierdo), altura(x->derecho));

    return x;
}

Nodo* AVLTree::rotacionIzquierdaDerecha(Nodo* nodo) {
    nodo->izquierdo = rotacionIzquierda(nodo->izquierdo);
    return rotacionDerecha(nodo);
}

Nodo* AVLTree::rotacionDerechaIzquierda(Nodo* nodo) {
    nodo->derecho = rotacionDerecha(nodo->derecho);
    return rotacionIzquierda(nodo);
}

void AVLTree::insertar(int valor) {
    raiz = insertar(raiz, valor);
}

Nodo* AVLTree::insertar(Nodo* nodo, int valor) {
    if (!nodo) return new Nodo(valor);

    if (valor < nodo->dato)
        nodo->izquierdo = insertar(nodo->izquierdo, valor);
    else if (valor > nodo->dato)
        nodo->derecho = insertar(nodo->derecho, valor);
    else
        return nodo; // duplicados no se insertan

    nodo->altura = 1 + max(altura(nodo->izquierdo), altura(nodo->derecho));
    int balanceFactor = balance(nodo);

    // Casos de desbalance
    if (balanceFactor > 1 && valor < nodo->izquierdo->dato)
        return rotacionDerecha(nodo);
    if (balanceFactor < -1 && valor > nodo->derecho->dato)
        return rotacionIzquierda(nodo);
    if (balanceFactor > 1 && valor > nodo->izquierdo->dato)
        return rotacionIzquierdaDerecha(nodo);
    if (balanceFactor < -1 && valor < nodo->derecho->dato)
        return rotacionDerechaIzquierda(nodo);

    return nodo;
}

void AVLTree::eliminar(int valor) {
    raiz = eliminar(raiz, valor);
}

Nodo* AVLTree::eliminar(Nodo* nodo, int valor) {
    if (!nodo) return nodo;

    if (valor < nodo->dato)
        nodo->izquierdo = eliminar(nodo->izquierdo, valor);
    else if (valor > nodo->dato)
        nodo->derecho = eliminar(nodo->derecho, valor);
    else {
        // Nodo con uno o ningún hijo
        if (!nodo->izquierdo || !nodo->derecho) {
            Nodo* temp = nodo->izquierdo ? nodo->izquierdo : nodo->derecho;
            delete nodo;
            return temp;
        } else {
            // Nodo con dos hijos: reemplazar con sucesor
            Nodo* temp = nodo->derecho;
            while (temp->izquierdo)
                temp = temp->izquierdo;
            nodo->dato = temp->dato;
            nodo->derecho = eliminar(nodo->derecho, temp->dato);
        }
    }

    nodo->altura = 1 + max(altura(nodo->izquierdo), altura(nodo->derecho));
    int balanceFactor = balance(nodo);

    // Rebalancear si es necesario
    if (balanceFactor > 1 && balance(nodo->izquierdo) >= 0)
        return rotacionDerecha(nodo);
    if (balanceFactor > 1 && balance(nodo->izquierdo) < 0)
        return rotacionIzquierdaDerecha(nodo);
    if (balanceFactor < -1 && balance(nodo->derecho) <= 0)
        return rotacionIzquierda(nodo);
    if (balanceFactor < -1 && balance(nodo->derecho) > 0)
        return rotacionDerechaIzquierda(nodo);

    return nodo;
}

void AVLTree::inOrden(std::vector<int>& resultado) {
    inOrden(raiz, resultado);
}

void AVLTree::inOrden(Nodo* nodo, std::vector<int>& resultado) {
    if (!nodo) return;
    inOrden(nodo->izquierdo, resultado);
    resultado.push_back(nodo->dato);
    inOrden(nodo->derecho, resultado);
}

int AVLTree::obtenerNivel(int valor) {
    return obtenerNivel(raiz, valor, 0);
}

int AVLTree::obtenerNivel(Nodo* nodo, int valor, int nivel) {
    if (!nodo) return -1;
    if (nodo->dato == valor) return nivel;
    if (valor < nodo->dato)
        return obtenerNivel(nodo->izquierdo, valor, nivel + 1);
    else
        return obtenerNivel(nodo->derecho, valor, nivel + 1);
}

