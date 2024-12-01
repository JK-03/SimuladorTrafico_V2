#ifndef CARRO_H
#define CARRO_H

#include "Colisionador.h"
#include "Interfaz.h" 

class Grafo;
class Interfaz; 
class Nodo; 

#include "Ciudad/Grafo.h"
#include "Vehiculo.h"
#include <vector>
#include "Semaforo.h"
#include "ArbolSemaforos.h"

class Carro : public Vehiculo {
public:
    Carro(const std::string& nombre, const sf::Vector2f& posicion, float velocidad, Grafo& grafo, const std::string& rutaImagen, const std::vector<sf::Vector2f>& ruta, const std::map<std::string, Nodo>& nodosSemaforos, float tamanoCuadro = 50.0f);

    sf::Vector2f obtenerDireccionDesdeArista(const Grafo& grafo, const std::string& nodoDesde, const std::string& nodoHacia);

    void dibujar(sf::RenderWindow& window);
    void calcularRuta(const std::string& nodoInicio, const std::string& nodoDestino);
    void mover(float deltaTime);
    void detener(float tiempo);
    const std::map<std::string, Nodo>& getNodosSemaforos() const; 
    void actualizarVelocidad(float nuevaVelocidad);
    void mostrarColision(sf::RenderWindow& window, const std::vector<Carro*>& carros);
    void cargarSemaforos(ArbolSemaforos* arbolSemaforos); 
    void continuarMovimiento(); 

    float getVelocidad() const;

    static std::vector<sf::Vector2f> generarRutaCiclica(Grafo& grafo, const std::string& nodoInicio, int cantidad);

    bool colisionDetectada() const;
    bool verificarColisiones(const std::vector<Carro*>& listaDeCarros);
    bool colisionado = false;
    bool enEspera = false;

    const float radioEspera = 50.0f;

    void verificarSemaforos(ArbolSemaforos* arbolSemaforos);
    bool dentroDelRadio(Semaforo* semaforo, float radioDeteccion);
    
private:
    float tamanoCuadro;
    std::vector<sf::Vector2f> ruta;
    std::map<std::string, Nodo> nodosSemaforos;

    float tiempoDetenido = 0;
    float velocidad;

    Grafo& grafo; 
    Colisionador colisionador;
    ArbolSemaforos* arbolSemaforos;
};

#endif // CARRO_H