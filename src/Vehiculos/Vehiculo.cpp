#include "Vehiculo.h"
#include <iostream>

Vehiculo::Vehiculo(const std::string& nombre, const sf::Vector2f& posicion, float velocidad, const std::string& rutaImagen)
    : nombre(nombre), posicion(posicion), velocidad(velocidad) {
    
    if (!textura.loadFromFile(rutaImagen)) {
    } else {
        sprite.setTexture(textura);
        sprite.setPosition(posicion);
    }
}

void Vehiculo::mover(float deltaTime) {
    posicion += sf::Vector2f(velocidad * deltaTime, 0);
    sprite.setPosition(posicion);
}

void Vehiculo::dibujar(sf::RenderWindow& window) {
    window.draw(sprite);
}

void Vehiculo::establecerPosicion(const sf::Vector2f& nuevaPosicion) {
    posicion = nuevaPosicion;
    sprite.setPosition(nuevaPosicion);
}

sf::Vector2f Vehiculo::obtenerPosicion() const {
    return posicion;
}