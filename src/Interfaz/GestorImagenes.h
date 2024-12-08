#ifndef GESTOR_IMAGENES_H
#define GESTOR_IMAGENES_H

#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <string>

class GestorImagenes {
public:
    GestorImagenes();
    ~GestorImagenes();
    
    bool cargarImagen(const std::string& nombre, const std::string& archivo);
    sf::Texture& obtenerImagen(const std::string& nombre);
    bool tieneImagen(const std::string& nombre) const;
    void dibujarImagen(const std::string& nombre, sf::RenderWindow& ventana, const sf::Vector2f& posicion, float escalaX, float escalaY);

private:
    std::unordered_map<std::string, sf::Texture> imagenes;
};

#endif // GESTOR_IMAGENES_H