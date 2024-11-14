#ifndef BOTONMANAGER_H
#define BOTONMANAGER_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <functional>

class BotonManager {
public:
    BotonManager(const sf::Font& font);
    void agregarBoton(const std::string& texto, const sf::Vector2f& posicion, std::function<void()> callback);
    void draw(sf::RenderWindow& window);
    void manejarEventos(const sf::Event& event, sf::RenderWindow& window);

private:
    struct Boton {
        sf::RectangleShape forma;
        sf::Text textoBoton;
        std::function<void()> callback;
    };

    std::vector<Boton> botones;
    const sf::Font font;
};

#endif // BOTONMANAGER_H