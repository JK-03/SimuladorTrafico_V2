#ifndef CARRO_H
#define CARRO_H

#include "Vehiculo.h"
#include "Grafo.h"
#include <vector>
#include "Interfaz.h"
#include "Semaforo.h"

class Carro : public Vehiculo {
public:
    Carro(const std::string& nombre, const sf::Vector2f& posicion, float velocidad, Grafo& grafo, const std::string& rutaImagen, const std::vector<sf::Vector2f>& ruta, const std::map<std::string, Nodo>& nodosSemaforos);

    sf::Vector2f obtenerDireccionDesdeArista(const Grafo& grafo, const std::string& nodoDesde, const std::string& nodoHacia);

    void dibujar(sf::RenderWindow& window);
    void calcularRuta(const std::string& nodoInicio, const std::string& nodoDestino);
    void mover(float deltaTime); 
    
private:
    Grafo& grafo; 
    std::vector<sf::Vector2f> ruta;
    std::map<std::string, Nodo> nodosSemaforos;
};

#endif // CARRO_H