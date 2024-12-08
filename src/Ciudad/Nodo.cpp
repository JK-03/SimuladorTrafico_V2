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
    sf::CircleShape nodoFondo(radio + 5.f);
    nodoFondo.setPosition(posicion.x - nodoFondo.getRadius(), posicion.y - nodoFondo.getRadius());
    if (estaCerrada) {
        nodoFondo.setFillColor(sf::Color(255, 140, 0, 100));
    } else {
        nodoFondo.setFillColor(sf::Color(255, 229, 217));
    }

    ventana.draw(nodoFondo);

    sf::CircleShape circulo(radio);
    circulo.setPosition(posicion.x - radio, posicion.y - radio);
    if (estaCerrada) {
        circulo.setFillColor(sf::Color(255, 140, 0, 255));
    } else {
        circulo.setFillColor(sf::Color(0, 0, 0, 255));
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

Semaforo* Nodo::obtenerSemaforo() const {
    return semaforo;
}

void Nodo::setColor(sf::Color color) {
    circulo.setRadius(20.0f);
    circulo.setFillColor(color);
    circulo.setOutlineColor(sf::Color(0, 0, 0, 255));
    circulo.setOutlineThickness(2);
}

sf::CircleShape& Nodo::getCirculo() {
    return circulo;
}

const sf::CircleShape& Nodo::getCirculo() const {
    return circulo;
}

bool Nodo::esCerrada() const {
    return estaCerrada;
}

void Nodo::agregarSemaforoConexion(Nodo* nodoConectado, Semaforo* semaforo) {
    semaforosPorConexion[nodoConectado] = {semaforo, true};
}

bool Nodo::tieneSemaforoEnConexion(const Nodo* nodoConectado) const {
    auto it = semaforosPorConexion.find(const_cast<Nodo*>(nodoConectado));
    return it != semaforosPorConexion.end() && it->second.first != nullptr;
}

void Nodo::cerrarCalle() {
    estaCerrada = true;
}

void Nodo::abrirCalle() {
    estaCerrada = false; 
}

sf::Vector2f Nodo::getPosicion() const {
    return posicion;
}