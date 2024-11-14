#include <SFML/Graphics.hpp>
#include <iostream>
#include "Carro.h"
#include "Grafo.h"
#include "Interfaz.h"

void dibujarTodo(sf::RenderWindow& window, Grafo& grafo, Interfaz& interfaz, const std::vector<Carro*>& vehiculos, bool mostrarEtiquetas) {
    window.clear(sf::Color(255, 255, 255)); 
    interfaz.crearPanelSuperior(window);
    interfaz.crearPanelDerecho(window);
    grafo.dibujar(window, mostrarEtiquetas);
    
    for (const auto& carro : vehiculos) {
        carro->dibujar(window);
    }

    window.display();
}

void moverCarros(std::vector<Carro*>& vehiculos, float deltaTime) {
    for (auto& carro : vehiculos) {
        carro->mover(deltaTime);
    }
}

int main() {
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Simulador de Trafico");
    Grafo grafo; 

    std::vector<Carro*> vehiculos; 

    sf::Font font;
    if (!font.loadFromFile("../Resources/Roboto-BoldCondensed.ttf")) {
    }

    Interfaz interfaz(font, grafo);
    sf::Clock clock;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            interfaz.manejarEventos(event, window);
        }

        float deltaTime = clock.restart().asSeconds(); 
        grafo.actualizarSemaforos(deltaTime);
        moverCarros(interfaz.obtenerVehiculos(), deltaTime);
        dibujarTodo(window, grafo, interfaz, interfaz.obtenerVehiculos(), interfaz.isMostrarEtiquetas());
    }

    for (auto& carro : interfaz.obtenerVehiculos()) {
        delete carro;
    }

    return 0;
}