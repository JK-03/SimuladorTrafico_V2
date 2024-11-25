#ifndef SEMAFORO_H
#define SEMAFORO_H

#include <SFML/System/Clock.hpp>

class Semaforo {
public:
    enum Estado {
        Verde,
        Rojo,
        Amarillo,
        ParpadeandoAmarillo
    };

    Semaforo(float tiempoVerde, float tiempoRojo, float tiempoAmarillo);

    Estado obtenerEstado() const;
    bool estaVerde() const; 
    bool estaRojo() const; 
    bool estaAmarillo() const; 
    bool estaParpadeandoAmarillo() const; 
    const sf::Clock& obtenerReloj() const;

    void actualizar(float deltaTime);

    void ponerRojo();  // Nueva función para cambiar a rojo
    void ponerVerde(); // Nueva función para cambiar a verde

    sf::Clock& obtenerReloj();

private:
    float tiempoVerde;
    float tiempoRojo;
    float tiempoAmarillo;
    Estado estado;
    float tiempoTranscurrido;
    sf::Clock reloj;
};

#endif // SEMAFORO_H
