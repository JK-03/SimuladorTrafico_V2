#ifndef CARRO_H
#define CARRO_H

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

    // Métodos de movimiento y ruta
    void mover(float deltaTime);
    void detener(float tiempo);
    void continuarMovimiento();
    void calcularRuta(const std::string& nodoInicio, const std::string& nodoDestino);
    sf::Vector2f obtenerDireccionDesdeArista(const Grafo& grafo, const std::string& nodoDesde, const std::string& nodoHacia);
    std::vector<sf::Vector2f> generarRutaCiclicaSinNodoPrevio(Grafo& grafo, const std::string& nodoInicio, int cantidad, const std::string& nodoPrevio);

    // Métodos de colisión
    bool colisionDetectada() const;
    bool verificarColisiones(const std::vector<Carro*>& listaDeCarros);
    void mostrarColision(sf::RenderWindow& window, const std::vector<Carro*>& carros);
    
    // Métodos relacionados con semáforos
    void cargarSemaforos(ArbolSemaforos* arbolSemaforos); 
    void verificarSemaforos(ArbolSemaforos* arbolSemaforos);
    bool dentroDelRadio(Semaforo* semaforo, float radioDeteccion);

    // Métodos de velocidad
    void actualizarVelocidad(float nuevaVelocidad);
    float getVelocidad() const;

    // Métodos de dibujo
    void dibujar(sf::RenderWindow& window);

    // Getters
    const std::map<std::string, Nodo>& getNodosSemaforos() const;

    // Propiedades
    bool colisionado = false;
    bool enEspera = false;
    const float radioEspera = 50.0f;

    static float velocidadClima;
    
private:
    float tamanoCuadro;
    std::map<std::string, Nodo> nodosSemaforos;
    float tiempoDetenido = 0;
    float velocidad;
    Grafo& grafo; 
    ArbolSemaforos* arbolSemaforos;

protected:
    std::vector<sf::Vector2f> ruta;
};

#endif // CARRO_H