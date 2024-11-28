#include "Carro.h"
#include <cmath>
#include <iostream>
#include <limits>
#include <queue>
#include <algorithm>
#include <SFML/Graphics.hpp>
#include <unordered_set>

Carro::Carro(const std::string& nombre, const sf::Vector2f& posicion, float velocidad, 
             Grafo& grafo, const std::string& rutaImagen, 
             const std::vector<sf::Vector2f>& ruta, 
             const std::map<std::string, Nodo>& nodosSemaforos, float tamanoCuadro)
    : Vehiculo(nombre, posicion, velocidad, rutaImagen), 
      grafo(grafo), 
      ruta(ruta),
      nodosSemaforos(nodosSemaforos), 
      velocidad(10.0f),
      tamanoCuadro(tamanoCuadro)
{
    sprite.setTexture(textura);
    sprite.setScale(0.1f, 0.1f); 
    this->posicion = !ruta.empty() ? ruta.front() : posicion;
    sprite.setPosition(this->posicion); 
}

void Carro::mover(float deltaTime, const sf::Font& font) {
    if (colisionado) {
        tiempoDetenido -= deltaTime;
        if (tiempoDetenido <= 0) {
            colisionado = false;
        }
        return; // No mover si está colisionado
    }

    if (enEspera) {
        return; // No mover si está esperando debido a una colisión cercana
    }

    if (ruta.size() < 2) {
        return; // No hacer nada si no hay más puntos en la ruta
    }

    std::string nodoActual = grafo.obtenerNodoDesdePosicion(this->posicion, 35.0f);

    if (nodosSemaforos.find(nodoActual) != nodosSemaforos.end() && !grafo.estaSemaforoVerde(nodoActual)) {
        return; // No mover si está en un semáforo en rojo
    }

    sf::Vector2f posicionActual = ruta.front();
    sf::Vector2f posicionSiguiente = ruta[1];

    sf::Vector2f direccion = posicionSiguiente - posicionActual;
    float distanciaTotal = std::sqrt(direccion.x * direccion.x + direccion.y * direccion.y);

    if (distanciaTotal > 0) {
        direccion /= distanciaTotal;
    }

    sf::Vector2f nuevaPosicion = posicion + direccion * velocidad * deltaTime;

    if (std::sqrt((nuevaPosicion.x - posicionActual.x) * (nuevaPosicion.x - posicionActual.x) +
                  (nuevaPosicion.y - posicionActual.y) * (nuevaPosicion.y - posicionActual.y)) >= distanciaTotal) {
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

void Carro::detener(float tiempo) {
    colisionado = true;
    tiempoDetenido = tiempo;
    velocidad = 0.0f;
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

bool Carro::verificarColisiones(const std::vector<Carro*>& listaDeCarros) {
    const float radioColision = 20.0f;
    bool estaEnRadioDeColision = false;

    for (size_t i = 0; i < listaDeCarros.size(); ++i) {
        Carro* otroCarro = listaDeCarros[i];

        // Ignorar el carro actual
        if (this != otroCarro) {
            float distancia = std::sqrt(
                std::pow(this->obtenerPosicion().x - otroCarro->obtenerPosicion().x, 2) +
                std::pow(this->obtenerPosicion().y - otroCarro->obtenerPosicion().y, 2)
            );

            // Si hay colisión directa
            if (distancia < radioColision) {
                // Verificar si ambos carros están en un nodo de semáforo
                std::string nodoActual = grafo.obtenerNodoDesdePosicion(this->posicion, 35.0f);
                std::string nodoOtroCarro = grafo.obtenerNodoDesdePosicion(otroCarro->obtenerPosicion(), 35.0f);

                if (nodosSemaforos.find(nodoActual) != nodosSemaforos.end() &&
                    nodosSemaforos.find(nodoOtroCarro) != nodosSemaforos.end()) {
                    // Ignorar colisión si ambos están en un nodo de semáforo
                    continue;
                }

                // Marcar ambos carros como colisionados y detenerlos
                this->detener(10.0f);
                otroCarro->detener(10.0f);

                this->colisionado = true;
                otroCarro->colisionado = true;

                return true; // Colisión detectada
            }

            // Si el carro está dentro del radio de espera de otro carro colisionado
            if (otroCarro->colisionado && distancia < radioEspera) {
                estaEnRadioDeColision = true;
            }
        }
    }

    // Si está en el radio de colisión, no moverse pero no afectar a otros
    if (estaEnRadioDeColision) {
        enEspera = true; // Marcar como en espera
    } else {
        enEspera = false; // Liberar estado de espera si no hay colisión cercana
    }

    return false; // No hay colisión directa
}




void Carro::mostrarColision(sf::RenderWindow& window, const std::vector<Carro*>& listaDeCarros) {
    bool hayColision = verificarColisiones(listaDeCarros); 

    if (hayColision) {
        colisionador.mostrarColision(window, true); 
    }
}

bool Carro::colisionDetectada() const { 
    return colisionado; 
}