#include "GestorImagenes.h"
#include <iostream>

GestorImagenes::GestorImagenes() {
    cargarImagen("Soleado", "../Resources/Soleado.png");
    cargarImagen("Lluvia", "../Resources/Lluvia.png");
    cargarImagen("Nieve", "../Resources/Nieve.png");
}

GestorImagenes::~GestorImagenes() {
}

bool GestorImagenes::cargarImagen(const std::string& nombre, const std::string& archivo) {
    sf::Texture texture;
    if (texture.loadFromFile(archivo)) {
        imagenes[nombre] = texture;
        return true;
    }
    std::cerr << "Error al cargar la imagen: " << archivo << std::endl;
    return false;
}

sf::Texture& GestorImagenes::obtenerImagen(const std::string& nombre) {
    return imagenes.at(nombre); 
}

bool GestorImagenes::tieneImagen(const std::string& nombre) const {
    return imagenes.find(nombre) != imagenes.end();
}

void GestorImagenes::dibujarImagen(const std::string& nombre, sf::RenderWindow& ventana, const sf::Vector2f& posicion, float escalaX, float escalaY) {
    if (tieneImagen(nombre)) {
        sf::Sprite sprite(imagenes.at(nombre));
        sprite.setPosition(posicion);
        sprite.setScale(escalaX, escalaY); 

        ventana.draw(sprite);  
    } else {
        std::cerr << "Imagen no encontrada: " << nombre << std::endl;
    }
}