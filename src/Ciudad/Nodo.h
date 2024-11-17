#ifndef NODO_H
#define NODO_H

#include <SFML/Graphics.hpp>
#include "Semaforo.h"

class Nodo {
public:
    Nodo();
    Nodo(float posX, float posY, float radio, float tiempoVerde, float tiempoRojo, float tiempoAmarillo, int fila, int columna);

    const sf::Vector2f& obtenerPosicion() const;
    void setPosicion(const sf::Vector2f& nuevaPosicion);

    float obtenerRadio() const;
    void setRadio(float nuevoRadio);

    Semaforo& obtenerSemaforo();
    const Semaforo& obtenerSemaforo() const;

    int obtenerFila() const;
    int obtenerColumna() const;

    void dibujar(sf::RenderWindow& ventana) const;

private:
    float radio;
    Semaforo semaforo;
    int fila;
    int columna;
    sf::Vector2f posicion;
    mutable sf::Clock reloj; 
};

#endif // NODO_H