#ifndef NODOARBOL_H
#define NODOARBOL_H

class Semaforo;

class NodoArbol {
public:
    Semaforo* semaforo;
    NodoArbol* izquierdo;
    NodoArbol* derecho;

    // Constructor
    NodoArbol(Semaforo* semaforo) 
        : semaforo(semaforo), izquierdo(nullptr), derecho(nullptr) {}
};

#endif // NODOARBOL_H