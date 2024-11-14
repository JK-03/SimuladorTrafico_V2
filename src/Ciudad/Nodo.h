#ifndef NODO_H
#define NODO_H

#include <SFML/Graphics.hpp>
#include "Semaforo.h"

class Nodo {
public:
    Nodo();
    Nodo(const sf::Vector2f& posicion, float tiempoVerde, float tiempoRojo, float radio = 15.0f);

    const sf::Vector2f& obtenerPosicion() const;
    void setPosicion(const sf::Vector2f& posicion);

    float obtenerRadio() const;  // Nuevo: Obtener el radio
    void setRadio(float nuevoRadio);  // Nuevo: Modificar el radio

    Semaforo& obtenerSemaforo();
    const Semaforo& obtenerSemaforo() const;

    sf::Vector2f posicion;  // Expuesto para acceso directo si es necesario

private:
    float radio;  // Nuevo: Radio del nodo
    Semaforo semaforo;
};

#endif // NODO_H
