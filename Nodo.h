#ifndef NODO_H
#define NODO_H

struct Nodo {
    int dato;
    int altura;
    Nodo* izquierdo;
    Nodo* derecho;

    Nodo(int valor) {
        dato = valor;
        altura = 1; // nuevo nodo siempre se crea con altura 1
        izquierdo = nullptr;
        derecho = nullptr;
    }
};

#endif

