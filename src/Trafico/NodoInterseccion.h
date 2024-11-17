#ifndef NODOINTERSECCION_H
#define NODOINTERSECCION_H

#include "Interseccion.h"

class NodoInterseccion {
public:
    Interseccion* interseccion;
    NodoInterseccion* izquierda;
    NodoInterseccion* derecha;

    NodoInterseccion(Interseccion* interseccion)
        : interseccion(interseccion), izquierda(nullptr), derecha(nullptr) {}
};

#endif //NODOINTERSECCION_H