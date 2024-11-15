#include "Interfaz.h"
#include "Carro.h"
#include "Vehiculo.h"
#include "Ruta.h"
#include <iostream>

Interfaz::Interfaz(const sf::Font& fuente, Grafo& grafo)
    : font(fuente), botonManager(fuente), grafo(grafo), espaciado(200.0f) {

    botonManager.agregarBoton("Semaforos++", sf::Vector2f(1282, 130), [this]() {
        sf::FloatRect areaValida(50, 50, 1100, 700);
        agregarNodoActivo = true;
        sf::Vector2f posicionInicial(100, 100);
        this->grafo.agregarNodosSecuenciales(espaciado, areaValida, posicionInicial);
    });

    botonManager.agregarBoton("Carros++", sf::Vector2f(1282, 190), [this, &grafo]() {
        static int index = 0;

        std::string nodoInicio = grafo.obtenerNodoAleatorio();
        std::vector<std::string> nodosDisponibles = grafo.obtenerNodosConectados(nodoInicio);
        sf::Vector2f posicionNodo = grafo.obtenerPosicionNodo(nodoInicio);
        std::vector<sf::Vector2f> rutaCiclica = generarRutaCiclica(grafo, nodoInicio, 20);

        sf::Vector2f nuevaPosicionNodo = posicionNodo;
        nuevaPosicionNodo.x -= 20.0f; 
        nuevaPosicionNodo.y -= 20.0f; 

        Carro* nuevoCarro = new Carro(
            "Carro_" + std::to_string(index),
            nuevaPosicionNodo, 
            5.0f,
            grafo,
            "../Resources/Carro.png",
            rutaCiclica,
            grafo.getNodosSemaforos()
        );

        vehiculos.push_back(nuevoCarro);
        index++;
    });

    botonManager.agregarBoton("Toggle Etiquetas", sf::Vector2f(1282, 250), [this]() {
        toggleMostrarEtiquetas(); 
    });
}

void Interfaz::crearPanelSuperior(sf::RenderWindow& window) {
    sf::RectangleShape panelSuperior(sf::Vector2f(window.getSize().x, 50));
    panelSuperior.setFillColor(sf::Color(200, 200, 200));
    panelSuperior.setPosition(0, 0);
    window.draw(panelSuperior);

    sf::Text weatherText;
    weatherText.setFont(font);
    weatherText.setString("Weather: Sunny, 25°C");
    weatherText.setCharacterSize(20);
    weatherText.setFillColor(sf::Color::Black);
    weatherText.setPosition(10, 10);
    window.draw(weatherText);
}

void Interfaz::crearPanelDerecho(sf::RenderWindow& window) {
    const float panelAncho = 200;
    float panelSuperiorAltura = 50;
    sf::RectangleShape panelDerecho(sf::Vector2f(panelAncho, window.getSize().y - panelSuperiorAltura));
    panelDerecho.setFillColor(sf::Color(150, 150, 150));
    panelDerecho.setPosition(window.getSize().x - panelAncho, panelSuperiorAltura);
    window.draw(panelDerecho);

    sf::Text menuTitle;
    menuTitle.setFont(font);
    menuTitle.setString("MENU");
    menuTitle.setCharacterSize(24);
    menuTitle.setFillColor(sf::Color::Black);

    if (mostrarMensajeLimite) {
        sf::Text mensajeLimite("Limite de nodos alcanzado", font, 25);
        mensajeLimite.setFillColor(sf::Color::Red);
        mensajeLimite.setPosition(window.getSize().x - panelAncho - 100, panelSuperiorAltura - 40);
        window.draw(mensajeLimite);

        if (mensajeReloj.getElapsedTime().asSeconds() >= tiempoMensajeVisible) {
            mostrarMensajeLimite = false;
        }
    }

    float titleWidth = menuTitle.getGlobalBounds().width;
    menuTitle.setPosition(window.getSize().x - panelAncho + (panelAncho - titleWidth) / 2, panelSuperiorAltura + 10);
    window.draw(menuTitle);

    botonManager.draw(window);
}

void Interfaz::manejarEventos(const sf::Event& event, sf::RenderWindow& window) {
    botonManager.manejarEventos(event, window);
}

bool Interfaz::isMostrarEtiquetas() const {
    return mostrarEtiquetas;
}

void Interfaz::toggleMostrarEtiquetas() {
    mostrarEtiquetas = !mostrarEtiquetas; 
}

std::vector<Carro*>& Interfaz::obtenerVehiculos() {
    return vehiculos; 
}

void Interfaz::setMostrarMensajeLimite(bool estatus) {
    mostrarMensajeLimite = estatus;
    if (mostrarMensajeLimite) {
        mensajeReloj.restart();
    }
}

bool Interfaz::getMostrarMensajeLimite() const {
    return mostrarMensajeLimite;
}

Interfaz::~Interfaz() {
    vehiculos.clear();
}