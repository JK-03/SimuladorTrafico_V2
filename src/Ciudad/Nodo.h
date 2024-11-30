#ifndef NODO_H
#define NODO_H

#include <SFML/Graphics.hpp>
#include "Semaforo.h"

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

private:
    Semaforo* semaforo; 

    std::string nombre;
    float radio;
    int fila;
    int columna;
    sf::Vector2f posicion;
    mutable sf::Clock reloj;
    bool esSemaforo; 
};

#endif // NODO_H