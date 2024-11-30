#include "Semaforo.h"
#include <SFML/Graphics.hpp>

Semaforo::Semaforo(float tiempoVerde, float tiempoRojo, float tiempoAmarillo, float tiempoParpadeo, sf::Vector2f posicion, float radio)
    : tiempoVerde(tiempoVerde), tiempoRojo(tiempoRojo), tiempoAmarillo(tiempoAmarillo), tiempoParpadeo(tiempoParpadeo), 
      estado(Verde), tiempoTranscurrido(0.0f), estaEncendido(true), posicion(posicion), radio(radio) {

    circuloSemaforo.setRadius(radio);
    circuloSemaforo.setPointCount(30);  
    circuloSemaforo.setPosition(posicion); 
    circuloSemaforo.setFillColor(sf::Color::Green); 
}

Semaforo::Estado Semaforo::obtenerEstado() const {
    return estado;
}

bool Semaforo::estaVerde() const {
    return estado == Verde;
}

bool Semaforo::estaRojo() const {
    return estado == Rojo;
}

bool Semaforo::estaAmarillo() const {
    return estado == Amarillo;
}

bool Semaforo::estaParpadeandoAmarillo() const {
    return estado == ParpadeandoAmarillo;
}

sf::Clock& Semaforo::obtenerReloj() {
    return reloj;
}

const sf::Clock& Semaforo::obtenerReloj() const {
    return reloj;
}

void Semaforo::ponerRojo() {
    estado = Rojo;
    tiempoTranscurrido = 0.0f;
    circuloSemaforo.setFillColor(sf::Color::Red);
}

void Semaforo::ponerVerde() {
    estado = Verde;
    tiempoTranscurrido = 0.0f;
    circuloSemaforo.setFillColor(sf::Color::Green); 
}

sf::Vector2f Semaforo::obtenerPosicion() const {
    return posicion;
}

void Semaforo::dibujar(sf::RenderWindow& ventana) {
    sf::CircleShape nodoFondo(15 + 2.f);
    nodoFondo.setPosition(posicion.x - nodoFondo.getRadius(), posicion.y - nodoFondo.getRadius());

    if (estado == Rojo) {
        nodoFondo.setFillColor(sf::Color(255, 0, 0, 100));
    } else if (estado == Verde) {
        nodoFondo.setFillColor(sf::Color(0, 255, 0, 100));
    } else if (estado == Amarillo) {
        nodoFondo.setFillColor(sf::Color(255, 255, 0, 100));
    } else if (estado == ParpadeandoAmarillo) {
        if (static_cast<int>(reloj.getElapsedTime().asSeconds()) % 2 == 0) {
            nodoFondo.setFillColor(sf::Color(255, 255, 0, 100));
        } else {
            nodoFondo.setFillColor(sf::Color(255, 255, 0, 0));
        }
    }

    ventana.draw(nodoFondo);

    sf::CircleShape circulo(10);
    circulo.setPosition(posicion.x - 10.f, posicion.y - 10.f);

    float tiempoTranscurrido = reloj.getElapsedTime().asSeconds();
    if (estado == Amarillo || (estado == ParpadeandoAmarillo && estaEncendido)) {
        if (fmod(tiempoTranscurrido, 1.0f) < 0.5f) {
            circulo.setFillColor(sf::Color::Yellow);  
        } else {
            circulo.setFillColor(sf::Color::Transparent); 
        }
    } else if (estado == Rojo) {
        circulo.setFillColor(sf::Color::Red);
    } else if (estado == Verde) {
        circulo.setFillColor(sf::Color::Green);
    }

    ventana.draw(circulo);
}

void Semaforo::setPosicion(float x, float y) {
    posicion = sf::Vector2f(x, y);  
    circuloSemaforo.setPosition(posicion); 
}

void Semaforo::actualizar(float deltaTime) {
    tiempoTranscurrido += deltaTime;

    switch (estado) {
        case Verde:
            if (tiempoTranscurrido >= tiempoVerde) {
                estado = Amarillo;
                tiempoTranscurrido = 0.0f;
            }
            break;
        case Amarillo:
            if (tiempoTranscurrido >= tiempoAmarillo) {
                estado = Rojo;
                tiempoTranscurrido = 0.0f;
            }
            break;
        case Rojo:
            if (tiempoTranscurrido >= tiempoRojo) {
                estado = Verde;
                tiempoTranscurrido = 0.0f;
            }
            break;
        case ParpadeandoAmarillo:
            if (tiempoTranscurrido >= tiempoParpadeo) {
                estaEncendido = !estaEncendido;
                tiempoTranscurrido = 0.0f;
            }
            break;
    }
}