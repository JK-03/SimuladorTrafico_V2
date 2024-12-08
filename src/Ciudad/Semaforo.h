#ifndef SEMAFORO_H
#define SEMAFORO_H

#include <SFML/Graphics.hpp>  
#include <SFML/System/Clock.hpp>

class Semaforo {
public:
    // Enumeración para los estados del semáforo
    enum Estado {
        Verde,
        Rojo,
        Amarillo,
        ParpadeandoAmarillo
    };

    Semaforo(float tiempoVerde, float tiempoRojo, float tiempoAmarillo, float tiempoParpadeo, sf::Vector2f posicion, float radio);

    // Métodos para obtener el estado y reloj
    Estado obtenerEstado() const;
    const sf::Clock& obtenerReloj() const;
    sf::Clock& obtenerReloj();

    // Métodos de actualización del semáforo
    void actualizar(float deltaTime);
    void ponerRojo();
    void ponerVerde(); 

    // Métodos para comprobar los estados del semáforo
    bool estaVerde() const; 
    bool estaRojo() const; 
    bool estaAmarillo() const; 
    bool estaParpadeandoAmarillo() const; 

    // Métodos para la posición y dibujo del semáforo
    sf::Vector2f obtenerPosicion() const;
    void setPosicion(float x, float y);
    void dibujar(sf::RenderWindow& ventana);

private:
    // Atributos del semáforo
    float tiempoVerde;
    float tiempoRojo;
    float tiempoAmarillo;
    float tiempoParpadeo;
    float radio;

    bool estaEncendido;
    Estado estado;
    float tiempoTranscurrido;
    sf::Clock reloj;

    sf::Vector2f posicion;
    sf::CircleShape circuloSemaforo;
};

#endif // SEMAFORO_H