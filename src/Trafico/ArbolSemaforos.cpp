#include "ArbolSemaforos.h"
#include "Semaforo.h"  
#include "Nodo.h"
#include <iostream>

void ArbolSemaforos::insertar(Semaforo* semaforo, Nodo* nodo1, Nodo* nodo2) {
    insertarAux(raiz, semaforo, nodo1, nodo2);
}

void ArbolSemaforos::insertarAux(NodoArbol*& nodo, Semaforo* semaforo, Nodo* nodo1, Nodo* nodo2) {
    if (nodo == nullptr) {
        float direccionX = nodo2->obtenerPosicion().x - nodo1->obtenerPosicion().x;
        float direccionY = nodo2->obtenerPosicion().y - nodo1->obtenerPosicion().y;

        float longitud = std::sqrt(direccionX * direccionX + direccionY * direccionY);
        direccionX /= longitud;
        direccionY /= longitud;

        float distancia = 40.0f; 
        float semaforoX = nodo1->obtenerPosicion().x + direccionX * distancia;
        float semaforoY = nodo1->obtenerPosicion().y + direccionY * distancia;

        semaforo->setPosicion(semaforoX, semaforoY);
        nodo = new NodoArbol(semaforo);
    } else {
        if (semaforo->obtenerPosicion().x < nodo->semaforo->obtenerPosicion().x) {
            insertarAux(nodo->izquierdo, semaforo, nodo1, nodo2);
        } else {
            insertarAux(nodo->derecho, semaforo, nodo1, nodo2);
        }
    }
}

void ArbolSemaforos::recorrerEnOrden(NodoArbol* nodo, sf::RenderWindow& ventana) const {
    static sf::Clock reloj; 
    if (nodo != nullptr) {
        recorrerEnOrden(nodo->izquierdo, ventana);
        float deltaTime = reloj.restart().asSeconds(); 
        nodo->semaforo->actualizar(deltaTime); 
        nodo->semaforo->dibujar(ventana);
        recorrerEnOrden(nodo->derecho, ventana);
    }
}


void ArbolSemaforos::dibujarSemaforos(sf::RenderWindow& ventana) {
    if (raiz == nullptr) {
    } else {
        recorrerEnOrden(raiz, ventana);
    }
}

void ArbolSemaforos::actualizarSemaforos(float deltaTime) {
    if (raiz == nullptr) return;
    actualizarRecursivo(raiz, deltaTime);
}

void ArbolSemaforos::actualizarRecursivo(NodoArbol* nodo, float deltaTime) {
    if (nodo == nullptr) return;

    actualizarRecursivo(nodo->izquierdo, deltaTime);
    nodo->semaforo->actualizar(deltaTime);
    actualizarRecursivo(nodo->derecho, deltaTime);
}