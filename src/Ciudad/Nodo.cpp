#include "Nodo.h"

Nodo::Nodo() : posicion(0, 0), radio(15.0f), semaforo(0.0f, 0.0f) {}

Nodo::Nodo(const sf::Vector2f& pos, float tiempoVerde, float tiempoRojo, float radio)
    : posicion(pos), radio(radio), semaforo(tiempoVerde, tiempoRojo) {}

const sf::Vector2f& Nodo::obtenerPosicion() const {
    return posicion;
}

void Nodo::setPosicion(const sf::Vector2f& pos) {
    posicion = pos;
}

float Nodo::obtenerRadio() const {
    return radio;
}

void Nodo::setRadio(float nuevoRadio) {
    radio = nuevoRadio;
}

Semaforo& Nodo::obtenerSemaforo() {
    return semaforo;
}

const Semaforo& Nodo::obtenerSemaforo() const {
    return semaforo;
}
