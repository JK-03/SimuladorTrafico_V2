#ifndef INTERFAZ_H
#define INTERFAZ_H

#include <SFML/Graphics.hpp>
#include "BotonManager.h"
#include <memory>
#include "Grafo.h"
#include "Trafico/ArbolSemaforos.h"
#include "Trafico/NodoArbol.h"
#include <mutex>

class NodoArbol;
class Carro; 
class CarroEspecial;
class Grafo;

class Interfaz {
public:
    Interfaz(const sf::Font& font, Grafo& grafo);

    void crearPanelSuperior(sf::RenderWindow& window);
    void crearPanelDerecho(sf::RenderWindow& window);
    void manejarEventos(const sf::Event& event, sf::RenderWindow& window);
    void setMostrarMensajeLimite(bool estatus);
    void dibujarMensajeLimite(sf::RenderWindow& window);
    void dibujarMensajeGrafoVacio(sf::RenderWindow& window);
    void dibujarMensajeSemaforo(sf::RenderWindow& window);
    void dibujarMensajeCalle(sf::RenderWindow& window);
    void actualizarVelocidad(float nuevaVelocidad); 
    void cambiarClima();
    void dibujarSemaforos(sf::RenderWindow& window);
    void actualizarSemaforos(float deltaTime);
    void mostrarMensajeTemporal();

    bool isMostrarEtiquetas() const;
    bool getMostrarMensajeLimite() const;

    void toggleMostrarEtiquetas();
    std::vector<Carro*>& obtenerVehiculos(); 
    std::vector<CarroEspecial*>& obtenerVehiculosEspeciales();

    bool agregarNodoActivo = false; 
    bool mostrarMensajeLimite = false;
    
    ~Interfaz();

    std::unordered_map<Nodo*, Semaforo*> obtenerMapaSemaforos() const;
    ArbolSemaforos* obtenerArbolSemaforos();

    float obtenerVelocidadClima() const; 

private:
    ArbolSemaforos* arbolSemaforos;

    std::unordered_map<Nodo*, Semaforo*> mapaSemaforos;

    sf::Font font;
    sf::Clock relojMensaje;

    BotonManager botonManager;
    bool mostrarEtiquetas = true;
    Grafo& grafo;
    float espaciado;

    std::vector<Carro*> vehiculos; 
    std::vector<CarroEspecial*> vehiculosEspecial;

    //Limite de Nodos - Text
    sf::Clock mensajeReloj;
    float tiempoMensajeVisible = 8.0f;
    bool mostrarMensaje = true; 
    bool mostrarMensajeGrafoVacio = false;
    bool mostrarMensajeSemaforos = false;
    bool mostrarMensajeCalles = false;

    enum Clima { SOLEADO, LLUVIA, NIEVE };
    Clima climaActual;
    float temperatura;
    float velocidadClima;

    std::string obtenerNombreClima(Clima clima);
    void actualizarVelocidadesDeVehiculos();

    std::mutex climaMutex;
};

#endif // INTERFAZ_H