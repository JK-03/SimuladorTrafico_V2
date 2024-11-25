#ifndef COLISIONADOR_H
#define COLISIONADOR_H

#include <SFML/Graphics.hpp>
#include <string>

class Colisionador {
public:
    Colisionador(const std::string& rutaImagen = "../Resources/TrafficSign.png", const sf::Vector2f& posicionFija = sf::Vector2f(300.f, 200.f));
    void mostrarColision(sf::RenderWindow& window, bool hayColision);

private:
    sf::Texture texture; 
    sf::Sprite sprite; 
    sf::Vector2f posicion;
};

#endif // COLISIONADOR_H