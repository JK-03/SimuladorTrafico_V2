#include "Grafo.h"
#include <unordered_map>
#include <iostream>
#include <cmath>

Grafo::Grafo() : espaciado(200.0f), filas(4), columnas(6) { 
    srand(static_cast<unsigned>(time(0)));
}

void Grafo::agregarNodo(const std::string& nombre, const sf::Vector2f& posicion, float tiempoVerde, float tiempoRojo, float radio) {
    int fila = static_cast<int>(posicion.y / espaciado);
    int columna = static_cast<int>(posicion.x / espaciado);
    
    nodos[nombre] = Nodo(posicion, tiempoVerde, tiempoRojo, fila, columna, radio);
}

void Grafo::agregarArista(const std::string& nodoA, const std::string& nodoB) {
    if (nodos.find(nodoA) != nodos.end() && nodos.find(nodoB) != nodos.end()) {
        aristas.push_back(std::make_pair(nodoA, nodoB));
        aristas.push_back(std::make_pair(nodoB, nodoA));
    }
}


bool Grafo::estaAristaLibre(const std::string& desde, const std::string& hacia) {
    return std::find(aristas.begin(), aristas.end(), std::make_pair(desde, hacia)) == aristas.end();
}

bool Grafo::estaSemaforoVerde(const std::string& nodo) const {
    auto it = nodos.find(nodo);
    if (it == nodos.end()) {
        return false;
    }
    return it->second.obtenerSemaforo().estaVerde();
}

sf::Vector2f Grafo::obtenerPosicionNodo(const std::string& nombreNodo) const {
    auto it = nodos.find(nombreNodo);
    if (it != nodos.end()) {
        sf::Vector2f posicionOriginal = it->second.posicion;
        return posicionOriginal;
    } else {
        return sf::Vector2f(0, 0);
    }
}

int Grafo::getNumeroDeNodos() const {
    return nodos.size();
}

void Grafo::actualizarSemaforos(float deltaTiempo) {
    if (deltaTiempo <= 0) return;
    for (auto& par : nodos) {
        par.second.obtenerSemaforo().actualizar(deltaTiempo);
    }
}

Semaforo& Grafo::obtenerSemaforo(const std::string& nombreNodo) {
    return nodos[nombreNodo].obtenerSemaforo(); 
}

void Grafo::dibujar(sf::RenderWindow& window, bool mostrarEtiquetas) {
    if (!font.loadFromFile("../Resources/Roboto-BoldCondensed.ttf")) {
    }

    for (const auto& arista : aristas) {
        const auto& n1 = nodos.find(arista.first);
        const auto& n2 = nodos.find(arista.second);

        if (n1 != nodos.end() && n2 != nodos.end()) {
            sf::Vertex line[] = {
                sf::Vertex(n1->second.obtenerPosicion(), sf::Color::Black),
                sf::Vertex(n2->second.obtenerPosicion(), sf::Color::Black)
            };
            window.draw(line, 2, sf::Lines);
        }
    }

    for (const auto& nodo : nodos) {
        sf::Color color = nodo.second.obtenerSemaforo().estaVerde() ? sf::Color::Green : sf::Color::Red;
        sf::CircleShape shape(10);
        shape.setPosition(nodo.second.obtenerPosicion().x - 10, nodo.second.obtenerPosicion().y - 10); 
        shape.setFillColor(color);
        window.draw(shape);

        if (mostrarEtiquetas) {
            sf::Text text(nodo.first, font, 15);
            text.setPosition(nodo.second.obtenerPosicion().x - 10, nodo.second.obtenerPosicion().y - 25);
            text.setFillColor(sf::Color::Black);
            window.draw(text);
        }
    }
}

void Grafo::agregarNodosSecuenciales(float espaciado, const sf::FloatRect& areaValida, const sf::Vector2f& primeraPosicion) {
    int fila = nodoCount / columnas;
    int columna = nodoCount % columnas;

    float x = primeraPosicion.x + columna * espaciado;
    float y = primeraPosicion.y + fila * espaciado;

    if (x <= areaValida.left + areaValida.width && y <= areaValida.top + areaValida.height) {
        sf::Vector2f posicion(x, y);
        std::string nombre = "S_" + std::to_string(fila + 1) + "_" + std::to_string(columna + 1);

        agregarNodo(nombre, posicion, 30.0f, 40.0f, 15.0f);
        agregarAristasSecuenciales();

        nodoCount++;
    } else if (interfaz && !interfaz->getMostrarMensajeLimite()) { 
        interfaz->setMostrarMensajeLimite(true);
    }
}

void Grafo::agregarAristasSecuenciales() {
    for (auto it = nodos.begin(); it != nodos.end(); ++it) {
        int filaActual = it->second.obtenerFila();
        int columnaActual = it->second.obtenerColumna();

        if (columnaActual < columnas - 1) {
            std::string nombreSiguiente = "S_" + std::to_string(filaActual + 1) + "_" + std::to_string(columnaActual + 2);
            if (nodos.find(nombreSiguiente) != nodos.end()) {
                agregarArista(it->first, nombreSiguiente);
            }
        }

        if (filaActual < filas - 1) {
            std::string nombreSiguiente = "S_" + std::to_string(filaActual + 2) + "_" + std::to_string(columnaActual + 1);
            if (nodos.find(nombreSiguiente) != nodos.end()) {
                agregarArista(it->first, nombreSiguiente);
            }
        }
    }
}

std::vector<std::string> Grafo::obtenerNodosConectados(const std::string& nombreNodo) const {
    std::vector<std::string> nodosConectados;
    for (const auto& arista : aristas) {
        if (arista.first == nombreNodo) {
            nodosConectados.push_back(arista.second);
        } else if (arista.second == nombreNodo) {
            nodosConectados.push_back(arista.first);
        }
    }
    return nodosConectados;
}

std::string Grafo::obtenerNodoAleatorio() const {
    if (nodos.empty()) {
        return "";
    }

    static std::string ultimoNodo;
    static bool semillaInicializada = false;
    if (!semillaInicializada) {
        std::srand(static_cast<unsigned int>(std::time(0)));
        semillaInicializada = true;
    }

    int index;
    std::string nodoAleatorio;

    do {
        index = std::rand() % nodos.size();
        auto it = nodos.begin();
        std::advance(it, index);
        nodoAleatorio = it->first; 
    } while (nodoAleatorio == ultimoNodo);

    ultimoNodo = nodoAleatorio; 
    return nodoAleatorio;
}

std::vector<std::pair<const std::string, Nodo>> Grafo::getNodos() const {
    std::vector<std::pair<const std::string, Nodo>> nodosList;
    for (const auto& par : nodos) {
        nodosList.push_back(par); 
    }
    return nodosList;
}

std::string Grafo::obtenerNodoDesdePosicion(const sf::Vector2f& posicion, float margen) const {
    for (const auto& [nombreNodo, nodo] : nodos) {
        sf::Vector2f posicionNodo = nodo.obtenerPosicion();

        if (std::abs(posicionNodo.x - posicion.x) <= margen && 
            std::abs(posicionNodo.y - posicion.y) <= margen) {
            return nombreNodo;
        }
    }
    return ""; 
}

std::unordered_map<std::string, Nodo> Grafo::obtenerNodos() const {
        std::unordered_map<std::string, Nodo> nodosUnorderedMap;
        for (const auto& par : nodos) {
            nodosUnorderedMap[par.first] = par.second;
        }
        return nodosUnorderedMap;
    }

std::map<std::string, Nodo> Grafo::getNodosSemaforos() const {
    std::map<std::string, Nodo> nodosSemaforos;
    for (const auto& par : nodos) {
        nodosSemaforos[par.first] = par.second;
    }
    return nodosSemaforos;
}

std::vector<std::string> Grafo::obtenerSemaforosConectados(const std::string& nombreNodo) {
    std::vector<std::string> nodosConectados = obtenerNodosConectados(nombreNodo);
    std::vector<std::string> semaforosVerdes;

    for (const auto& nodo : nodosConectados) {
        if (estaSemaforoVerde(nodo)) {
            semaforosVerdes.push_back(nodo);
        }
    }
    return semaforosVerdes;
}

float Grafo::getPeso(const std::string& desde, const std::string& hacia) const {
    for (const auto& arista : aristas) {
        if ((arista.first == desde && arista.second == hacia) || 
            (arista.first == hacia && arista.second == desde)) {
            return 1.0f; 
        }
    }
    return -1.0f; 
}

void Grafo::setInterfaz(Interfaz* interfaz) {
    this->interfaz = interfaz; 
}

