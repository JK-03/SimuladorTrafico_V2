#include "Nodo.h"
#include <cmath>

Nodo::Nodo() : posicion(0, 0), radio(15.0f), fila(0), columna(0), esSemaforo(false) {}

Nodo::Nodo(float posX, float posY, float radio, int fila, int columna, const std::string& nombre)
    : posicion(posX, posY), radio(radio), fila(fila), columna(columna), esSemaforo(false), nombre(nombre) {}

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

int Nodo::obtenerFila() const {
    return fila;
}

int Nodo::obtenerColumna() const {
    return columna;
}

void Nodo::dibujar(sf::RenderWindow& ventana) const {
    sf::CircleShape circulo(radio);
    circulo.setPosition(posicion.x - radio, posicion.y - radio);

    if (esSemaforo) {
        circulo.setFillColor(sf::Color::Red);
    } else {
        circulo.setFillColor(sf::Color::Black);
    }

    ventana.draw(circulo);
}

void Nodo::setEsSemaforo(bool valor) {
    esSemaforo = valor;
}

bool Nodo::getEsSemaforo() const {
    return esSemaforo;
}

float Nodo::obtenerTiempoTranscurrido() const {
    return reloj.getElapsedTime().asSeconds();
}

void Nodo::asignarSemaforo(Semaforo* semaforo) {
    this->semaforo = semaforo;
}

std::string Nodo::obtenerNombre() const {
    return nombre;
}

Semaforo* Nodo::getSemaforo() const {
    return semaforo; 
}

bool Nodo::tieneSemaforoEnConexion(const Nodo* nodoConectado) const {
    auto it = semaforosConexiones.find(const_cast<Nodo*>(nodoConectado));
    return it != semaforosConexiones.end();
}

void Nodo::agregarSemaforoConexion(Nodo* nodoConectado, Semaforo* semaforo) {
    if (semaforosConexiones.find(nodoConectado) == semaforosConexiones.end()) {
        semaforosConexiones[nodoConectado] = semaforo;
    }
}
