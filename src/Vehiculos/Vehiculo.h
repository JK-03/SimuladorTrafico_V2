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

    void establecerDireccionMovimiento(int direccion);
    int obtenerCarril() const;

    int obtenerDireccionMovimiento() const;

protected:
    std::string nombre;
    sf::Vector2f posicion;
    float velocidad;

    int direccionMovimiento;
    int carril;

    sf::Sprite sprite;
    sf::Texture textura;

    void actualizarCarril();
};

#endif // VEHICULO_H