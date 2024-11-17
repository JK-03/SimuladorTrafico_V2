#include "Nodo.h"

Nodo::Nodo() : posicion(0, 0), radio(15.0f), semaforo(0.0f, 0.0f, 0.0f), fila(0), columna(0) {}

Nodo::Nodo(float posX, float posY, float radio, float tiempoVerde, float tiempoRojo, float tiempoAmarillo, int fila, int columna)
    : posicion(posX, posY), radio(radio), semaforo(tiempoVerde, tiempoRojo, tiempoAmarillo), fila(fila), columna(columna) {}

const sf::Vector2f& Nodo::obtenerPosicion() const {
    return posicion;
}

void Nodo::setPosicion(const sf::Vector2f& nuevaPosicion) {
    posicion = nuevaPosicion;
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

int Nodo::obtenerFila() const {
    return fila;
}

int Nodo::obtenerColumna() const {
    return columna;
}

void Nodo::dibujar(sf::RenderWindow& ventana) const {
    sf::CircleShape circulo(radio);
    circulo.setPosition(posicion.x - radio, posicion.y - radio);

    switch (semaforo.obtenerEstado()) {
        case Semaforo::Verde:
            circulo.setFillColor(sf::Color(0, 255, 0, 100));
            break;
        case Semaforo::Rojo:
            circulo.setFillColor(sf::Color(255, 0, 0, 100));
            break;
        case Semaforo::Amarillo:
            circulo.setFillColor(sf::Color(255, 255, 0, 100));
            break;
        case Semaforo::ParpadeandoAmarillo:
            if (static_cast<int>(reloj.getElapsedTime().asSeconds()) % 2 == 0) {
                circulo.setFillColor(sf::Color(255, 255, 0, 100));
            } else {
                circulo.setFillColor(sf::Color(255, 255, 0, 0));
            }
            break;
        default:
            circulo.setFillColor(sf::Color(255, 255, 255, 100));
            break;
    }

    ventana.draw(circulo);
}