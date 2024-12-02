cmake_minimum_required(VERSION 3.10)

project(SistemaDeTrafico)

set(CMAKE_CXX_STANDARD 17)

# Buscar y configurar SFML
find_package(SFML 2.5 REQUIRED COMPONENTS graphics window system)

# Incluir directorios para SFML
include_directories(${SFML_INCLUDE_DIRS})

# Incluir directorios adicionales
include_directories(/usr/local/include)
include_directories(src src/Ciudad src/Vehiculos src/Interfaz src/Trafico)

# Especificar las rutas para las bibliotecas
link_directories(/usr/local/lib)

# Especificar los archivos fuente
set(SOURCES
    src/main.cpp
    src/Ciudad/Grafo.cpp
    src/Interfaz/BotonManager.cpp
    src/Vehiculos/Carro.cpp
    src/Interfaz/Interfaz.cpp
    src/Ciudad/Nodo.cpp
    src/Ciudad/Semaforo.cpp
    src/Vehiculos/Vehiculo.cpp
    src/Vehiculos/Colisionador.cpp
    src/Trafico/ArbolSemaforos.cpp
)

# Crear el ejecutable
add_executable(TrafficSimulation ${SOURCES})

# Enlazar con las bibliotecas de SFML y Thor
target_link_libraries(TrafficSimulation 
    sfml-graphics 
    sfml-window 
    sfml-system 
)