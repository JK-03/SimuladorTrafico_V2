#ifndef CARRO_H
#define CARRO_H

#include "Colisionador.h"

class Grafo;
class Interfaz; 
class Nodo; 

#include "Ciudad/Grafo.h"
#include "Vehiculo.h"
#include <vector>
#include "Interfaz.h"
#include "Semaforo.h"

class Carro : public Vehiculo {
public:
    Carro(const std::string& nombre, const sf::Vector2f& posicion, float velocidad, Grafo& grafo, const std::string& rutaImagen, const std::vector<sf::Vector2f>& ruta, const std::map<std::string, Nodo>& nodosSemaforos, float tamanoCuadro = 50.0f);

    sf::Vector2f obtenerDireccionDesdeArista(const Grafo& grafo, const std::string& nodoDesde, const std::string& nodoHacia);

    void dibujar(sf::RenderWindow& window);
    void calcularRuta(const std::string& nodoInicio, const std::string& nodoDestino);
    void mover(float deltaTime, const sf::Font& font);
    void detener(float tiempo);
    const std::map<std::string, Nodo>& getNodosSemaforos() const; 
    void actualizarVelocidad(float nuevaVelocidad);

    float getVelocidad() const;

    std::vector<sf::Vector2f> generarRutaCiclica(Grafo& grafo, const std::string& nodoInicio, int cantidad);

    bool colisionDetectada() const;
    bool verificarColisiones(const std::vector<Carro*>& listaDeCarros);
    bool colisionado = false;

    void mostrarColision(sf::RenderWindow& window, const std::vector<Carro*>& listaDeCarros);

    
private:
    Grafo& grafo; 
    float tamanoCuadro;
    std::vector<sf::Vector2f> ruta;
    std::map<std::string, Nodo> nodosSemaforos;

    float tiempoDetenido = 0;
    float velocidad;

    Colisionador colisionador;
};

#endif // CARRO_H