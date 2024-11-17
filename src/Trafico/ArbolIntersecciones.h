#ifndef ARBOLINTERSECCIONES_H
#define ARBOLINTERSECCIONES_H

#include "NodoInterseccion.h"

class ArbolIntersecciones {
public:
    NodoInterseccion* raiz;

    ArbolIntersecciones() : raiz(nullptr) {}

    void insertar(Interseccion* interseccion) {
        raiz = insertarRecursivo(raiz, interseccion);
    }

    NodoInterseccion* insertarRecursivo(NodoInterseccion* raiz, Interseccion* interseccion) {
        if (raiz == nullptr) {
            return new NodoInterseccion(interseccion);
        }
        if (interseccion->prioridad < raiz->interseccion->prioridad) {
            raiz->izquierda = insertarRecursivo(raiz->izquierda, interseccion);
        } else {
            raiz->derecha = insertarRecursivo(raiz->derecha, interseccion);
        }
        return raiz;
    }

    void mostrarIntersecciones(NodoInterseccion* nodo) {
        if (nodo != nullptr) {
            mostrarIntersecciones(nodo->izquierda);
            std::cout << "Intersección: " << nodo->interseccion->nombre
                      << ", Prioridad: " << nodo->interseccion->prioridad << "\n";
            mostrarIntersecciones(nodo->derecha);
        }
    }
};

#endif //ARBOLINTERSECCIONES_H