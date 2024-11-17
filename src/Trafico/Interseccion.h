#ifndef INTERSECCION_H
#define INTERSECCION_H

#include <string>

class Interseccion {
public:
    std::string nombre;
    int prioridad;
    bool tieneSemaforo;

    Interseccion(std::string nombre, int prioridad, bool tieneSemaforo)
        : nombre(nombre), prioridad(prioridad), tieneSemaforo(tieneSemaforo) {}
};

#endif //INTERSECCION_H