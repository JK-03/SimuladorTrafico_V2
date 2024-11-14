#ifndef VEHICULO_H
#define VEHICULO_H

#include <SFML/Graphics.hpp>
#include <string>

class Vehiculo {
public:
    Vehiculo(const std::string& nombre, const sf::Vector2f& posicion, float velocidad, const std::string& rutaImagen);

    virtual void mover(float deltaTime);
    virtual void dibujar(sf::RenderWindow& window);

    void establecerPosicion(const sf::Vector2f& nuevaPosicion);
    sf::Vector2f obtenerPosicion() const;

protected:
    std::string nombre;
    sf::Vector2f posicion;
    float velocidad;

    sf::Sprite sprite;
    sf::Texture textura;
};

#endif // VEHICULO_H