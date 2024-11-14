#ifndef INTERFAZ_H
#define INTERFAZ_H

#include <SFML/Graphics.hpp>
#include "BotonManager.h"
#include <memory>
#include "Grafo.h"
#include "Carro.h"
#include <vector>

class Interfaz {
public:
    Interfaz(const sf::Font& font, Grafo& grafo);

    void crearPanelSuperior(sf::RenderWindow& window);
    void crearPanelDerecho(sf::RenderWindow& window);
    void manejarEventos(const sf::Event& event, sf::RenderWindow& window);
    bool isMostrarEtiquetas() const;
    void toggleMostrarEtiquetas();
    std::vector<Carro*>& obtenerVehiculos(); 
    bool agregarNodoActivo = false; 

    ~Interfaz();

private:
    sf::Font font;
    BotonManager botonManager;
    bool mostrarEtiquetas = true;
    Grafo& grafo;
    float espaciado;

    std::vector<Carro*> vehiculos; 
};

#endif // INTERFAZ_H