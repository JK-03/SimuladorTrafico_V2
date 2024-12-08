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
    ~Interfaz();

    // Métodos de configuración
    void actualizarVelocidad(float nuevaVelocidad); 
    void cambiarClima();
    void toggleMostrarEtiquetas();
    void actualizarSemaforos(float deltaTime);

    // Métodos de creación de paneles
    void crearPanelSuperior(sf::RenderWindow& window);
    void crearPanelDerecho(sf::RenderWindow& window);

    // Manejo de eventos
    void manejarEventos(const sf::Event& event, sf::RenderWindow& window);

    // Métodos de visualización
    void dibujarSemaforos(sf::RenderWindow& window);
    void dibujarMensajeLimite(sf::RenderWindow& window);
    void dibujarMensajeGrafoVacio(sf::RenderWindow& window);
    void dibujarMensajeSemaforo(sf::RenderWindow& window);
    void dibujarMensajeCalle(sf::RenderWindow& window);
    void mostrarMensajeTemporal();

    // Métodos de control de mensajes
    void setMostrarMensajeLimite(bool estatus);

    // Métodos de información de estado
    bool isMostrarEtiquetas() const;
    bool getMostrarMensajeLimite() const;
    std::unordered_map<Nodo*, Semaforo*> obtenerMapaSemaforos() const;
    ArbolSemaforos* obtenerArbolSemaforos();
    float obtenerVelocidadClima() const; 
    std::vector<Carro*>& obtenerVehiculos(); 
    std::vector<CarroEspecial*>& obtenerVehiculosEspeciales();

    bool agregarNodoActivo = false; 
    bool mostrarMensajeLimite = false;

private:
    // Miembros de datos
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

    // Mensajes temporales
    sf::Clock mensajeReloj;
    float tiempoMensajeVisible = 8.0f;
    bool mostrarMensaje = true; 
    bool mostrarMensajeGrafoVacio = false;
    bool mostrarMensajeSemaforos = false;
    bool mostrarMensajeCalles = false;

    // Datos de clima
    enum Clima { SOLEADO, LLUVIA, NIEVE };
    Clima climaActual;
    float temperatura;
    float velocidadClima;

    // Métodos privados de ayuda
    std::string obtenerNombreClima(Clima clima);
    void actualizarVelocidadesDeVehiculos();

    std::mutex climaMutex;
};

#endif // INTERFAZ_H
