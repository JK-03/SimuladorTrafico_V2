#include "Ruta.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <unordered_set>
#include <vector>
#include <algorithm>

std::vector<sf::Vector2f> generarRutaCiclica(Grafo& grafo, const std::string& nodoInicio, int cantidad) {
    std::vector<sf::Vector2f> ruta;
    std::unordered_set<std::string> nodosVisitados;
    std::string nodoActual = nodoInicio;

    ruta.push_back(grafo.obtenerPosicionNodo(nodoActual));
    nodosVisitados.insert(nodoActual);

    for (int i = 1; i < cantidad; ++i) {
        std::vector<std::string> nodosConectados = grafo.obtenerNodosConectados(nodoActual);

        if (nodosConectados.empty()) {
            break;
        }

        std::vector<std::string> nodosNoVisitados;
        std::copy_if(nodosConectados.begin(), nodosConectados.end(), std::back_inserter(nodosNoVisitados),
                     [&](const std::string& nodo) { return nodosVisitados.count(nodo) == 0; });

        if (!nodosNoVisitados.empty()) {
            int indiceAleatorio = rand() % nodosNoVisitados.size();
            nodoActual = nodosNoVisitados[indiceAleatorio];
            nodosVisitados.insert(nodoActual);
        } else {
            break;
        }

        sf::Vector2f posicionNodo = grafo.obtenerPosicionNodo(nodoActual);
        ruta.push_back(posicionNodo);
    }

    ruta.push_back(grafo.obtenerPosicionNodo(nodoInicio));

    return ruta;
}