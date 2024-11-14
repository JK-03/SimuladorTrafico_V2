#ifndef SEMAFORO_H
#define SEMAFORO_H
#include <queue>

class Carro;

class Semaforo {
public:
    Semaforo(float tiempoVerde, float tiempoRojo);
    void actualizar(float deltaTiempo);
    bool estaVerde() const; 

    float getTiempoVerde() const { return tiempoVerde; }
    float getTiempoRojo() const { return tiempoRojo; }

    std::queue<Carro*> carrosEsperando;

private:
    float tiempoVerde;
    float tiempoRojo;
    float tiempoTranscurrido;
    bool enVerde;
};

#endif // SEMAFORO_H