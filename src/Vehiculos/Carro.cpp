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

    if (ruta.size() == 1) {
        std::string nodoActual = grafo.obtenerNodoDesdePosicion(posicion);
        std::vector<sf::Vector2f> nuevaRuta = generarRutaCiclicaSinNodoPrevio(grafo, nodoActual, 5, "");

        if (!nuevaRuta.empty()) {
            posicion = nuevaRuta.front();
            ruta = nuevaRuta;
        } else {
            std::cout << "No se generó una nueva ruta." << std::endl;
        }
        return;
    }

    verificarSemaforos(arbolSemaforos);

    if (ruta.size() >= 2) {
        sf::Vector2f posicionActual = ruta.front();
        sf::Vector2f posicionSiguiente = ruta[1];

        std::string nodoActualNombre = grafo.obtenerNodoDesdePosicion(posicionActual);
        std::string nodoSiguienteNombre = grafo.obtenerNodoDesdePosicion(posicionSiguiente);

        Nodo* nodoSiguiente = grafo.obtenerNodoPorNombre(nodoSiguienteNombre);
        if (nodoSiguiente && nodoSiguiente->esCerrada()) {
            
            // Generar una nueva ruta sin incluir la calle cerrada
            std::string nodoPrevio = nodoActualNombre;
            std::vector<sf::Vector2f> nuevaRuta = generarRutaCiclicaSinNodoPrevio(grafo, nodoPrevio, 5, nodoSiguienteNombre);

            if (!nuevaRuta.empty()) {
                ruta = nuevaRuta;
                posicion = ruta.front();
            } 
            return;
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

        if (distanciaRecorrida >= distanciaTotal - 0.1f) {
            ruta.erase(ruta.begin());

            if (ruta.size() > 1) {
                posicion = ruta.front();
            } else {
                std::string nodoActual = grafo.obtenerNodoDesdePosicion(posicion);
                std::string nodoPrevio = ruta.size() > 1 ? grafo.obtenerNodoDesdePosicion(ruta[1]) : "";
                
                std::vector<sf::Vector2f> nuevaRuta = generarRutaCiclicaSinNodoPrevio(grafo, nodoActual, 5, nodoPrevio);

                if (!nuevaRuta.empty()) {
                    ruta = nuevaRuta;
                    posicion = ruta.front();
                } else {
                    std::cout << "No se generó una nueva ruta." << std::endl;
                }
            }
        } else {
            posicion = nuevaPosicion;
        }
    }

    sprite.setPosition(posicion);
}

std::vector<sf::Vector2f> Carro::generarRutaCiclicaSinNodoPrevio(Grafo& grafo, const std::string& nodoInicio, int cantidad, const std::string& nodoPrevio) {
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

        std::vector<std::string> nodosValidos;
        std::copy_if(nodosConectados.begin(), nodosConectados.end(), std::back_inserter(nodosValidos),
                     [&](const std::string& nodo) {
                         return nodosVisitados.count(nodo) == 0 && nodo != nodoPrevio;
                     });

        if (!nodosValidos.empty()) {
            int indiceAleatorio = rand() % nodosValidos.size();
            nodoActual = nodosValidos[indiceAleatorio];
            nodosVisitados.insert(nodoActual);

            ruta.push_back(grafo.obtenerPosicionNodo(nodoActual));
        } else {
            break;
        }
    }

    if (!ruta.empty() && nodoPrevio == grafo.obtenerNodoDesdePosicion(ruta.front())) {
        ruta.erase(ruta.begin()); 
    }

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