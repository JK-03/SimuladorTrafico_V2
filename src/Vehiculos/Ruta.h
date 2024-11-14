#ifndef RUTA_H
#define RUTA_H

#include <vector>
#include <SFML/Graphics.hpp>
#include "Grafo.h"

std::vector<sf::Vector2f> generarRutaCiclica(Grafo& grafo, const std::string& nodoInicio, int cantidad);

#endif // RUTA_H
