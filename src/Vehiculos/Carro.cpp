#include "Carro.h"
#include <cmath>
#include <iostream>
#include <limits>
#include <queue>
#include <algorithm>

Carro::Carro(const std::string& nombre, const sf::Vector2f& posicion, float velocidad, 
             Grafo& grafo, const std::string& rutaImagen, 
             const std::vector<sf::Vector2f>& ruta, 
             const std::map<std::string, Nodo>& nodosSemaforos)
    : Vehiculo(nombre, posicion, velocidad, rutaImagen), 
      grafo(grafo), 
      ruta(ruta),
      nodosSemaforos(nodosSemaforos) 
{
    if (!textura.loadFromFile(rutaImagen)) {
    }

    sprite.setTexture(textura);
    sprite.setScale(0.1f, 0.1f); 
    this->posicion = !ruta.empty() ? ruta.front() : posicion;
    sprite.setPosition(this->posicion); 
}

void Carro::mover(float deltaTime) {
    if (ruta.size() < 2) {
        //std::cout << "Ruta insuficiente para mover." << std::endl;
        return;
    }

    std::string nodoActual = grafo.obtenerNodoDesdePosicion(this->posicion, 60.0f);

    if (nodosSemaforos.find(nodoActual) != nodosSemaforos.end() && !grafo.estaSemaforoVerde(nodoActual)) {
        //std::cout << "Semáforo en rojo en el nodo " << nodoActual << ". El carro se detiene." << std::endl;
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
        //std::cout << "Nodo alcanzado: (" << posicionSiguiente.x << ", " << posicionSiguiente.y << ")" << std::endl;
        ruta.erase(ruta.begin());

        if (!ruta.empty()) {
            posicion = ruta.front();
        }
    } else {
        posicion = nuevaPosicion;
    }

    sprite.setPosition(posicion);
}

void simularFlujo(Grafo& grafo, float deltaTiempo) {
    grafo.actualizarSemaforos(deltaTiempo);

    for (const auto& [nombreNodo, nodo] : grafo.getNodosSemaforos()) {
        if (nombreNodo.empty()) {
            //std::cerr << "Error: El nodo no tiene nombre asignado." << std::endl;
            continue; 
        }

        if (!grafo.estaSemaforoVerde(nombreNodo)) {
            //std::cout << "Semáforo en rojo, detenido en nodo: " << nombreNodo << std::endl;
        } else {
            //std::cout << "Semáforo en verde en el nodo: " << nombreNodo << ". Avanzando..." << std::endl;
        }
    }
}

float calcularDistancia(const sf::Vector2f& a, const sf::Vector2f& b) {
    return std::sqrt(std::pow(b.x - a.x, 2) + std::pow(b.y - a.y, 2));
}

void simularMovimiento(Grafo& grafo, sf::Vector2f& posicionCarro,const std::string& nodoDestino, float deltaTiempo) {
    float velocidad = 5000.0f; 
    bool carroDetenido = false;

    const Nodo& nodo = grafo.getNodosSemaforos().at(nodoDestino);
    float distancia = calcularDistancia(posicionCarro, nodo.obtenerPosicion());

    if (distancia <= nodo.obtenerRadio()) {
        if (!nodo.obtenerSemaforo().estaVerde()) {
            carroDetenido = true;
        }
    }

    if (!carroDetenido) {
        sf::Vector2f direccion = nodo.obtenerPosicion() - posicionCarro;
        float longitud = std::sqrt(direccion.x * direccion.x + direccion.y * direccion.y);

        if (longitud != 0) direccion /= longitud; 

        posicionCarro += direccion * velocidad * deltaTiempo;
    }
}

void Carro::dibujar(sf::RenderWindow& window) {
    window.draw(sprite);
}

sf::Vector2f Carro::obtenerDireccionDesdeArista(const Grafo& grafo, 
                                                const std::string& nodoDesde, 
                                                const std::string& nodoHacia) {
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
