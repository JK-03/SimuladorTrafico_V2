#ifndef INTERFAZ_H
#define INTERFAZ_H

#include <SFML/Graphics.hpp>
#include "BotonManager.h"
#include <memory>
#include "Grafo.h"

class Carro;  // Declaración anticipada de Carro

class Grafo;

class Interfaz {
public:
    Interfaz(const sf::Font& font, Grafo& grafo);

    void crearPanelSuperior(sf::RenderWindow& window);
    void crearPanelDerecho(sf::RenderWindow& window);
    void manejarEventos(const sf::Event& event, sf::RenderWindow& window);
    void setMostrarMensajeLimite(bool estatus);
    void dibujarMensajeLimite(sf::RenderWindow& window);
    void actualizarVelocidad(float nuevaVelocidad); 
    void cambiarClima();

    bool isMostrarEtiquetas() const;
    void mostrarMensajeTemporal();
    bool getMostrarMensajeLimite() const;

    void toggleMostrarEtiquetas();
    std::vector<Carro*>& obtenerVehiculos(); 

    bool agregarNodoActivo = false; 
    bool mostrarMensajeLimite = false;
    
    ~Interfaz();

private:
    sf::Font font;

    sf::Clock relojMensaje;

    BotonManager botonManager;
    bool mostrarEtiquetas = true;
    Grafo& grafo;
    float espaciado;

    std::vector<Carro*> vehiculos; 

    //Limite de Nodos - Text
    sf::Clock mensajeReloj;
    float tiempoMensajeVisible = 10.0f;
    bool mostrarMensaje = true; 

    enum Clima { SOLEADO, LLUVIA, NIEVE };
    Clima climaActual;
    float temperatura;
    float velocidadClima;

    std::string obtenerNombreClima(Clima clima);
    void actualizarVelocidadesDeVehiculos();
};

#endif // INTERFAZ_H