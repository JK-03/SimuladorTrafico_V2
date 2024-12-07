#ifndef CARRO_ESPECIAL_H
#define CARRO_ESPECIAL_H

#include "Carro.h"

class CarroEspecial : public Carro {
public:
    CarroEspecial(const std::string& nombre, const sf::Vector2f& posicion, float velocidad, 
                  Grafo& grafo, const std::string& rutaImagen, 
                  const std::vector<sf::Vector2f>& ruta, 
                  float tamanoCuadro = 50.0f);

    void mover(float deltaTime) override;
    void verificarSemaforos(ArbolSemaforos* arbolSemaforos); 
    void definirRuta(const std::vector<sf::Vector2f>& nuevaRuta);
    void dibujar(sf::RenderWindow& window) override;

    bool tienePrioridad() const;

private:
    bool prioridad; 
};

#endif // CARRO_ESPECIAL_H
