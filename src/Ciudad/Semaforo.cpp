#include "Semaforo.h"

Semaforo::Semaforo(float tiempoVerde, float tiempoRojo, float tiempoAmarillo)
    : tiempoVerde(tiempoVerde), tiempoRojo(tiempoRojo), tiempoAmarillo(tiempoAmarillo),
      estado(Verde), tiempoTranscurrido(0.0f) {}

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

void Semaforo::actualizar(float deltaTime) {
    tiempoTranscurrido += deltaTime;

    switch (estado) {
        case Verde:
            if (tiempoTranscurrido >= tiempoVerde) {
                estado = ParpadeandoAmarillo;
                tiempoTranscurrido = 0.0f;
            }
            break;

        case ParpadeandoAmarillo:
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
    }
}

void Semaforo::ponerRojo() {
    estado = Rojo;
    tiempoTranscurrido = 0.0f;
}

void Semaforo::ponerVerde() {
    estado = Verde;
    tiempoTranscurrido = 0.0f; 
}
