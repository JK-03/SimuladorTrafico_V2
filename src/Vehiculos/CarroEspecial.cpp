#include "CarroEspecial.h"
#include <iostream>

CarroEspecial::CarroEspecial(const std::string& nombre, const sf::Vector2f& posicion, float velocidad, 
                             Grafo& grafo, const std::string& rutaImagen, 
                             const std::vector<sf::Vector2f>& ruta, 
                             float tamanoCuadro)
    : Carro(nombre, posicion, velocidad, grafo, rutaImagen, ruta, {}, tamanoCuadro), 
      prioridad(true) 
{
}

void CarroEspecial::mover(float deltaTime) {
    Carro::mover(deltaTime); 
}

void CarroEspecial::verificarSemaforos(ArbolSemaforos* arbolSemaforos) {
}

bool CarroEspecial::tienePrioridad() const {
    return prioridad;
}

void CarroEspecial::definirRuta(const std::vector<sf::Vector2f>& nuevaRuta) {
    this->ruta = nuevaRuta; 
}

void CarroEspecial::dibujar(sf::RenderWindow& window) {
    window.draw(sprite);
}