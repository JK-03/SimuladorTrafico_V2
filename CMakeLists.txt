cmake_minimum_required(VERSION 3.10)

project(SistemaDeTrafico)

set(CMAKE_CXX_STANDARD 17)

find_package(SFML 2.5 REQUIRED graphics window system)

include_directories(${SFML_INCLUDE_DIR})

include_directories(src src/Ciudad src/Vehiculos src/Interfaz)

set(SOURCES
    src/main.cpp
    src/Ciudad/Grafo.cpp
    src/Interfaz/BotonManager.cpp
    src/Vehiculos/Carro.cpp
    src/Interfaz/Interfaz.cpp
    src/Ciudad/Nodo.cpp
    src/Vehiculos/Ruta.cpp
    src/Ciudad/Semaforo.cpp
    src/Vehiculos/Vehiculo.cpp
)

add_executable(TrafficSimulation ${SOURCES})

target_link_libraries(TrafficSimulation sfml-graphics sfml-window sfml-system)