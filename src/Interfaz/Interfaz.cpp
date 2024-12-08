#include "Interfaz.h"
#include "Carro.h"
#include "Vehiculo.h"
#include "CarroEspecial.h"
#include <iostream>
#include <cmath>
#include <ctime>
#include <iomanip>
#include <utility>
#include <set>
#include <algorithm>
#include <random>
#include <sstream>
#include <thread>
#include <chrono>
#include <cstdlib> 

Interfaz::Interfaz(const sf::Font& fuente, Grafo& grafo)
    : font(fuente), botonManager(fuente), grafo(grafo), espaciado(200.0f), climaActual(SOLEADO), temperatura(25.0f), velocidadClima(1.0f) {

    arbolSemaforos = new ArbolSemaforos();

    if (!imagenClima.loadFromFile("../Resources/Soleado.png")) {
        std::cerr << "Error al cargar la imagen del clima." << std::endl;
    }
    spriteClima.setTexture(imagenClima);

    botonManager.agregarBoton("Calles++", sf::Vector2f(1285, 190), [this]() {
        sf::FloatRect areaValida(50, 50, 1100, 700);
        agregarNodoActivo = true;
        sf::Vector2f posicionInicial(100, 100);
        this->grafo.agregarNodosSecuenciales(espaciado, areaValida, posicionInicial);
    });

    botonManager.agregarBoton("Semaforos++", sf::Vector2f(1285, 250), [this, &grafo]() {
        if (grafo.obtenerCantidadNodos() < 2) {
            mostrarMensajeSemaforos = true;
            return;
        }

        Nodo* nodoRelacionado = grafo.obtenerNodoAlAzar();
        sf::Vector2f posicionNodo = nodoRelacionado->obtenerPosicion();
        std::vector<Nodo*> conexiones = grafo.obtenerConexionesDeNodo(nodoRelacionado);

        if (!conexiones.empty()) {
            static std::set<std::pair<Nodo*, Nodo*>> conexionesUsadas;
            Nodo* nodoConectado = nullptr;
            
            std::random_device rd;
            std::mt19937 g(rd());
            std::shuffle(conexiones.begin(), conexiones.end(), g);

            for (Nodo* nodoCandidato : conexiones) {
                if (conexionesUsadas.find({nodoRelacionado, nodoCandidato}) == conexionesUsadas.end() &&
                    conexionesUsadas.find({nodoCandidato, nodoRelacionado}) == conexionesUsadas.end()) {

                    nodoConectado = nodoCandidato;
                    break;
                }
            }

            if (nodoConectado != nullptr) {
                conexionesUsadas.insert({nodoRelacionado, nodoConectado});
                conexionesUsadas.insert({nodoConectado, nodoRelacionado});

                sf::Vector2f posicionConectada = nodoConectado->obtenerPosicion();
                float direccionX = posicionConectada.x - posicionNodo.x;
                float direccionY = posicionConectada.y - posicionNodo.y;

                float longitud = std::sqrt(direccionX * direccionX + direccionY * direccionY);
                direccionX /= longitud; 
                direccionY /= longitud; 

                float distancia = 25.0f;
                float semaforoX = posicionNodo.x + direccionX * distancia;
                float semaforoY = posicionNodo.y + direccionY * distancia;

                Semaforo* nuevoSemaforo = new Semaforo(30.f, 20.f, 20.f, 20.f, sf::Vector2f(semaforoX, semaforoY), 30.0f);
                
                nodoRelacionado->asignarSemaforo(nuevoSemaforo);
                arbolSemaforos->insertar(nuevoSemaforo, nodoRelacionado, nodoConectado);
            }
        }
    });

    botonManager.agregarBoton("Cerrar Calle", sf::Vector2f(1285, 310), [this, &grafo]() {
        if (grafo.obtenerCantidadNodos() < 4) {
            mostrarMensajeCalles = true;
            return;
        }

        Nodo* nodoRelacionado = grafo.obtenerNodoAlAzar();
        
        if (nodoRelacionado == nullptr) {
            return;
        }
        
        std::vector<Nodo*> conexiones = grafo.obtenerConexionesDeNodo(nodoRelacionado);

        if (conexiones.empty()) {
            return;
        }

        static std::set<std::pair<Nodo*, Nodo*>> conexionesCerradas;
        Nodo* nodoConectado = nullptr;

        std::random_device rd;
        std::mt19937 g(rd());
        std::shuffle(conexiones.begin(), conexiones.end(), g);

        for (Nodo* nodoCandidato : conexiones) {
            if (conexionesCerradas.find({nodoRelacionado, nodoCandidato}) == conexionesCerradas.end() &&
                conexionesCerradas.find({nodoCandidato, nodoRelacionado}) == conexionesCerradas.end()) {
                
                nodoConectado = nodoCandidato;
                break;
            }
        }

        if (nodoRelacionado != nullptr && nodoConectado != nullptr) {
            nodoRelacionado->cerrarCalle();
            nodoConectado->cerrarCalle();

            conexionesCerradas.insert({nodoRelacionado, nodoConectado});
            conexionesCerradas.insert({nodoConectado, nodoRelacionado});

            nodoRelacionado->setColor(sf::Color::Red); 
            nodoConectado->setColor(sf::Color::Red); 

            const int tiempoReapertura = 60;

            std::thread([nodoRelacionado, nodoConectado, tiempoReapertura]() {
                std::this_thread::sleep_for(std::chrono::seconds(tiempoReapertura));

                nodoRelacionado->abrirCalle();
                nodoConectado->abrirCalle();

                nodoRelacionado->setColor(sf::Color::White); 
                nodoConectado->setColor(sf::Color::White); 

                static std::set<std::pair<Nodo*, Nodo*>> conexionesCerradas;
                conexionesCerradas.erase({nodoRelacionado, nodoConectado});
                conexionesCerradas.erase({nodoConectado, nodoRelacionado});
            }).detach();
        }
    });

    botonManager.agregarBoton("Carros++", sf::Vector2f(1285, 420), [this, &grafo]() {
        if (grafo.obtenerCantidadNodos() == 0) {
            mostrarMensajeGrafoVacio = true;
            return;
        }

        static int index = 0;

        std::string nodoInicio = grafo.obtenerNodoAleatorio();
        sf::Vector2f posicionNodo = grafo.obtenerPosicionNodo(nodoInicio);

        bool posicionValida = true;
        for (auto& carro : vehiculos) {
            if (std::sqrt(std::pow(carro->obtenerPosicion().x - posicionNodo.x, 2) + 
                        std::pow(carro->obtenerPosicion().y - posicionNodo.y, 2)) < 50) {
                posicionValida = false;
                break;
            }
        }

        if (!posicionValida) {
            nodoInicio = grafo.obtenerNodoAleatorio();
            posicionNodo = grafo.obtenerPosicionNodo(nodoInicio);
        }

        Carro carro("Carro_" + std::to_string(index), posicionNodo, 50.0f, grafo, "../Resources/Carro.png", {}, grafo.getNodosSemaforos());
        std::vector<sf::Vector2f> rutaCiclica = carro.generarRutaCiclicaSinNodoPrevio(grafo, nodoInicio, 5, "");

        for (size_t i = 0; i < rutaCiclica.size() - 1; ++i) {
            sf::Vector2f& nodoActual = rutaCiclica[i];
            sf::Vector2f& nodoSiguiente = rutaCiclica[i + 1];

            if (std::abs(nodoSiguiente.x - nodoActual.x) < std::numeric_limits<float>::epsilon()) {
                if (nodoSiguiente.y > nodoActual.y) {
                    nodoActual.x -= 45.0f;
                    nodoSiguiente.x -= 45.0f;
                } else {
                    nodoActual.x += 5.0f;
                    nodoSiguiente.x += 5.0f;
                }
            } else if (std::abs(nodoSiguiente.y - nodoActual.y) < std::numeric_limits<float>::epsilon()) {
                if (nodoSiguiente.x > nodoActual.x) {
                    nodoActual.y += 5.0f;
                    nodoSiguiente.y += 5.0f;
                } else {
                    nodoActual.y -= 30.0f;
                    nodoSiguiente.y -= 30.0f;
                }
            }
        }

        Carro* nuevoCarro = new Carro(
            "Carro_" + std::to_string(index),
            posicionNodo,
            5.0f,
            grafo,
            "../Resources/Carro.png",
            rutaCiclica,
            grafo.getNodosSemaforos()
        );

        nuevoCarro->cargarSemaforos(obtenerArbolSemaforos());
        vehiculos.push_back(nuevoCarro);
        index++;
    });

    botonManager.agregarBoton("C. Especiales++", sf::Vector2f(1285, 480), [this, &grafo]() {
        if (grafo.obtenerCantidadNodos() == 0) {
            mostrarMensajeGrafoVacio = true;
            return;
        }

        static int index = 0;

        std::string nodoInicio = grafo.obtenerNodoAleatorio();
        sf::Vector2f posicionNodo = grafo.obtenerPosicionNodo(nodoInicio);

        bool posicionValida = true;
        for (auto& carro : vehiculos) {
            if (std::sqrt(std::pow(carro->obtenerPosicion().x - posicionNodo.x, 2) + 
                        std::pow(carro->obtenerPosicion().y - posicionNodo.y, 2)) < 50) {
                posicionValida = false;
                break;
            }
        }

        if (!posicionValida) {
            nodoInicio = grafo.obtenerNodoAleatorio();
            posicionNodo = grafo.obtenerPosicionNodo(nodoInicio);
        }

        int tipoCarro = rand() % 3 + 1;
        std::string imagenCarro;

        switch (tipoCarro) {
            case 1:
                imagenCarro = "../Resources/ambulancia.png";
                break;
            case 2:
                imagenCarro = "../Resources/fireTruck.png";
                break;
            case 3:
                imagenCarro = "../Resources/police.png";
                break;
        }

        CarroEspecial* carroEspecial = new CarroEspecial(
            "CarroEspecial_" + std::to_string(index),
            posicionNodo,
            50.0f,
            grafo,
            imagenCarro,
            {}
        );

        std::vector<sf::Vector2f> rutaCiclica = carroEspecial->generarRutaCiclicaSinNodoPrevio(grafo, nodoInicio, 5, "");

        for (size_t i = 0; i < rutaCiclica.size() - 1; ++i) {
            sf::Vector2f& nodoActual = rutaCiclica[i];
            sf::Vector2f& nodoSiguiente = rutaCiclica[i + 1];

            if (std::abs(nodoSiguiente.x - nodoActual.x) < std::numeric_limits<float>::epsilon()) {
                if (nodoSiguiente.y > nodoActual.y) {
                    nodoActual.x -= 45.0f;
                    nodoSiguiente.x -= 45.0f;
                } else {
                    nodoActual.x += 5.0f;
                    nodoSiguiente.x += 5.0f;
                }
            } else if (std::abs(nodoSiguiente.y - nodoActual.y) < std::numeric_limits<float>::epsilon()) {
                if (nodoSiguiente.x > nodoActual.x) {
                    nodoActual.y += 5.0f;
                    nodoSiguiente.y += 5.0f;
                } else {
                    nodoActual.y -= 30.0f;
                    nodoSiguiente.y -= 30.0f;
                }
            }
        }

        carroEspecial->definirRuta(rutaCiclica);
        vehiculosEspecial.push_back(carroEspecial);

        index++;
    });

    botonManager.agregarBoton("E. Colisiones", sf::Vector2f(1285, 540), [this]() {
        for (auto it = vehiculos.begin(); it != vehiculos.end(); ) {
            if ((*it)->colisionado) {
                delete *it; 
                it = vehiculos.erase(it); 
            } else {
                ++it; 
            }
        }
    });

    botonManager.agregarBoton("Clima", sf::Vector2f(1285, 650), [this]() {
        cambiarClima();  
    });

    botonManager.agregarBoton("Toggle Etiquetas", sf::Vector2f(1285, 710), [this]() {
        std::cout << "Presionado";
        toggleMostrarEtiquetas(); 
    });
}

void Interfaz::cambiarClima() {
    int climaRandom = rand() % 3;
    
    {
        std::lock_guard<std::mutex> lock(climaMutex);  
        switch (climaRandom) {
            case 0:
                climaActual = SOLEADO;
                temperatura = 25.0f;
                velocidadClima = 14.0f;
                break;
            case 1:
                climaActual = LLUVIA;
                temperatura = 15.0f;
                velocidadClima = 10.7f;
                break;
            case 2:
                climaActual = NIEVE;
                temperatura = -5.0f;
                velocidadClima = 20.0f;
                break;
        }
    }

    std::thread([this]() {
    while (true) {
        std::this_thread::sleep_for(std::chrono::seconds(6));

        {
            std::lock_guard<std::mutex> lock(climaMutex);
            if (climaActual == NIEVE || climaActual == LLUVIA) {
                temperatura += (rand() % 3 - 1);
            }

            if (temperatura < -10.0f) {
                temperatura = -10.0f;
            } else if (temperatura > 35.0f) {
                temperatura = 35.0f;
            }

        }
    }}).detach(); 
}

void Interfaz::crearPanelSuperior(sf::RenderWindow& window) {
    const float alturaPanel = 50.0f;

    sf::RectangleShape panelSuperior(sf::Vector2f(window.getSize().x, alturaPanel));
    panelSuperior.setFillColor(sf::Color(255, 202, 212));
    panelSuperior.setOutlineThickness(2.0f);
    panelSuperior.setOutlineColor(sf::Color::White);
    panelSuperior.setPosition(0, 0);
    window.draw(panelSuperior);

    std::string textoClimaActual;
    float tempActual;
    {
        std::lock_guard<std::mutex> lock(climaMutex); 
        textoClimaActual = obtenerNombreClima(climaActual);
        tempActual = temperatura;
    }

    sf::Text textoClima;
    textoClima.setFont(font);
    std::ostringstream climaTexto;
    climaTexto << "Clima: " << textoClimaActual << ", " << std::fixed << std::setprecision(1) << tempActual << "°C";
    textoClima.setString(climaTexto.str());
    textoClima.setCharacterSize(25);
    textoClima.setFillColor(sf::Color::Black);
    textoClima.setPosition(20.0f, 10.0f);
    window.draw(textoClima);

    dibujarMensajeLimite(window);
    dibujarMensajeGrafoVacio(window);
    dibujarMensajeSemaforo(window);
    dibujarMensajeCalle(window);
    dibujarClima(window);
}

std::string Interfaz::obtenerNombreClima(Clima clima) {
    switch (clima) {
        case SOLEADO: return "Soleado";
        case LLUVIA: return "Lluvia";
        case NIEVE: return "Nieve";
        default: return "Desconocido";
    }
}

void Interfaz::actualizarVelocidadesDeVehiculos() {
    for (auto* carro : vehiculos) {
        carro->actualizarVelocidad(velocidadClima);
    }
}

void Interfaz::crearPanelDerecho(sf::RenderWindow& window) {
    const float panelAncho = 200;
    const float panelSuperiorAltura = 50;
    const float anchoLinea = 150.0f;

    sf::RectangleShape panelDerecho(sf::Vector2f(panelAncho, window.getSize().y - panelSuperiorAltura));
    panelDerecho.setFillColor(sf::Color(255, 202, 212));
    panelDerecho.setOutlineThickness(2.0f);
    panelDerecho.setOutlineColor(sf::Color::White);
    panelDerecho.setPosition(window.getSize().x - panelAncho, panelSuperiorAltura);
    window.draw(panelDerecho);

    // Ciudad
    sf::RectangleShape lineaDivisoria(sf::Vector2f(anchoLinea, 2.0f)); 
    lineaDivisoria.setFillColor(sf::Color::White);
    float posicionX = window.getSize().x - panelAncho + (panelAncho - anchoLinea) / 2;
    lineaDivisoria.setPosition(posicionX, panelSuperiorAltura + 120);
    window.draw(lineaDivisoria);

    // Carros
    sf::RectangleShape lineaDivisoria2(sf::Vector2f(anchoLinea, 2.0f)); 
    lineaDivisoria2.setFillColor(sf::Color::White);
    lineaDivisoria2.setPosition(posicionX, panelSuperiorAltura + 350);
    window.draw(lineaDivisoria2);

    // Otros
    sf::RectangleShape lineaDivisoria3(sf::Vector2f(anchoLinea, 2.0f)); 
    lineaDivisoria3.setFillColor(sf::Color::White);
    lineaDivisoria3.setPosition(posicionX, panelSuperiorAltura + 580);
    window.draw(lineaDivisoria3);

    sf::Font fontMenu;
    if (!fontMenu.loadFromFile("../Resources/Lobster-Regular.ttf")) {
        return;
    }

    // Menú
    sf::Text menuTitle;
    menuTitle.setFont(fontMenu);
    menuTitle.setString("MENU");
    menuTitle.setCharacterSize(50);
    menuTitle.setFillColor(sf::Color::White);

    // Apartado Ciudad
    sf::Text ciudadTitle;
    ciudadTitle.setFont(fontMenu);
    ciudadTitle.setString("Ciudad");
    ciudadTitle.setCharacterSize(20);
    ciudadTitle.setFillColor(sf::Color::White);

    // Apartado Carros
    sf::Text carrosTitle;
    carrosTitle.setFont(fontMenu);
    carrosTitle.setString("Carros");
    carrosTitle.setCharacterSize(20);
    carrosTitle.setFillColor(sf::Color::White);

    // Apartado Otros
    sf::Text otrosTitle;
    otrosTitle.setFont(fontMenu);
    otrosTitle.setString("Otros");
    otrosTitle.setCharacterSize(20);
    otrosTitle.setFillColor(sf::Color::White);

    // Menú title
    float titleWidth = menuTitle.getGlobalBounds().width;
    menuTitle.setPosition(window.getSize().x - panelAncho + (panelAncho - titleWidth) / 2, panelSuperiorAltura + 10);
    window.draw(menuTitle);

    // Ciudad title (centrado)
    float ciudadWidth = ciudadTitle.getGlobalBounds().width;
    ciudadTitle.setPosition(window.getSize().x - panelAncho + (panelAncho - ciudadWidth) / 2, panelSuperiorAltura + 90);
    window.draw(ciudadTitle);

    // Ciudad Carros (centrado)
    float carrosWidth = carrosTitle.getGlobalBounds().width;
    carrosTitle.setPosition(window.getSize().x - panelAncho + (panelAncho - carrosWidth) / 2, panelSuperiorAltura + 320);
    window.draw(carrosTitle);

    // Ciudad Otros (centrado)
    float otrosWidth = otrosTitle.getGlobalBounds().width;
    otrosTitle.setPosition(window.getSize().x - panelAncho + (panelAncho - otrosWidth) / 2, panelSuperiorAltura + 550);
    window.draw(otrosTitle);

    botonManager.draw(window);
}

void Interfaz::dibujarMensajeLimite(sf::RenderWindow& window) {
    if (mostrarMensajeLimite) {
        sf::Font fontMenu;
        if (!fontMenu.loadFromFile("../Resources/Lobster-Regular.ttf")) {
            return;
        }

        sf::Text mensajeLimite("Limite de nodos alcanzado", fontMenu, 25);
        mensajeLimite.setFillColor(sf::Color::Black);

        float mensajeX = window.getSize().x - 300.0f;
        float mensajeY = 10.0f; 
        mensajeLimite.setPosition(mensajeX, mensajeY);

        window.draw(mensajeLimite);

        if (mensajeReloj.getElapsedTime().asSeconds() >= tiempoMensajeVisible) {
            mostrarMensajeLimite = false;
        }
    }
}

void Interfaz::dibujarMensajeGrafoVacio(sf::RenderWindow& window) {
    if (mostrarMensajeGrafoVacio) {
        sf::Font fontMenu;
        if (!fontMenu.loadFromFile("../Resources/Lobster-Regular.ttf")) {
            return;
        }
        sf::Text mensajeGrafoVacio("No se pueden agregar carros, el grafo esta vacio", fontMenu, 25);
        mensajeGrafoVacio.setFillColor(sf::Color::Black);

        float mensajeX = window.getSize().x - 490.0f;
        float mensajeY = 10.0f; 
        mensajeGrafoVacio.setPosition(mensajeX, mensajeY);

        window.draw(mensajeGrafoVacio);

        if (mensajeReloj.getElapsedTime().asSeconds() >= tiempoMensajeVisible) {
            mostrarMensajeGrafoVacio = false;
        }
    }
}

void Interfaz::dibujarMensajeSemaforo(sf::RenderWindow& window) {
    if (mostrarMensajeSemaforos) {
        sf::Font fontMenu;
        if (!fontMenu.loadFromFile("../Resources/Lobster-Regular.ttf")) {
            return;
        }
        sf::Text mensajeGrafoVacio("Agrega mas calles para poder generar un semaforo", fontMenu, 25);
        mensajeGrafoVacio.setFillColor(sf::Color::Black);

        float mensajeX = window.getSize().x - 550.0f;
        float mensajeY = 10.0f; 
        mensajeGrafoVacio.setPosition(mensajeX, mensajeY);

        window.draw(mensajeGrafoVacio);

        if (mensajeReloj.getElapsedTime().asSeconds() >= tiempoMensajeVisible) {
            mostrarMensajeSemaforos = false;
        }
    }
}

void Interfaz::dibujarMensajeCalle(sf::RenderWindow& window) {
    if (mostrarMensajeCalles) {
        sf::Font fontMenu;
        if (!fontMenu.loadFromFile("../Resources/Lobster-Regular.ttf")) {
            return;
        }
        sf::Text mensajeGrafoVacio("Necesitas mas calles para poder cerrar una calle", fontMenu, 25);
        mensajeGrafoVacio.setFillColor(sf::Color::Black);

        float mensajeX = window.getSize().x - 540.0f;
        float mensajeY = 10.0f; 
        mensajeGrafoVacio.setPosition(mensajeX, mensajeY);

        window.draw(mensajeGrafoVacio);

        if (mensajeReloj.getElapsedTime().asSeconds() >= tiempoMensajeVisible) {
            mostrarMensajeCalles = false;
        }
    }
}

void Interfaz::manejarEventos(const sf::Event& event, sf::RenderWindow& window) {
    botonManager.manejarEventos(event, window);
}

bool Interfaz::isMostrarEtiquetas() const {
    return mostrarEtiquetas;
}

void Interfaz::toggleMostrarEtiquetas() {
    mostrarEtiquetas = !mostrarEtiquetas; 
}

std::vector<Carro*>& Interfaz::obtenerVehiculos() {
    return vehiculos; 
}

std::vector<CarroEspecial*>& Interfaz::obtenerVehiculosEspeciales() {
    return vehiculosEspecial;
}

void Interfaz::setMostrarMensajeLimite(bool estatus) {
    mostrarMensajeLimite = estatus;
    if (mostrarMensajeLimite) {
        mensajeReloj.restart();
    }
}

bool Interfaz::getMostrarMensajeLimite() const {
    return mostrarMensajeLimite;
}

Interfaz::~Interfaz() {
    vehiculos.clear();
}

void Interfaz::dibujarSemaforos(sf::RenderWindow& window) {
    arbolSemaforos->dibujarSemaforos(window); 
}

void Interfaz::actualizarSemaforos(float deltaTime) {
    arbolSemaforos->actualizarSemaforos(deltaTime);
}

ArbolSemaforos* Interfaz::obtenerArbolSemaforos() {
    return arbolSemaforos;
}

float Interfaz::obtenerVelocidadClima() const {
    return velocidadClima;
}

void Interfaz::dibujarClima(sf::RenderWindow& ventana) {
    std::string climaString;
    sf::Vector2f posicionClima;
    switch (climaActual) {
        case SOLEADO:
            climaString = "Soleado"; 
            posicionClima = sf::Vector2f(250, 1);
            break;
        case LLUVIA:
            climaString = "Lluvia"; 
            posicionClima = sf::Vector2f(230, 1);
            break;
        case NIEVE:
            climaString = "Nieve";  
            posicionClima = sf::Vector2f(220, 1);
            break;
        default:
            std::cerr << "Estado de clima no reconocido" << std::endl;
            return;
    }

    gestorImagenes.dibujarImagen(climaString, ventana, posicionClima, 0.05f, 0.05f);
}
