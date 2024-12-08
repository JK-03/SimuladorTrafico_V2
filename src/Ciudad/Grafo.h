#ifndef GRAFO_H
#define GRAFO_H

#include <map>
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>
#include "Semaforo.h"
#include "Nodo.h"
#include "Interfaz/Interfaz.h"
#include <unordered_map>

class Interfaz;

class Grafo {
public:
    Grafo(); 

    // Métodos de manipulación de nodos
    void agregarNodo(const std::string& nombre, const sf::Vector2f& posicion, float radio);
    void agregarNodosSecuenciales(float espaciado, const sf::FloatRect& areaValida, const sf::Vector2f& primeraPosicion);

    // Métodos de manipulación de aristas
    void agregarArista(const std::string& nodoA, const std::string& nodoB);
    void agregarAristasSecuenciales();

    // Métodos de actualización
    void actualizarSemaforos(float deltaTiempo);

    // Métodos de consulta de nodos y aristas
    bool estaSemaforoVerde(const std::string& nodo) const; 
    bool estaAristaLibre(const std::string& desde, const std::string& hacia);
    int getNumeroDeNodos() const;
    float getPeso(const std::string& desde, const std::string& hacia) const;
    sf::Vector2f obtenerPosicionNodo(const std::string& nombreNodo) const;
    std::string obtenerNodoAleatorio() const;
    std::string obtenerNodoDesdePosicion(const sf::Vector2f& posicion, float margen = 5.0f) const;
    std::vector<std::string> obtenerSemaforosConectados(const std::string& nombreNodo);
    std::vector<std::string> obtenerNodosConectados(const std::string& nombreNodo) const;
    std::vector<Nodo*> obtenerConexionesDeNodo(const Nodo* nodo);
    std::vector<std::pair<const std::string, Nodo>> getNodos() const;
    std::unordered_map<std::string, Nodo> obtenerNodos() const;
    std::map<std::string, Nodo> getNodosSemaforos() const;
    Nodo* obtenerNodoAlAzar();
    Nodo* obtenerNodoPorNombre(const std::string& nombreNodo);
    size_t obtenerCantidadNodos() const;

    // Métodos de visualización
    void dibujar(sf::RenderWindow& window, bool mostrarEtiquetas);

    // Métodos de configuración
    void setInterfaz(Interfaz* interfaz);

private:
    // Miembros de datos
    std::map<std::string, Nodo> nodos;
    std::vector<std::pair<std::string, std::string>> aristas;
    sf::Font font; 
    Interfaz* interfaz;
    bool fontLoaded = false;

    // Datos de nodos
    int filaActual = 1;
    int columnaActual = 1;
    float espaciado;
    int filas = 4;
    int columnas = 6;
    int nodoCount = 0;
};

#endif // GRAFO_H