#include "Semaforo.h"

Semaforo::Semaforo(float tiempoVerde, float tiempoRojo)
    : tiempoVerde(tiempoVerde), tiempoRojo(tiempoRojo), tiempoTranscurrido(0), enVerde(true) {}

void Semaforo::actualizar(float deltaTiempo) {
    tiempoTranscurrido += deltaTiempo;

    if (enVerde && tiempoTranscurrido >= tiempoVerde) {
        enVerde = false; 
        tiempoTranscurrido = 0; 
    }
    else if (!enVerde && tiempoTranscurrido >= tiempoRojo) {
        enVerde = true;
        tiempoTranscurrido = 0; 
    }
}

bool Semaforo::estaVerde() const {
    return enVerde;
}