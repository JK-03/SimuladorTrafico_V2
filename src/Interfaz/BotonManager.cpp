#include "BotonManager.h"

BotonManager::BotonManager(const sf::Font& font) : font(font) {}

void BotonManager::agregarBoton(const std::string& texto, const sf::Vector2f& posicion, std::function<void()> callback) {
    Boton boton;
    boton.forma.setSize(sf::Vector2f(180, 40));
    boton.forma.setFillColor(sf::Color(100, 100, 250));
    boton.forma.setPosition(posicion);

    boton.textoBoton.setFont(font);
    boton.textoBoton.setString(texto);
    boton.textoBoton.setCharacterSize(20);
    boton.textoBoton.setFillColor(sf::Color::White);

    float textWidth = boton.textoBoton.getGlobalBounds().width;
    boton.textoBoton.setPosition(posicion.x + (180 - textWidth) / 2, posicion.y + 5);

    boton.callback = callback; 
    botones.push_back(boton);
}

void BotonManager::draw(sf::RenderWindow& window) {
    for (const auto& boton : botones) {
        window.draw(boton.forma);
        window.draw(boton.textoBoton);
    }
}

void BotonManager::manejarEventos(const sf::Event& event, sf::RenderWindow& window) { 
    static sf::Cursor handCursor;
    handCursor.loadFromSystem(sf::Cursor::Hand);

    if (event.type == sf::Event::MouseMoved) {
        for (auto& boton : botones) {
            if (boton.forma.getGlobalBounds().contains(static_cast<float>(event.mouseMove.x), static_cast<float>(event.mouseMove.y))) {
                window.setMouseCursor(handCursor);
            }
        }
    }
    
    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
        for (auto& boton : botones) {
            if (boton.forma.getGlobalBounds().contains(static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y))) {
                boton.callback();
            }
        }
    }
}
