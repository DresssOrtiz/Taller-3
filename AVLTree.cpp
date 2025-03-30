#include "AVLTree.h"

AVLTree::AVLTree() {
    raiz = nullptr;
}

AVLTree::~AVLTree() {
    // TODO: liberar memoria recursivamente si se desea
}

void AVLTree::insertar(int valor) {
    raiz = insertar(raiz, valor);
}

Nodo* AVLTree::insertar(Nodo* nodo, int valor) {
    if (nodo == nullptr) {
        return new Nodo(valor);
    }

    if (valor < nodo->dato) {
        nodo->izquierdo = insertar(nodo->izquierdo, valor);
    } else if (valor > nodo->dato) {
        nodo->derecho = insertar(nodo->derecho, valor);
    } else {
        return nodo;
    }

    int alturaIzq = altura(nodo->izquierdo);
    int alturaDer = altura(nodo->derecho);
    if (alturaIzq > alturaDer) {
        nodo->altura = 1 + alturaIzq;
    } else {
        nodo->altura = 1 + alturaDer;
    }

    int balanceFactor = balance(nodo);

    if (balanceFactor > 1 && valor < nodo->izquierdo->dato) {
        return rotacionDerecha(nodo);
    }
    if (balanceFactor < -1 && valor > nodo->derecho->dato) {
        return rotacionIzquierda(nodo);
    }
    if (balanceFactor > 1 && valor > nodo->izquierdo->dato) {
        return rotacionIzquierdaDerecha(nodo);
    }
    if (balanceFactor < -1 && valor < nodo->derecho->dato) {
        return rotacionDerechaIzquierda(nodo);
    }

    return nodo;
}

void AVLTree::eliminar(int valor) {
    raiz = eliminar(raiz, valor);
}

Nodo* AVLTree::eliminar(Nodo* nodo, int valor) {
    if (nodo == nullptr) {
        return nodo;
    }

    if (valor < nodo->dato) {
        nodo->izquierdo = eliminar(nodo->izquierdo, valor);
    } else if (valor > nodo->dato) {
        nodo->derecho = eliminar(nodo->derecho, valor);
    } else {
        if (nodo->izquierdo == nullptr || nodo->derecho == nullptr) {
            Nodo* temp;
            if (nodo->izquierdo != nullptr) {
                temp = nodo->izquierdo;
            } else {
                temp = nodo->derecho;
            }
            delete nodo;
            return temp;
        } else {
            Nodo* temp = nodo->derecho;
            while (temp->izquierdo != nullptr) {
                temp = temp->izquierdo;
            }
            nodo->dato = temp->dato;
            nodo->derecho = eliminar(nodo->derecho, temp->dato);
        }
    }

    int alturaIzq = altura(nodo->izquierdo);
    int alturaDer = altura(nodo->derecho);
    if (alturaIzq > alturaDer) {
        nodo->altura = 1 + alturaIzq;
    } else {
        nodo->altura = 1 + alturaDer;
    }

    int balanceFactor = balance(nodo);

    if (balanceFactor > 1 && balance(nodo->izquierdo) >= 0) {
        return rotacionDerecha(nodo);
    }
    if (balanceFactor > 1 && balance(nodo->izquierdo) < 0) {
        return rotacionIzquierdaDerecha(nodo);
    }
    if (balanceFactor < -1 && balance(nodo->derecho) <= 0) {
        return rotacionIzquierda(nodo);
    }
    if (balanceFactor < -1 && balance(nodo->derecho) > 0) {
        return rotacionDerechaIzquierda(nodo);
    }

    return nodo;
}

void AVLTree::inOrden(std::vector<int>& resultado) {
    inOrden(raiz, resultado);
}

void AVLTree::inOrden(Nodo* nodo, std::vector<int>& resultado) {
    if (nodo == nullptr) {
        return;
    }
    inOrden(nodo->izquierdo, resultado);
    resultado.push_back(nodo->dato);
    inOrden(nodo->derecho, resultado);
}

int AVLTree::obtenerNivel(int valor) {
    return obtenerNivel(raiz, valor, 0);
}

int AVLTree::obtenerNivel(Nodo* nodo, int valor, int nivel) {
    if (nodo == nullptr) {
        return -1;
    }
    if (nodo->dato == valor) {
        return nivel;
    }
    if (valor < nodo->dato) {
        return obtenerNivel(nodo->izquierdo, valor, nivel + 1);
    } else {
        return obtenerNivel(nodo->derecho, valor, nivel + 1);
    }
}

int AVLTree::altura(Nodo* nodo) {
    if (nodo != nullptr) {
        return nodo->altura;
    } else {
        return 0;
    }
}

int AVLTree::balance(Nodo* nodo) {
    if (nodo != nullptr) {
        return altura(nodo->izquierdo) - altura(nodo->derecho);
    } else {
        return 0;
    }
}

Nodo* AVLTree::rotacionIzquierda(Nodo* x) {
    Nodo* y = x->derecho;
    Nodo* T2 = y->izquierdo;

    y->izquierdo = x;
    x->derecho = T2;

    int alturaIzqX = altura(x->izquierdo);
    int alturaDerX = altura(x->derecho);
    if (alturaIzqX > alturaDerX) {
        x->altura = 1 + alturaIzqX;
    } else {
        x->altura = 1 + alturaDerX;
    }

    int alturaIzqY = altura(y->izquierdo);
    int alturaDerY = altura(y->derecho);
    if (alturaIzqY > alturaDerY) {
        y->altura = 1 + alturaIzqY;
    } else {
        y->altura = 1 + alturaDerY;
    }

    return y;
}

Nodo* AVLTree::rotacionDerecha(Nodo* y) {
    Nodo* x = y->izquierdo;
    Nodo* T2 = x->derecho;

    x->derecho = y;
    y->izquierdo = T2;

    int alturaIzqY = altura(y->izquierdo);
    int alturaDerY = altura(y->derecho);
    if (alturaIzqY > alturaDerY) {
        y->altura = 1 + alturaIzqY;
    } else {
        y->altura = 1 + alturaDerY;
    }

    int alturaIzqX = altura(x->izquierdo);
    int alturaDerX = altura(x->derecho);
    if (alturaIzqX > alturaDerX) {
        x->altura = 1 + alturaIzqX;
    } else {
        x->altura = 1 + alturaDerX;
    }

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
