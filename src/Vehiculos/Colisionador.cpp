#include "Colisionador.h"    
#include <iostream>  

Colisionador::Colisionador(const std::string& rutaImagen, const sf::Vector2f& posicionFija) 
    : posicion(posicionFija) {

    if (!texture.loadFromFile(rutaImagen)) {
        std::cerr << "Error cargando la imagen de colisión" << std::endl;
    }
    sprite.setTexture(texture);
    sprite.setPosition(posicion);
}

void Colisionador::mostrarColision(sf::RenderWindow& window, bool hayColision) {
    if (hayColision) {
        sprite.setScale(0.1f, 0.1f);
        sprite.setPosition(0.f, window.getSize().y - sprite.getGlobalBounds().height);
        window.draw(sprite); 
    }
}
