#ifndef SEMAFORO_H
#define SEMAFORO_H

#include <SFML/Graphics.hpp>  
#include <SFML/System/Clock.hpp>

class Semaforo {
public:
    enum Estado {
        Verde,
        Rojo,
        Amarillo,
        ParpadeandoAmarillo
    };

    Semaforo(float tiempoVerde, float tiempoRojo, float tiempoAmarillo, float tiempoParpadeo, sf::Vector2f posicion, float radio);

    Estado obtenerEstado() const;
    bool estaVerde() const; 
    bool estaRojo() const; 
    bool estaAmarillo() const; 
    bool estaParpadeandoAmarillo() const; 
    const sf::Clock& obtenerReloj() const;

    void actualizar(float deltaTime);
    void ponerRojo();
    void ponerVerde(); 

    sf::Clock& obtenerReloj();
    sf::Vector2f obtenerPosicion() const;

    void dibujar(sf::RenderWindow& ventana);
    void setPosicion(float x, float y);

private:
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