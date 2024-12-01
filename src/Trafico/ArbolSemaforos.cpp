#include "ArbolSemaforos.h"
#include "Semaforo.h"  
#include "Nodo.h"
#include <iostream>
#include <cmath>

void ArbolSemaforos::insertar(Semaforo* semaforo, Nodo* nodo1, Nodo* nodo2) {
    insertarAux(raiz, semaforo, nodo1, nodo2);
}

void ArbolSemaforos::insertarAux(NodoArbol*& nodo, Semaforo* semaforo, Nodo* nodo1, Nodo* nodo2) {
    float direccionX = nodo2->obtenerPosicion().x - nodo1->obtenerPosicion().x;
    float direccionY = nodo2->obtenerPosicion().y - nodo1->obtenerPosicion().y;

    float longitud = std::sqrt(direccionX * direccionX + direccionY * direccionY);
    direccionX /= longitud;
    direccionY /= longitud;

    float distancia = 40.0f; 

    sf::Vector2f posicionSemaforo(
        nodo1->obtenerPosicion().x + direccionX * distancia,
        nodo1->obtenerPosicion().y + direccionY * distancia
    );

    if (nodo1->tieneSemaforoEnConexion(nodo2)) {
        return;
    }

    if (nodo == nullptr) {
        semaforo->setPosicion(posicionSemaforo.x, posicionSemaforo.y);
        nodo = new NodoArbol(semaforo);

        nodo1->agregarSemaforoConexion(nodo2, semaforo);
        std::cout << "Semáforo agregado en la posición: (" 
                  << posicionSemaforo.x << ", " << posicionSemaforo.y << ")\n";
    } else {
        if (direccionX > 0 && direccionY == 0) {
            insertarAux(nodo->derecho, semaforo, nodo1, nodo2);
        } else if (direccionX < 0 && direccionY == 0) {
            insertarAux(nodo->izquierdo, semaforo, nodo1, nodo2);
        } else if (direccionX == 0 && direccionY > 0) {
            insertarAux(nodo->derecho, semaforo, nodo1, nodo2);
        } else if (direccionX == 0 && direccionY < 0) {
            insertarAux(nodo->izquierdo, semaforo, nodo1, nodo2);
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

bool ArbolSemaforos::existeSemaforoEnPosicion(NodoArbol* nodo, const sf::Vector2f& posicion, float tolerancia) const {
    if (nodo == nullptr) return false;

    float distanciaX = nodo->semaforo->obtenerPosicion().x - posicion.x;
    float distanciaY = nodo->semaforo->obtenerPosicion().y - posicion.y;
    float distancia = std::sqrt(distanciaX * distanciaX + distanciaY * distanciaY);

    if (distancia <= tolerancia) {
        return true; 
    }

    return existeSemaforoEnPosicion(nodo->izquierdo, posicion, tolerancia) ||
           existeSemaforoEnPosicion(nodo->derecho, posicion, tolerancia);
}
