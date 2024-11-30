#include "Vehiculo.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

Vehiculo::Vehiculo(const std::string& nombre, const sf::Vector2f& posicion, float velocidad, const std::string& rutaImagen)
    : nombre(nombre), posicion(posicion), velocidad(velocidad) {
    static bool semillaInicializada = false;
    if (!semillaInicializada) {
        std::srand(static_cast<unsigned>(std::time(nullptr)));
        semillaInicializada = true;
    }

    direccionMovimiento = (std::rand() % 2 == 0) ? 1 : -1;
    actualizarCarril();

    if (!textura.loadFromFile(rutaImagen)) {
    } else {
        sprite.setTexture(textura);
        sprite.setPosition(posicion);
    }
}

void Vehiculo::mover(float deltaTime) {
    posicion += sf::Vector2f(direccionMovimiento * velocidad * deltaTime, 0);
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

void Vehiculo::establecerDireccionMovimiento(int direccion) {
    direccionMovimiento = direccion;
    actualizarCarril();
}

int Vehiculo::obtenerCarril() const {
    return carril;
}

void Vehiculo::actualizarCarril() {
    if (direccionMovimiento == 1) {
        carril = 2;
    } else if (direccionMovimiento == -1) {
        carril = 1;
    }
}

int Vehiculo::obtenerDireccionMovimiento() const {
    return direccionMovimiento;
}
