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

    // Métodos para obtener y establecer propiedades básicas
    const sf::Vector2f& obtenerPosicion() const;
    void setPosicion(const sf::Vector2f& nuevaPosicion);

    float obtenerRadio() const;
    void setRadio(float nuevoRadio);

    int obtenerFila() const;
    int obtenerColumna() const;

    // Métodos para dibujar y gestionar el nodo
    void dibujar(sf::RenderWindow& ventana) const;

    // Métodos relacionados con el semáforo
    void setEsSemaforo(bool valor);
    bool getEsSemaforo() const;
    float obtenerTiempoTranscurrido() const;
    void asignarSemaforo(Semaforo* semaforo);
    Semaforo* obtenerSemaforo() const;
    bool tieneSemaforoEnConexion(const Nodo* nodoConectado) const;
    void agregarSemaforoConexion(Nodo* nodoConectado, Semaforo* semaforo);

    // Métodos para obtener el nombre y el circulo
    std::string obtenerNombre() const;
    sf::CircleShape& getCirculo();
    const sf::CircleShape& getCirculo() const;

    // Métodos para gestionar la calle
    void setColor(sf::Color color);
    void cerrarCalle();
    bool esCerrada() const;
    void abrirCalle();

    // Propiedades adicionales
    sf::Vector2f getPosicion() const;

    // Estructuras para manejar semáforos por conexión
    std::unordered_map<Nodo*, std::pair<Semaforo*, bool>> semaforosPorConexion;

private:
    // Atributos de la clase
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
