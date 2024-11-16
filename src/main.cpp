#include <SFML/Graphics.hpp>
#include <iostream>
#include "Vehiculos/Carro.h"
#include "Grafo.h"
#include "Interfaz.h"

void dibujarTodo(sf::RenderWindow& window, Grafo& grafo, Interfaz& interfaz, const std::vector<Carro*>& vehiculos, bool mostrarEtiquetas) {
    window.clear(sf::Color(255, 229, 217));  

    sf::RectangleShape fondoGrafo(sf::Vector2f(window.getSize().x, window.getSize().y));
    fondoGrafo.setFillColor(sf::Color(255, 229, 217));
    window.draw(fondoGrafo);

    interfaz.crearPanelDerecho(window);
    interfaz.crearPanelSuperior(window);

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

    std::vector<Carro*> vehiculos; 

    sf::Font font;
    if (!font.loadFromFile("../Resources/Roboto-BoldCondensed.ttf")) {
    }

    Grafo grafo;
    Interfaz interfaz(font, grafo); 

    grafo.setInterfaz(&interfaz); 
    
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