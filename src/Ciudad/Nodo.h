#ifndef NODO_H
#define NODO_H

#include <SFML/Graphics.hpp>
#include "Semaforo.h"
#include <map>
#include <unordered_map>

class Nodo {
public:
    Nodo();
    Nodo(float posX, float posY, float radio, int fila, int columna, const std::string& nombre);

    const sf::Vector2f& obtenerPosicion() const;
    void setPosicion(const sf::Vector2f& nuevaPosicion);

    float obtenerRadio() const;
    void setRadio(float nuevoRadio);

    int obtenerFila() const;
    int obtenerColumna() const;

    void dibujar(sf::RenderWindow& ventana) const;

    void setEsSemaforo(bool valor);
    bool getEsSemaforo() const;

    float obtenerTiempoTranscurrido() const;
    void asignarSemaforo(Semaforo* semaforo);

    std::string obtenerNombre() const;

    Semaforo* getSemaforo() const;

    bool tieneSemaforoEnConexion(const Nodo* nodoConectado) const;
    void agregarSemaforoConexion(Nodo* nodoConectado, Semaforo* semaforo);

    sf::CircleShape& getCirculo();
    const sf::CircleShape& getCirculo() const;

    std::unordered_map<Nodo*, std::pair<Semaforo*, bool>> semaforosPorConexion;

    Semaforo* obtenerSemaforo() const;

    void setColor(sf::Color color);
    void cerrarCalle();   
    bool esCerrada() const;

private:
    Semaforo* semaforo;
    std::map<Nodo*, Semaforo*> semaforosConexiones; 

    std::string nombre;
    sf::Color color;
    mutable sf::CircleShape circulo;
    float radio;
    int fila;
    int columna;
    sf::Vector2f posicion;
    mutable sf::Clock reloj;
    bool esSemaforo;
    bool estaCerrada = false;
};

#endif // NODO_H