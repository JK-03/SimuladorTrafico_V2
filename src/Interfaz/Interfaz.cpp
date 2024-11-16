#include "Interfaz.h"
#include "Carro.h"
#include "Vehiculo.h"
#include "Ruta.h"
#include <iostream>

Interfaz::Interfaz(const sf::Font& fuente, Grafo& grafo)
    : font(fuente), botonManager(fuente), grafo(grafo), espaciado(200.0f) {

    botonManager.agregarBoton("Semaforos++", sf::Vector2f(1285, 130), [this]() {
        sf::FloatRect areaValida(50, 50, 1100, 700);
        agregarNodoActivo = true;
        sf::Vector2f posicionInicial(100, 100);
        this->grafo.agregarNodosSecuenciales(espaciado, areaValida, posicionInicial);
    });

    botonManager.agregarBoton("Carros++", sf::Vector2f(1285, 190), [this, &grafo]() {
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

    botonManager.agregarBoton("Toggle Etiquetas", sf::Vector2f(1285, 310), [this]() {
        toggleMostrarEtiquetas(); 
    });

     botonManager.agregarBoton("Clima", sf::Vector2f(1285, 250), [this]() {
        toggleMostrarEtiquetas(); 
    });
}

void Interfaz::crearPanelSuperior(sf::RenderWindow& window) {
    const float alturaPanel = 50.0f;

    sf::RectangleShape panelSuperior(sf::Vector2f(window.getSize().x, alturaPanel));
    panelSuperior.setFillColor(sf::Color(255, 202, 212));
    panelSuperior.setOutlineThickness(2.0f);
    panelSuperior.setOutlineColor(sf::Color::White);
    panelSuperior.setPosition(0, 0);
    window.draw(panelSuperior);

    sf::Text textoClima;
    textoClima.setFont(font);
    textoClima.setString("Clima: Soleado, 25°C");
    textoClima.setCharacterSize(25);
    textoClima.setFillColor(sf::Color::Black);
    textoClima.setPosition(20.0f, 10.0f);
    window.draw(textoClima);

    dibujarMensajeLimite(window);
}

void Interfaz::crearPanelDerecho(sf::RenderWindow& window) {
    const float panelAncho = 200;
    const float panelSuperiorAltura = 50;

    sf::RectangleShape panelDerecho(sf::Vector2f(panelAncho, window.getSize().y - panelSuperiorAltura));
    panelDerecho.setFillColor(sf::Color(255, 202, 212));
    panelDerecho.setOutlineThickness(2.0f);
    panelDerecho.setOutlineColor(sf::Color::White);
    panelDerecho.setPosition(window.getSize().x - panelAncho, panelSuperiorAltura);
    window.draw(panelDerecho);

    sf::Font fontMenu;
    if (!fontMenu.loadFromFile("../Resources/Lobster-Regular.ttf")) {
        return;
    }

    sf::Text menuTitle;
    menuTitle.setFont(fontMenu);
    menuTitle.setString("MENU");
    menuTitle.setCharacterSize(50);
    menuTitle.setFillColor(sf::Color::White);

    float titleWidth = menuTitle.getGlobalBounds().width;
    menuTitle.setPosition(window.getSize().x - panelAncho + (panelAncho - titleWidth) / 2, panelSuperiorAltura + 10);
    window.draw(menuTitle);

    botonManager.draw(window);
}

void Interfaz::dibujarMensajeLimite(sf::RenderWindow& window) {
    if (mostrarMensajeLimite) {
        sf::Text mensajeLimite("Limite de nodos alcanzado", font, 25);
        mensajeLimite.setFillColor(sf::Color::Black);

        float mensajeX = window.getSize().x - 300.0f;
        float mensajeY = 10.0f; 
        mensajeLimite.setPosition(mensajeX, mensajeY);

        window.draw(mensajeLimite);

        if (mensajeReloj.getElapsedTime().asSeconds() >= tiempoMensajeVisible) {
            mostrarMensajeLimite = false;
        }
    }
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