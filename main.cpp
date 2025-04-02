#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

// Definición del nodo AVL
struct Nodo {
    int valor;
    Nodo* izquierdo;
    Nodo* derecho;
    int altura;

    Nodo(int v) : valor(v), izquierdo(nullptr), derecho(nullptr), altura(1) {}
};

// Función para obtener la altura de un nodo
int obtenerAltura(Nodo* nodo) {
    return (nodo == nullptr) ? 0 : nodo->altura;
}

// Función para contar el número de nodos en el árbol
int contarNodos(Nodo* nodo) {
    if (nodo == nullptr) return 0;
    return 1 + contarNodos(nodo->izquierdo) + contarNodos(nodo->derecho);
}

// Rotaciones
Nodo* rotarDerecha(Nodo* y) {
    Nodo* x = y->izquierdo;
    Nodo* T2 = x->derecho;

    x->derecho = y;
    y->izquierdo = T2;

    y->altura = max(obtenerAltura(y->izquierdo), obtenerAltura(y->derecho)) + 1;
    x->altura = max(obtenerAltura(x->izquierdo), obtenerAltura(x->derecho)) + 1;

    return x;
}

Nodo* rotarIzquierda(Nodo* x) {
    Nodo* y = x->derecho;
    Nodo* T2 = y->izquierdo;

    y->izquierdo = x;
    x->derecho = T2;

    x->altura = max(obtenerAltura(x->izquierdo), obtenerAltura(x->derecho)) + 1;
    y->altura = max(obtenerAltura(y->izquierdo), obtenerAltura(y->derecho)) + 1;

    return y;
}

// Inserción en AVL
Nodo* insertarNodo(Nodo* nodo, int valor) {
    if (nodo == nullptr) return new Nodo(valor);

    if (valor < nodo->valor)
        nodo->izquierdo = insertarNodo(nodo->izquierdo, valor);
    else if (valor > nodo->valor)
        nodo->derecho = insertarNodo(nodo->derecho, valor);
    else
        return nodo;

    nodo->altura = 1 + max(obtenerAltura(nodo->izquierdo), obtenerAltura(nodo->derecho));
    int balance = obtenerAltura(nodo->izquierdo) - obtenerAltura(nodo->derecho);

    if (balance > 1 && valor < nodo->izquierdo->valor)
        return rotarDerecha(nodo);
    if (balance < -1 && valor > nodo->derecho->valor)
        return rotarIzquierda(nodo);
    if (balance > 1 && valor > nodo->izquierdo->valor) {
        nodo->izquierdo = rotarIzquierda(nodo->izquierdo);
        return rotarDerecha(nodo);
    }
    if (balance < -1 && valor < nodo->derecho->valor) {
        nodo->derecho = rotarDerecha(nodo->derecho);
        return rotarIzquierda(nodo);
    }

    return nodo;
}

// Función para recorrer el árbol en orden y guardar los valores en un vector
void recorrerEnOrden(Nodo* nodo, vector<int>& valores) {
    if (nodo == nullptr) return;
    recorrerEnOrden(nodo->izquierdo, valores);
    valores.push_back(nodo->valor);
    recorrerEnOrden(nodo->derecho, valores);
}

// Función para encontrar el nivel de un valor en el árbol
int encontrarNivel(Nodo* raiz, int valor, int nivel = 0) {
    if (raiz == nullptr) return -1;
    if (raiz->valor == valor) return nivel;
    
    if (valor < raiz->valor) 
        return encontrarNivel(raiz->izquierdo, valor, nivel + 1);
    else 
        return encontrarNivel(raiz->derecho, valor, nivel + 1);
}

void encontrarMedianaYNivel(Nodo* raiz) {
    if (raiz == nullptr) {
        cout << "El árbol está vacío." << endl;
        return;
    }

    vector<int> valores;
    recorrerEnOrden(raiz, valores);

    int n = valores.size();
    double mediana = 0;
    int central1 = 0, central2 = 0;

    if (n % 2 == 1) {
        // Caso impar
        central1 = valores[n / 2];
        mediana = central1;

        int nivelMediana = encontrarNivel(raiz, central1);
        cout << "Dato central: " << central1 << " (Nivel: " << nivelMediana << ")" << endl;
    } else {
        // Caso par
        central1 = valores[n / 2 - 1];
        central2 = valores[n / 2];
        mediana = (central1 + central2) / 2.0;

        int nivel1 = encontrarNivel(raiz, central1);
        int nivel2 = encontrarNivel(raiz, central2);

        cout << "Datos centrales: " << central1 << " (Nivel: " << nivel1 << ") y " 
             << central2 << " (Nivel: " << nivel2 << ")" << endl;
    }

    cout << "Mediana: " << mediana << endl;
}


// Función para cargar datos desde un archivo
Nodo* cargarArchivo(const string& nombreArchivo, Nodo* raiz) {
    ifstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        cerr << "Error al abrir el archivo." << endl;
        return raiz;
    }

    char operacion;
    float valor;
    while (archivo >> operacion >> valor) {
        if (operacion == 'A') {
            raiz = insertarNodo(raiz, valor);
            cout << "Agregado: " << valor << endl;  // Depuración
        }
    }

    archivo.close();
    return raiz;
}

// Función principal
int main() {
    Nodo* raiz = nullptr;
    raiz = cargarArchivo("in_00.txt", raiz);

    encontrarMedianaYNivel(raiz);
    
    return 0;
}
