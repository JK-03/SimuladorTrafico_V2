#include "Carro.h"
#include "Interfaz.h"
#include <cmath>
#include <iostream>
#include <limits>
#include <queue>
#include <algorithm>
#include <SFML/Graphics.hpp>
#include <unordered_set>

float Carro::velocidadClima = 15.0f;

Carro::Carro(const std::string& nombre, const sf::Vector2f& posicion, float velocidad, 
             Grafo& grafo, const std::string& rutaImagen, 
             const std::vector<sf::Vector2f>& ruta, 
             const std::map<std::string, Nodo>& nodosSemaforos, float tamanoCuadro)
    : Vehiculo(nombre, posicion, velocidad, rutaImagen), 
      grafo(grafo), 
      ruta(ruta),
      nodosSemaforos(nodosSemaforos), 
      velocidad(15.0f),
      tamanoCuadro(tamanoCuadro)
{
    sprite.setTexture(textura);
    sprite.setScale(0.1f, 0.1f); 
    if (!ruta.empty()) {
        this->posicion = ruta.front();
    } else {
        this->posicion = posicion;
    }
    sprite.setPosition(this->posicion); 
}

void Carro::mover(float deltaTime) {
    if (colisionado) {
        tiempoDetenido -= deltaTime;
        if (tiempoDetenido <= 0) {
            colisionado = false;
        }
        return;
    }

    if (enEspera) {
        return;
    }

    if (ruta.size() < 2) {
        return;
    }

    verificarSemaforos(arbolSemaforos);
    
    if (colisionado) {
        return;
    }

    sf::Vector2f posicionActual = ruta.front();
    sf::Vector2f posicionSiguiente = ruta[1];

    bool esVertical = std::abs(posicionSiguiente.x - posicionActual.x) < std::numeric_limits<float>::epsilon();
    bool esHorizontal = std::abs(posicionSiguiente.y - posicionActual.y) < std::numeric_limits<float>::epsilon();

    if (esVertical) {
        if (posicionSiguiente.y > posicionActual.y) {
            posicionActual.x -= tamanoCuadro / 4.0f;
            posicionSiguiente.x -= tamanoCuadro / 4.0f;
        } else {
            posicionActual.x += tamanoCuadro / 4.0f;
            posicionSiguiente.x += tamanoCuadro / 4.0f;
        }
    } else if (esHorizontal) {
        if (posicionSiguiente.x > posicionActual.x) {
            posicionActual.y += tamanoCuadro / 4.0f;
            posicionSiguiente.y += tamanoCuadro / 4.0f;
        } else {
            posicionActual.y -= tamanoCuadro / 4.0f;
            posicionSiguiente.y -= tamanoCuadro / 4.0f;
        }
    }

    sf::Vector2f direccion = posicionSiguiente - posicionActual;
    float distanciaTotal = std::sqrt(direccion.x * direccion.x + direccion.y * direccion.y);
    if (distanciaTotal > 0) {
        direccion /= distanciaTotal;
    }

    sf::Vector2f nuevaPosicion = posicion + direccion * velocidad * deltaTime;

    float distanciaRecorrida = std::sqrt(
        (nuevaPosicion.x - posicionActual.x) * (nuevaPosicion.x - posicionActual.x) +
        (nuevaPosicion.y - posicionActual.y) * (nuevaPosicion.y - posicionActual.y)
    );

    if (distanciaRecorrida >= distanciaTotal) {
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

void Carro::mostrarColision(sf::RenderWindow& window, const std::vector<Carro*>& carros) {
    if (!colisionado) return;

    float radioPequeno = 30.0f;
    sf::CircleShape indicador(radioPequeno);
    indicador.setFillColor(sf::Color(255, 0, 0, 100));
    indicador.setPosition(posicion.x, posicion.y);
    window.draw(indicador);
}

bool Carro::verificarColisiones(const std::vector<Carro*>& listaDeCarros) {
    const float radioColision = 20.0f;
    bool estaEnRadioDeColision = false;

    for (size_t i = 0; i < listaDeCarros.size(); ++i) {
        Carro* otroCarro = listaDeCarros[i];

        if (this != otroCarro) {
            float distancia = std::sqrt(
                std::pow(this->obtenerPosicion().x - otroCarro->obtenerPosicion().x, 2) +
                std::pow(this->obtenerPosicion().y - otroCarro->obtenerPosicion().y, 2)
            );

            if (distancia < radioColision) {
                std::string nodoActual = grafo.obtenerNodoDesdePosicion(this->posicion, 35.0f);
                std::string nodoOtroCarro = grafo.obtenerNodoDesdePosicion(otroCarro->obtenerPosicion(), 35.0f);

                if (nodosSemaforos.find(nodoActual) != nodosSemaforos.end() &&
                    nodosSemaforos.find(nodoOtroCarro) != nodosSemaforos.end()) {
                    continue;
                }

                this->detener(10.0f);
                otroCarro->detener(10.0f);

                this->colisionado = true;
                otroCarro->colisionado = true;

                return true; 
            }

            if (otroCarro->colisionado && distancia < radioEspera) {
                estaEnRadioDeColision = true;
            }
        }
    }

    if (estaEnRadioDeColision) {
        enEspera = true; 
    } else {
        enEspera = false; 
    }

    return false; 
}

void Carro::actualizarVelocidad(float nuevaVelocidad) {
    if (!colisionado) {
        velocidad = nuevaVelocidad;
    } 
}

void Carro::verificarSemaforos(ArbolSemaforos* arbolSemaforos) {
    if (arbolSemaforos == nullptr) {
        return; 
    }

    NodoArbol* semaforoCercano = arbolSemaforos->buscarSemaforoCercano(posicion, 30.0f);

    if (semaforoCercano) {
        if (semaforoCercano->semaforo->estaRojo()) {
            enEspera = true;
            velocidad = 0.0f;
        } else {
            enEspera = false;
            actualizarVelocidad(Carro::velocidadClima);
        }
    }
}

bool Carro::dentroDelRadio(Semaforo* semaforo, float radioDeteccion) {
    if (semaforo == nullptr) {
        return false;  
    }

    float distanciaX = semaforo->obtenerPosicion().x - this->posicion.x;
    float distanciaY = semaforo->obtenerPosicion().y - this->posicion.y;
    float distancia = std::sqrt(distanciaX * distanciaX + distanciaY * distanciaY);
    
    return distancia <= radioDeteccion;
}

void Carro::cargarSemaforos(ArbolSemaforos* arbol) {
    arbolSemaforos = arbol; 
}