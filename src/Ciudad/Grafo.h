#ifndef GRAFO_H
#define GRAFO_H

#include <map>
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>
#include "Semaforo.h"
#include "Nodo.h"
#include <unordered_map>

class Grafo {
public:
    Grafo();

    void agregarNodo(const std::string& nombre, const sf::Vector2f& posicion, float tiempoVerde, float tiempoRojo, float radio);
    void agregarArista(const std::string& n1, const std::string& n2);
    void agregarNodosAleatorios(int cantidad, float espaciado, const sf::FloatRect& areaValida);
    void actualizarSemaforos(float deltaTiempo);
    void dibujar(sf::RenderWindow& window, bool mostrarEtiquetas);

    bool estaAristaLibre(const std::string& desde, const std::string& hacia);
    bool estaSemaforoVerde(const std::string& nodo) const; 

    int getNumeroDeNodos() const;
    sf::Vector2f obtenerPosicionNodo(const std::string& nombreNodo) const;

    std::string obtenerNodoAleatorio() const;
    std::string obtenerNodoDesdePosicion(const sf::Vector2f& posicion, float margen = 5.0f) const;


    std::vector<std::string> obtenerSemaforosConectados(const std::string& nombreNodo);
    std::vector<std::string> obtenerNodosConectados(const std::string& nombreNodo) const;
    std::vector<std::pair<const std::string, Nodo>> getNodos() const;
    
    std::unordered_map<std::string, Nodo> obtenerNodos() const;
    std::map<std::string, Nodo> getNodosSemaforos() const;

    Semaforo& obtenerSemaforo(const std::string& nombreNodo);

    float getPeso(const std::string& desde, const std::string& hacia) const;

    void depurarNodos() const;

private:
    std::map<std::string, Nodo> nodos;
    std::vector<std::pair<std::string, std::string>> aristas;
    sf::Font font; 
    bool fontLoaded = false;
    int filas;
    int columnas;
    float espaciado;
};

#endif // GRAFO_H