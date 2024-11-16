#include "Carro.h"
#include <cmath>
#include <iostream>
#include <limits>
#include <queue>
#include <algorithm>
#include <unordered_set>

Carro::Carro(const std::string& nombre, const sf::Vector2f& posicion, float velocidad, 
             Grafo& grafo, const std::string& rutaImagen, 
             const std::vector<sf::Vector2f>& ruta, 
             const std::map<std::string, Nodo>& nodosSemaforos)
    : Vehiculo(nombre, posicion, velocidad, rutaImagen), 
      grafo(grafo), 
      ruta(ruta),
      nodosSemaforos(nodosSemaforos), 
      velocidad(10.0f) 
{
    sprite.setTexture(textura);
    sprite.setScale(0.1f, 0.1f); 
    this->posicion = !ruta.empty() ? ruta.front() : posicion;
    sprite.setPosition(this->posicion); 
}

void Carro::mover(float deltaTime) {
    if (ruta.size() < 2) {
        return;
    }

    std::string nodoActual = grafo.obtenerNodoDesdePosicion(this->posicion, 30.0f);

    if (nodosSemaforos.find(nodoActual) != nodosSemaforos.end() && !grafo.estaSemaforoVerde(nodoActual)) {
        return;
    }

    sf::Vector2f posicionActual = ruta.front();
    sf::Vector2f posicionSiguiente = ruta[1];

    sf::Vector2f direccion = posicionSiguiente - posicionActual;
    float distanciaTotal = std::hypot(direccion.x, direccion.y);

    if (distanciaTotal > 0) {
        direccion /= distanciaTotal;
    }

    sf::Vector2f nuevaPosicion = posicion + direccion * velocidad * deltaTime;

    if (std::hypot(nuevaPosicion.x - posicionActual.x, nuevaPosicion.y - posicionActual.y) >= distanciaTotal) {
        ruta.erase(ruta.begin());

        if (!ruta.empty()) {
            posicion = ruta.front();
        }
    } else {
        posicion = nuevaPosicion;
    }

    sprite.setPosition(posicion);
}

std::vector<sf::Vector2f> Carro::generarRutaCiclica(Grafo& grafo, const std::string& nodoInicio, int cantidad) {
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

void Carro::dibujar(sf::RenderWindow& window) {
    window.draw(sprite);
}

sf::Vector2f Carro::obtenerDireccionDesdeArista(const Grafo& grafo, const std::string& nodoDesde, const std::string& nodoHacia) {
    return grafo.obtenerPosicionNodo(nodoHacia) - grafo.obtenerPosicionNodo(nodoDesde);
}

void Carro::calcularRuta(const std::string& nodoInicio, const std::string& nodoDestino) {
    std::map<std::string, float> distancias;
    std::map<std::string, std::string> predecesores;

    auto comparador = [](const std::pair<std::string, float>& a, const std::pair<std::string, float>& b) {
        return a.second > b.second;
    };

    std::priority_queue<std::pair<std::string, float>, 
                        std::vector<std::pair<std::string, float>>, 
                        decltype(comparador)> cola(comparador);

    for (const auto& nodo : grafo.getNodos()) {
        distancias[nodo.first] = std::numeric_limits<float>::infinity();
    }

    distancias[nodoInicio] = 0;
    cola.emplace(nodoInicio, 0);

    while (!cola.empty()) {
        auto [nodoActual, distanciaActual] = cola.top();
        cola.pop();

        if (nodoActual == nodoDestino) {
            ruta.clear();
            for (auto at = nodoDestino; !at.empty(); at = predecesores[at]) {
                ruta.push_back(grafo.obtenerPosicionNodo(at));
            }
            std::reverse(ruta.begin(), ruta.end());
            return;
        }

        for (const auto& nodoConectado : grafo.obtenerNodosConectados(nodoActual)) {
            float nuevaDistancia = distanciaActual + grafo.getPeso(nodoActual, nodoConectado);
            if (nuevaDistancia < distancias[nodoConectado]) {
                distancias[nodoConectado] = nuevaDistancia;
                predecesores[nodoConectado] = nodoActual;
                cola.emplace(nodoConectado, nuevaDistancia);
            }
        }
    }
}

void Carro::actualizarVelocidad(float nuevaVelocidad) {
    velocidad = nuevaVelocidad;
}

float Carro::getVelocidad() const {
    return velocidad;
}