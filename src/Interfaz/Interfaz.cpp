#include "Interfaz.h"
#include "Carro.h"
#include "Ruta.h"
#include "Vehiculo.h"
#include <iostream>
#include <cmath>
#include <ctime>
#include <iomanip>
#include <utility>
#include <set>
#include <algorithm>
#include <random>
#include <sstream>

Interfaz::Interfaz(const sf::Font& fuente, Grafo& grafo)
    : font(fuente), botonManager(fuente), grafo(grafo), espaciado(200.0f), climaActual(SOLEADO), temperatura(25.0f), velocidadClima(1.0f) {

    botonManager.agregarBoton("Calles++", sf::Vector2f(1285, 210), [this]() {
            sf::FloatRect areaValida(50, 50, 1100, 700);
            agregarNodoActivo = true;
            sf::Vector2f posicionInicial(100, 100);
            this->grafo.agregarNodosSecuenciales(espaciado, areaValida, posicionInicial);
        });

    botonManager.agregarBoton("Semaforos++", sf::Vector2f(1285, 560), [this, &grafo]() {
        Nodo* nodoRelacionado = grafo.obtenerNodoAlAzar();
        sf::Vector2f posicionNodo = nodoRelacionado->obtenerPosicion();
        std::vector<Nodo*> conexiones = grafo.obtenerConexionesDeNodo(nodoRelacionado);

        if (!conexiones.empty()) {
            static std::set<std::pair<Nodo*, Nodo*>> conexionesUsadas;
            Nodo* nodoConectado = nullptr;
            
            std::random_device rd;
            std::mt19937 g(rd());
            std::shuffle(conexiones.begin(), conexiones.end(), g);

            for (Nodo* nodoCandidato : conexiones) {
                if (conexionesUsadas.find({nodoRelacionado, nodoCandidato}) == conexionesUsadas.end() &&
                    conexionesUsadas.find({nodoCandidato, nodoRelacionado}) == conexionesUsadas.end()) {

                    nodoConectado = nodoCandidato;
                    break;
                }
            }

            if (nodoConectado != nullptr) {
                conexionesUsadas.insert({nodoRelacionado, nodoConectado});
                conexionesUsadas.insert({nodoConectado, nodoRelacionado});

                sf::Vector2f posicionConectada = nodoConectado->obtenerPosicion();
                float direccionX = posicionConectada.x - posicionNodo.x;
                float direccionY = posicionConectada.y - posicionNodo.y;

                float longitud = std::sqrt(direccionX * direccionX + direccionY * direccionY);
                direccionX /= longitud; 
                direccionY /= longitud; 

                float distancia = 25.0f;
                float semaforoX = posicionNodo.x + direccionX * distancia;
                float semaforoY = posicionNodo.y + direccionY * distancia;

                Semaforo* nuevoSemaforo = new Semaforo(30.f, 20.f, 20.f, 20.f, sf::Vector2f(semaforoX, semaforoY), 30.0f);
                nodoRelacionado->asignarSemaforo(nuevoSemaforo);
                arbolSemaforos.insertar(nuevoSemaforo, nodoRelacionado, nodoConectado);
            }
        }
    });

    botonManager.agregarBoton("Carros++", sf::Vector2f(1285, 270), [this, &grafo]() {
        static int index = 0;

        std::string nodoInicio = grafo.obtenerNodoAleatorio();
        sf::Vector2f posicionNodo = grafo.obtenerPosicionNodo(nodoInicio);

        bool posicionValida = true;
        for (auto& carro : vehiculos) {
            if (std::sqrt(std::pow(carro->obtenerPosicion().x - posicionNodo.x, 2) + 
                        std::pow(carro->obtenerPosicion().y - posicionNodo.y, 2)) < 50) {
                posicionValida = false;
                break;
            }
        }

        if (!posicionValida) {
            nodoInicio = grafo.obtenerNodoAleatorio();
            posicionNodo = grafo.obtenerPosicionNodo(nodoInicio);
        }

        Carro carro("Carro_" + std::to_string(index), posicionNodo, 50.0f, grafo, "../Resources/Carro.png", {}, grafo.getNodosSemaforos());
        std::vector<sf::Vector2f> rutaCiclica = carro.generarRutaCiclica(grafo, nodoInicio, 20);

        for (size_t i = 0; i < rutaCiclica.size() - 1; ++i) {
            sf::Vector2f& nodoActual = rutaCiclica[i];
            sf::Vector2f& nodoSiguiente = rutaCiclica[i + 1];

            if (std::abs(nodoSiguiente.x - nodoActual.x) < std::numeric_limits<float>::epsilon()) {
                if (nodoSiguiente.y > nodoActual.y) {
                    nodoActual.x -= 45.0f;
                    nodoSiguiente.x -= 45.0f;
                } else {
                    nodoActual.x += 5.0f;
                    nodoSiguiente.x += 5.0f;
                }
            } else if (std::abs(nodoSiguiente.y - nodoActual.y) < std::numeric_limits<float>::epsilon()) {
                if (nodoSiguiente.x > nodoActual.x) {
                    nodoActual.y += 5.0f;
                    nodoSiguiente.y += 5.0f;
                } else {
                    nodoActual.y -= 30.0f;
                    nodoSiguiente.y -= 30.0f;
                }
            }
        }

        Carro* nuevoCarro = new Carro(
            "Carro_" + std::to_string(index),
            posicionNodo,
            5.0f,
            grafo,
            "../Resources/Carro.png",
            rutaCiclica,
            grafo.getNodosSemaforos()
        );

        vehiculos.push_back(nuevoCarro);
        index++;
    });

    botonManager.agregarBoton("Toggle Etiquetas", sf::Vector2f(1285, 440), [this]() {
        toggleMostrarEtiquetas(); 
    });

    botonManager.agregarBoton("Clima", sf::Vector2f(1285, 380), [this]() {
        cambiarClima();  
    });

    botonManager.agregarBoton("E. Colisiones", sf::Vector2f(1285, 500), [this]() {
        for (auto it = vehiculos.begin(); it != vehiculos.end(); ) {
            if ((*it)->colisionado) {
                delete *it; 
                it = vehiculos.erase(it); 
            } else {
                ++it; 
            }
        }
    });

}

void Interfaz::cambiarClima() {
    int climaRandom = rand() % 3;
    switch (climaRandom) {
        case 0:
            climaActual = SOLEADO;
            temperatura = 25.0f;
            velocidadClima = 10.0f;
            break;
        case 1:
            climaActual = LLUVIA;
            temperatura = 15.0f;
            velocidadClima = 5.7f;
            break;
        case 2:
            climaActual = NIEVE;
            temperatura = -5.0f;
            velocidadClima = 20.f;
            break;
    }
    actualizarVelocidadesDeVehiculos();
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
    std::ostringstream climaTexto; 
    climaTexto << "Clima: " << obtenerNombreClima(climaActual) 
               << ", " << std::fixed << std::setprecision(1) << temperatura << "°C";
    textoClima.setString(climaTexto.str());
    textoClima.setCharacterSize(25);
    textoClima.setFillColor(sf::Color::Black);
    textoClima.setPosition(20.0f, 10.0f);
    window.draw(textoClima);

    dibujarMensajeLimite(window);
}


std::string Interfaz::obtenerNombreClima(Clima clima) {
    switch (clima) {
        case SOLEADO: return "Soleado";
        case LLUVIA: return "Lluvia";
        case NIEVE: return "Nieve";
        default: return "Desconocido";
    }
}

void Interfaz::actualizarVelocidadesDeVehiculos() {
    for (auto* carro : vehiculos) {
        carro->actualizarVelocidad(velocidadClima);
    }
}

void Interfaz::crearPanelDerecho(sf::RenderWindow& window) {
    const float panelAncho = 200;
    const float panelSuperiorAltura = 50;
    const float anchoLinea = 150.0f;

    sf::RectangleShape panelDerecho(sf::Vector2f(panelAncho, window.getSize().y - panelSuperiorAltura));
    panelDerecho.setFillColor(sf::Color(255, 202, 212));
    panelDerecho.setOutlineThickness(2.0f);
    panelDerecho.setOutlineColor(sf::Color::White);
    panelDerecho.setPosition(window.getSize().x - panelAncho, panelSuperiorAltura);
    window.draw(panelDerecho);

    sf::RectangleShape lineaDivisoria(sf::Vector2f(anchoLinea, 2.0f)); 
    lineaDivisoria.setFillColor(sf::Color::White);
    float posicionX = window.getSize().x - panelAncho + (panelAncho - anchoLinea) / 2;
    lineaDivisoria.setPosition(posicionX, panelSuperiorAltura + 130);
    window.draw(lineaDivisoria);

    sf::RectangleShape lineaDivisoria2(sf::Vector2f(anchoLinea, 2.0f)); 
    lineaDivisoria2.setFillColor(sf::Color::White);
    lineaDivisoria2.setPosition(posicionX, panelSuperiorAltura + 300);
    window.draw(lineaDivisoria2);

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

void Interfaz::dibujarSemaforos(sf::RenderWindow& window) {
    arbolSemaforos.dibujarSemaforos(window); 
}

void Interfaz::actualizarSemaforos(float deltaTime) {
    arbolSemaforos.actualizarSemaforos(deltaTime);
}