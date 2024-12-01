#ifndef ARBOL_SEMAFOROS_H
#define ARBOL_SEMAFOROS_H

#include <SFML/Graphics.hpp>  
#include "NodoArbol.h"
#include "Nodo.h"

class ArbolSemaforos {
public:
    ArbolSemaforos() : raiz(nullptr) {}

    void insertar(Semaforo* semaforo, Nodo* nodo1, Nodo* nodo2);
    void dibujarSemaforos(sf::RenderWindow& ventana);
    void recorrerEnOrden(NodoArbol* nodo, sf::RenderWindow& ventana) const;
    void actualizarSemaforos(float deltaTime);
    void actualizarRecursivo(NodoArbol* nodo, float deltaTime);

    bool existeSemaforoEnPosicion(NodoArbol* nodo, const sf::Vector2f& posicion, float tolerancia) const;

    NodoArbol* obtenerRaiz();
    NodoArbol* buscarSemaforoCercano(const sf::Vector2f& posicionCarro, float radioDeteccion);
    NodoArbol* buscarAux(NodoArbol* nodo, const sf::Vector2f& posicionCarro, float radioDeteccion);

private:
    NodoArbol* raiz;
    void insertarAux(NodoArbol*& nodo, Semaforo* semaforo, Nodo* nodo1, Nodo* nodo2);

    sf::Clock reloj;
};

#endif // ARBOL_SEMAFOROS_H