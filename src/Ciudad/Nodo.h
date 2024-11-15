#ifndef NODO_H
#define NODO_H

#include <SFML/Graphics.hpp>
#include "Semaforo.h"

class Nodo {
public:
    Nodo();
    Nodo(const sf::Vector2f& posicion, float tiempoVerde, float tiempoRojo, int fila, int columna, float radio = 15.0f);

    const sf::Vector2f& obtenerPosicion() const;
    void setPosicion(const sf::Vector2f& posicion);

    float obtenerRadio() const;
    void setRadio(float nuevoRadio); 

    Semaforo& obtenerSemaforo();
    const Semaforo& obtenerSemaforo() const;

    int obtenerFila() const;
    int obtenerColumna() const;

    sf::Vector2f posicion;

private:
    float radio;
    Semaforo semaforo;
    int fila;
    int columna;
};

#endif // NODO_H