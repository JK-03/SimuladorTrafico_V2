# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.31

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /opt/homebrew/bin/cmake

# The command to remove a file.
RM = /opt/homebrew/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/Users/jenniferbueso/Library/CloudStorage/OneDrive-Personal/Documents/Estructura de Datos I/SistemaDeTrafico"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/Users/jenniferbueso/Library/CloudStorage/OneDrive-Personal/Documents/Estructura de Datos I/SistemaDeTrafico/build"

# Include any dependencies generated for this target.
include CMakeFiles/TrafficSimulation.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/TrafficSimulation.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/TrafficSimulation.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/TrafficSimulation.dir/flags.make

CMakeFiles/TrafficSimulation.dir/codegen:
.PHONY : CMakeFiles/TrafficSimulation.dir/codegen

CMakeFiles/TrafficSimulation.dir/src/main.cpp.o: CMakeFiles/TrafficSimulation.dir/flags.make
CMakeFiles/TrafficSimulation.dir/src/main.cpp.o: /Users/jenniferbueso/Library/CloudStorage/OneDrive-Personal/Documents/Estructura\ de\ Datos\ I/SistemaDeTrafico/src/main.cpp
CMakeFiles/TrafficSimulation.dir/src/main.cpp.o: CMakeFiles/TrafficSimulation.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir="/Users/jenniferbueso/Library/CloudStorage/OneDrive-Personal/Documents/Estructura de Datos I/SistemaDeTrafico/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/TrafficSimulation.dir/src/main.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/TrafficSimulation.dir/src/main.cpp.o -MF CMakeFiles/TrafficSimulation.dir/src/main.cpp.o.d -o CMakeFiles/TrafficSimulation.dir/src/main.cpp.o -c "/Users/jenniferbueso/Library/CloudStorage/OneDrive-Personal/Documents/Estructura de Datos I/SistemaDeTrafico/src/main.cpp"

CMakeFiles/TrafficSimulation.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/TrafficSimulation.dir/src/main.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/Users/jenniferbueso/Library/CloudStorage/OneDrive-Personal/Documents/Estructura de Datos I/SistemaDeTrafico/src/main.cpp" > CMakeFiles/TrafficSimulation.dir/src/main.cpp.i

CMakeFiles/TrafficSimulation.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/TrafficSimulation.dir/src/main.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/Users/jenniferbueso/Library/CloudStorage/OneDrive-Personal/Documents/Estructura de Datos I/SistemaDeTrafico/src/main.cpp" -o CMakeFiles/TrafficSimulation.dir/src/main.cpp.s

CMakeFiles/TrafficSimulation.dir/src/Ciudad/Grafo.cpp.o: CMakeFiles/TrafficSimulation.dir/flags.make
CMakeFiles/TrafficSimulation.dir/src/Ciudad/Grafo.cpp.o: /Users/jenniferbueso/Library/CloudStorage/OneDrive-Personal/Documents/Estructura\ de\ Datos\ I/SistemaDeTrafico/src/Ciudad/Grafo.cpp
CMakeFiles/TrafficSimulation.dir/src/Ciudad/Grafo.cpp.o: CMakeFiles/TrafficSimulation.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir="/Users/jenniferbueso/Library/CloudStorage/OneDrive-Personal/Documents/Estructura de Datos I/SistemaDeTrafico/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/TrafficSimulation.dir/src/Ciudad/Grafo.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/TrafficSimulation.dir/src/Ciudad/Grafo.cpp.o -MF CMakeFiles/TrafficSimulation.dir/src/Ciudad/Grafo.cpp.o.d -o CMakeFiles/TrafficSimulation.dir/src/Ciudad/Grafo.cpp.o -c "/Users/jenniferbueso/Library/CloudStorage/OneDrive-Personal/Documents/Estructura de Datos I/SistemaDeTrafico/src/Ciudad/Grafo.cpp"

CMakeFiles/TrafficSimulation.dir/src/Ciudad/Grafo.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/TrafficSimulation.dir/src/Ciudad/Grafo.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/Users/jenniferbueso/Library/CloudStorage/OneDrive-Personal/Documents/Estructura de Datos I/SistemaDeTrafico/src/Ciudad/Grafo.cpp" > CMakeFiles/TrafficSimulation.dir/src/Ciudad/Grafo.cpp.i

CMakeFiles/TrafficSimulation.dir/src/Ciudad/Grafo.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/TrafficSimulation.dir/src/Ciudad/Grafo.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/Users/jenniferbueso/Library/CloudStorage/OneDrive-Personal/Documents/Estructura de Datos I/SistemaDeTrafico/src/Ciudad/Grafo.cpp" -o CMakeFiles/TrafficSimulation.dir/src/Ciudad/Grafo.cpp.s

CMakeFiles/TrafficSimulation.dir/src/Interfaz/BotonManager.cpp.o: CMakeFiles/TrafficSimulation.dir/flags.make
CMakeFiles/TrafficSimulation.dir/src/Interfaz/BotonManager.cpp.o: /Users/jenniferbueso/Library/CloudStorage/OneDrive-Personal/Documents/Estructura\ de\ Datos\ I/SistemaDeTrafico/src/Interfaz/BotonManager.cpp
CMakeFiles/TrafficSimulation.dir/src/Interfaz/BotonManager.cpp.o: CMakeFiles/TrafficSimulation.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir="/Users/jenniferbueso/Library/CloudStorage/OneDrive-Personal/Documents/Estructura de Datos I/SistemaDeTrafico/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/TrafficSimulation.dir/src/Interfaz/BotonManager.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/TrafficSimulation.dir/src/Interfaz/BotonManager.cpp.o -MF CMakeFiles/TrafficSimulation.dir/src/Interfaz/BotonManager.cpp.o.d -o CMakeFiles/TrafficSimulation.dir/src/Interfaz/BotonManager.cpp.o -c "/Users/jenniferbueso/Library/CloudStorage/OneDrive-Personal/Documents/Estructura de Datos I/SistemaDeTrafico/src/Interfaz/BotonManager.cpp"

CMakeFiles/TrafficSimulation.dir/src/Interfaz/BotonManager.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/TrafficSimulation.dir/src/Interfaz/BotonManager.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/Users/jenniferbueso/Library/CloudStorage/OneDrive-Personal/Documents/Estructura de Datos I/SistemaDeTrafico/src/Interfaz/BotonManager.cpp" > CMakeFiles/TrafficSimulation.dir/src/Interfaz/BotonManager.cpp.i

CMakeFiles/TrafficSimulation.dir/src/Interfaz/BotonManager.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/TrafficSimulation.dir/src/Interfaz/BotonManager.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/Users/jenniferbueso/Library/CloudStorage/OneDrive-Personal/Documents/Estructura de Datos I/SistemaDeTrafico/src/Interfaz/BotonManager.cpp" -o CMakeFiles/TrafficSimulation.dir/src/Interfaz/BotonManager.cpp.s

CMakeFiles/TrafficSimulation.dir/src/Vehiculos/Carro.cpp.o: CMakeFiles/TrafficSimulation.dir/flags.make
CMakeFiles/TrafficSimulation.dir/src/Vehiculos/Carro.cpp.o: /Users/jenniferbueso/Library/CloudStorage/OneDrive-Personal/Documents/Estructura\ de\ Datos\ I/SistemaDeTrafico/src/Vehiculos/Carro.cpp
CMakeFiles/TrafficSimulation.dir/src/Vehiculos/Carro.cpp.o: CMakeFiles/TrafficSimulation.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir="/Users/jenniferbueso/Library/CloudStorage/OneDrive-Personal/Documents/Estructura de Datos I/SistemaDeTrafico/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/TrafficSimulation.dir/src/Vehiculos/Carro.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/TrafficSimulation.dir/src/Vehiculos/Carro.cpp.o -MF CMakeFiles/TrafficSimulation.dir/src/Vehiculos/Carro.cpp.o.d -o CMakeFiles/TrafficSimulation.dir/src/Vehiculos/Carro.cpp.o -c "/Users/jenniferbueso/Library/CloudStorage/OneDrive-Personal/Documents/Estructura de Datos I/SistemaDeTrafico/src/Vehiculos/Carro.cpp"

CMakeFiles/TrafficSimulation.dir/src/Vehiculos/Carro.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/TrafficSimulation.dir/src/Vehiculos/Carro.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/Users/jenniferbueso/Library/CloudStorage/OneDrive-Personal/Documents/Estructura de Datos I/SistemaDeTrafico/src/Vehiculos/Carro.cpp" > CMakeFiles/TrafficSimulation.dir/src/Vehiculos/Carro.cpp.i

CMakeFiles/TrafficSimulation.dir/src/Vehiculos/Carro.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/TrafficSimulation.dir/src/Vehiculos/Carro.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/Users/jenniferbueso/Library/CloudStorage/OneDrive-Personal/Documents/Estructura de Datos I/SistemaDeTrafico/src/Vehiculos/Carro.cpp" -o CMakeFiles/TrafficSimulation.dir/src/Vehiculos/Carro.cpp.s

CMakeFiles/TrafficSimulation.dir/src/Interfaz/Interfaz.cpp.o: CMakeFiles/TrafficSimulation.dir/flags.make
CMakeFiles/TrafficSimulation.dir/src/Interfaz/Interfaz.cpp.o: /Users/jenniferbueso/Library/CloudStorage/OneDrive-Personal/Documents/Estructura\ de\ Datos\ I/SistemaDeTrafico/src/Interfaz/Interfaz.cpp
CMakeFiles/TrafficSimulation.dir/src/Interfaz/Interfaz.cpp.o: CMakeFiles/TrafficSimulation.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir="/Users/jenniferbueso/Library/CloudStorage/OneDrive-Personal/Documents/Estructura de Datos I/SistemaDeTrafico/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/TrafficSimulation.dir/src/Interfaz/Interfaz.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/TrafficSimulation.dir/src/Interfaz/Interfaz.cpp.o -MF CMakeFiles/TrafficSimulation.dir/src/Interfaz/Interfaz.cpp.o.d -o CMakeFiles/TrafficSimulation.dir/src/Interfaz/Interfaz.cpp.o -c "/Users/jenniferbueso/Library/CloudStorage/OneDrive-Personal/Documents/Estructura de Datos I/SistemaDeTrafico/src/Interfaz/Interfaz.cpp"

CMakeFiles/TrafficSimulation.dir/src/Interfaz/Interfaz.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/TrafficSimulation.dir/src/Interfaz/Interfaz.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/Users/jenniferbueso/Library/CloudStorage/OneDrive-Personal/Documents/Estructura de Datos I/SistemaDeTrafico/src/Interfaz/Interfaz.cpp" > CMakeFiles/TrafficSimulation.dir/src/Interfaz/Interfaz.cpp.i

CMakeFiles/TrafficSimulation.dir/src/Interfaz/Interfaz.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/TrafficSimulation.dir/src/Interfaz/Interfaz.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/Users/jenniferbueso/Library/CloudStorage/OneDrive-Personal/Documents/Estructura de Datos I/SistemaDeTrafico/src/Interfaz/Interfaz.cpp" -o CMakeFiles/TrafficSimulation.dir/src/Interfaz/Interfaz.cpp.s

CMakeFiles/TrafficSimulation.dir/src/Ciudad/Nodo.cpp.o: CMakeFiles/TrafficSimulation.dir/flags.make
CMakeFiles/TrafficSimulation.dir/src/Ciudad/Nodo.cpp.o: /Users/jenniferbueso/Library/CloudStorage/OneDrive-Personal/Documents/Estructura\ de\ Datos\ I/SistemaDeTrafico/src/Ciudad/Nodo.cpp
CMakeFiles/TrafficSimulation.dir/src/Ciudad/Nodo.cpp.o: CMakeFiles/TrafficSimulation.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir="/Users/jenniferbueso/Library/CloudStorage/OneDrive-Personal/Documents/Estructura de Datos I/SistemaDeTrafico/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/TrafficSimulation.dir/src/Ciudad/Nodo.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/TrafficSimulation.dir/src/Ciudad/Nodo.cpp.o -MF CMakeFiles/TrafficSimulation.dir/src/Ciudad/Nodo.cpp.o.d -o CMakeFiles/TrafficSimulation.dir/src/Ciudad/Nodo.cpp.o -c "/Users/jenniferbueso/Library/CloudStorage/OneDrive-Personal/Documents/Estructura de Datos I/SistemaDeTrafico/src/Ciudad/Nodo.cpp"

CMakeFiles/TrafficSimulation.dir/src/Ciudad/Nodo.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/TrafficSimulation.dir/src/Ciudad/Nodo.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/Users/jenniferbueso/Library/CloudStorage/OneDrive-Personal/Documents/Estructura de Datos I/SistemaDeTrafico/src/Ciudad/Nodo.cpp" > CMakeFiles/TrafficSimulation.dir/src/Ciudad/Nodo.cpp.i

CMakeFiles/TrafficSimulation.dir/src/Ciudad/Nodo.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/TrafficSimulation.dir/src/Ciudad/Nodo.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/Users/jenniferbueso/Library/CloudStorage/OneDrive-Personal/Documents/Estructura de Datos I/SistemaDeTrafico/src/Ciudad/Nodo.cpp" -o CMakeFiles/TrafficSimulation.dir/src/Ciudad/Nodo.cpp.s

CMakeFiles/TrafficSimulation.dir/src/Ciudad/Semaforo.cpp.o: CMakeFiles/TrafficSimulation.dir/flags.make
CMakeFiles/TrafficSimulation.dir/src/Ciudad/Semaforo.cpp.o: /Users/jenniferbueso/Library/CloudStorage/OneDrive-Personal/Documents/Estructura\ de\ Datos\ I/SistemaDeTrafico/src/Ciudad/Semaforo.cpp
CMakeFiles/TrafficSimulation.dir/src/Ciudad/Semaforo.cpp.o: CMakeFiles/TrafficSimulation.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir="/Users/jenniferbueso/Library/CloudStorage/OneDrive-Personal/Documents/Estructura de Datos I/SistemaDeTrafico/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/TrafficSimulation.dir/src/Ciudad/Semaforo.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/TrafficSimulation.dir/src/Ciudad/Semaforo.cpp.o -MF CMakeFiles/TrafficSimulation.dir/src/Ciudad/Semaforo.cpp.o.d -o CMakeFiles/TrafficSimulation.dir/src/Ciudad/Semaforo.cpp.o -c "/Users/jenniferbueso/Library/CloudStorage/OneDrive-Personal/Documents/Estructura de Datos I/SistemaDeTrafico/src/Ciudad/Semaforo.cpp"

CMakeFiles/TrafficSimulation.dir/src/Ciudad/Semaforo.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/TrafficSimulation.dir/src/Ciudad/Semaforo.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/Users/jenniferbueso/Library/CloudStorage/OneDrive-Personal/Documents/Estructura de Datos I/SistemaDeTrafico/src/Ciudad/Semaforo.cpp" > CMakeFiles/TrafficSimulation.dir/src/Ciudad/Semaforo.cpp.i

CMakeFiles/TrafficSimulation.dir/src/Ciudad/Semaforo.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/TrafficSimulation.dir/src/Ciudad/Semaforo.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/Users/jenniferbueso/Library/CloudStorage/OneDrive-Personal/Documents/Estructura de Datos I/SistemaDeTrafico/src/Ciudad/Semaforo.cpp" -o CMakeFiles/TrafficSimulation.dir/src/Ciudad/Semaforo.cpp.s

CMakeFiles/TrafficSimulation.dir/src/Vehiculos/Vehiculo.cpp.o: CMakeFiles/TrafficSimulation.dir/flags.make
CMakeFiles/TrafficSimulation.dir/src/Vehiculos/Vehiculo.cpp.o: /Users/jenniferbueso/Library/CloudStorage/OneDrive-Personal/Documents/Estructura\ de\ Datos\ I/SistemaDeTrafico/src/Vehiculos/Vehiculo.cpp
CMakeFiles/TrafficSimulation.dir/src/Vehiculos/Vehiculo.cpp.o: CMakeFiles/TrafficSimulation.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir="/Users/jenniferbueso/Library/CloudStorage/OneDrive-Personal/Documents/Estructura de Datos I/SistemaDeTrafico/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/TrafficSimulation.dir/src/Vehiculos/Vehiculo.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/TrafficSimulation.dir/src/Vehiculos/Vehiculo.cpp.o -MF CMakeFiles/TrafficSimulation.dir/src/Vehiculos/Vehiculo.cpp.o.d -o CMakeFiles/TrafficSimulation.dir/src/Vehiculos/Vehiculo.cpp.o -c "/Users/jenniferbueso/Library/CloudStorage/OneDrive-Personal/Documents/Estructura de Datos I/SistemaDeTrafico/src/Vehiculos/Vehiculo.cpp"

CMakeFiles/TrafficSimulation.dir/src/Vehiculos/Vehiculo.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/TrafficSimulation.dir/src/Vehiculos/Vehiculo.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/Users/jenniferbueso/Library/CloudStorage/OneDrive-Personal/Documents/Estructura de Datos I/SistemaDeTrafico/src/Vehiculos/Vehiculo.cpp" > CMakeFiles/TrafficSimulation.dir/src/Vehiculos/Vehiculo.cpp.i

CMakeFiles/TrafficSimulation.dir/src/Vehiculos/Vehiculo.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/TrafficSimulation.dir/src/Vehiculos/Vehiculo.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/Users/jenniferbueso/Library/CloudStorage/OneDrive-Personal/Documents/Estructura de Datos I/SistemaDeTrafico/src/Vehiculos/Vehiculo.cpp" -o CMakeFiles/TrafficSimulation.dir/src/Vehiculos/Vehiculo.cpp.s

CMakeFiles/TrafficSimulation.dir/src/Vehiculos/Colisionador.cpp.o: CMakeFiles/TrafficSimulation.dir/flags.make
CMakeFiles/TrafficSimulation.dir/src/Vehiculos/Colisionador.cpp.o: /Users/jenniferbueso/Library/CloudStorage/OneDrive-Personal/Documents/Estructura\ de\ Datos\ I/SistemaDeTrafico/src/Vehiculos/Colisionador.cpp
CMakeFiles/TrafficSimulation.dir/src/Vehiculos/Colisionador.cpp.o: CMakeFiles/TrafficSimulation.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir="/Users/jenniferbueso/Library/CloudStorage/OneDrive-Personal/Documents/Estructura de Datos I/SistemaDeTrafico/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object CMakeFiles/TrafficSimulation.dir/src/Vehiculos/Colisionador.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/TrafficSimulation.dir/src/Vehiculos/Colisionador.cpp.o -MF CMakeFiles/TrafficSimulation.dir/src/Vehiculos/Colisionador.cpp.o.d -o CMakeFiles/TrafficSimulation.dir/src/Vehiculos/Colisionador.cpp.o -c "/Users/jenniferbueso/Library/CloudStorage/OneDrive-Personal/Documents/Estructura de Datos I/SistemaDeTrafico/src/Vehiculos/Colisionador.cpp"

CMakeFiles/TrafficSimulation.dir/src/Vehiculos/Colisionador.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/TrafficSimulation.dir/src/Vehiculos/Colisionador.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/Users/jenniferbueso/Library/CloudStorage/OneDrive-Personal/Documents/Estructura de Datos I/SistemaDeTrafico/src/Vehiculos/Colisionador.cpp" > CMakeFiles/TrafficSimulation.dir/src/Vehiculos/Colisionador.cpp.i

CMakeFiles/TrafficSimulation.dir/src/Vehiculos/Colisionador.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/TrafficSimulation.dir/src/Vehiculos/Colisionador.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/Users/jenniferbueso/Library/CloudStorage/OneDrive-Personal/Documents/Estructura de Datos I/SistemaDeTrafico/src/Vehiculos/Colisionador.cpp" -o CMakeFiles/TrafficSimulation.dir/src/Vehiculos/Colisionador.cpp.s

CMakeFiles/TrafficSimulation.dir/src/Trafico/ArbolSemaforos.cpp.o: CMakeFiles/TrafficSimulation.dir/flags.make
CMakeFiles/TrafficSimulation.dir/src/Trafico/ArbolSemaforos.cpp.o: /Users/jenniferbueso/Library/CloudStorage/OneDrive-Personal/Documents/Estructura\ de\ Datos\ I/SistemaDeTrafico/src/Trafico/ArbolSemaforos.cpp
CMakeFiles/TrafficSimulation.dir/src/Trafico/ArbolSemaforos.cpp.o: CMakeFiles/TrafficSimulation.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir="/Users/jenniferbueso/Library/CloudStorage/OneDrive-Personal/Documents/Estructura de Datos I/SistemaDeTrafico/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_10) "Building CXX object CMakeFiles/TrafficSimulation.dir/src/Trafico/ArbolSemaforos.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/TrafficSimulation.dir/src/Trafico/ArbolSemaforos.cpp.o -MF CMakeFiles/TrafficSimulation.dir/src/Trafico/ArbolSemaforos.cpp.o.d -o CMakeFiles/TrafficSimulation.dir/src/Trafico/ArbolSemaforos.cpp.o -c "/Users/jenniferbueso/Library/CloudStorage/OneDrive-Personal/Documents/Estructura de Datos I/SistemaDeTrafico/src/Trafico/ArbolSemaforos.cpp"

CMakeFiles/TrafficSimulation.dir/src/Trafico/ArbolSemaforos.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/TrafficSimulation.dir/src/Trafico/ArbolSemaforos.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/Users/jenniferbueso/Library/CloudStorage/OneDrive-Personal/Documents/Estructura de Datos I/SistemaDeTrafico/src/Trafico/ArbolSemaforos.cpp" > CMakeFiles/TrafficSimulation.dir/src/Trafico/ArbolSemaforos.cpp.i

CMakeFiles/TrafficSimulation.dir/src/Trafico/ArbolSemaforos.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/TrafficSimulation.dir/src/Trafico/ArbolSemaforos.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/Users/jenniferbueso/Library/CloudStorage/OneDrive-Personal/Documents/Estructura de Datos I/SistemaDeTrafico/src/Trafico/ArbolSemaforos.cpp" -o CMakeFiles/TrafficSimulation.dir/src/Trafico/ArbolSemaforos.cpp.s

# Object files for target TrafficSimulation
TrafficSimulation_OBJECTS = \
"CMakeFiles/TrafficSimulation.dir/src/main.cpp.o" \
"CMakeFiles/TrafficSimulation.dir/src/Ciudad/Grafo.cpp.o" \
"CMakeFiles/TrafficSimulation.dir/src/Interfaz/BotonManager.cpp.o" \
"CMakeFiles/TrafficSimulation.dir/src/Vehiculos/Carro.cpp.o" \
"CMakeFiles/TrafficSimulation.dir/src/Interfaz/Interfaz.cpp.o" \
"CMakeFiles/TrafficSimulation.dir/src/Ciudad/Nodo.cpp.o" \
"CMakeFiles/TrafficSimulation.dir/src/Ciudad/Semaforo.cpp.o" \
"CMakeFiles/TrafficSimulation.dir/src/Vehiculos/Vehiculo.cpp.o" \
"CMakeFiles/TrafficSimulation.dir/src/Vehiculos/Colisionador.cpp.o" \
"CMakeFiles/TrafficSimulation.dir/src/Trafico/ArbolSemaforos.cpp.o"

# External object files for target TrafficSimulation
TrafficSimulation_EXTERNAL_OBJECTS =

TrafficSimulation: CMakeFiles/TrafficSimulation.dir/src/main.cpp.o
TrafficSimulation: CMakeFiles/TrafficSimulation.dir/src/Ciudad/Grafo.cpp.o
TrafficSimulation: CMakeFiles/TrafficSimulation.dir/src/Interfaz/BotonManager.cpp.o
TrafficSimulation: CMakeFiles/TrafficSimulation.dir/src/Vehiculos/Carro.cpp.o
TrafficSimulation: CMakeFiles/TrafficSimulation.dir/src/Interfaz/Interfaz.cpp.o
TrafficSimulation: CMakeFiles/TrafficSimulation.dir/src/Ciudad/Nodo.cpp.o
TrafficSimulation: CMakeFiles/TrafficSimulation.dir/src/Ciudad/Semaforo.cpp.o
TrafficSimulation: CMakeFiles/TrafficSimulation.dir/src/Vehiculos/Vehiculo.cpp.o
TrafficSimulation: CMakeFiles/TrafficSimulation.dir/src/Vehiculos/Colisionador.cpp.o
TrafficSimulation: CMakeFiles/TrafficSimulation.dir/src/Trafico/ArbolSemaforos.cpp.o
TrafficSimulation: CMakeFiles/TrafficSimulation.dir/build.make
TrafficSimulation: /opt/homebrew/lib/libsfml-graphics.2.6.2.dylib
TrafficSimulation: /opt/homebrew/lib/libsfml-window.2.6.2.dylib
TrafficSimulation: /opt/homebrew/lib/libsfml-system.2.6.2.dylib
TrafficSimulation: CMakeFiles/TrafficSimulation.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir="/Users/jenniferbueso/Library/CloudStorage/OneDrive-Personal/Documents/Estructura de Datos I/SistemaDeTrafico/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_11) "Linking CXX executable TrafficSimulation"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/TrafficSimulation.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/TrafficSimulation.dir/build: TrafficSimulation
.PHONY : CMakeFiles/TrafficSimulation.dir/build

CMakeFiles/TrafficSimulation.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/TrafficSimulation.dir/cmake_clean.cmake
.PHONY : CMakeFiles/TrafficSimulation.dir/clean

CMakeFiles/TrafficSimulation.dir/depend:
	cd "/Users/jenniferbueso/Library/CloudStorage/OneDrive-Personal/Documents/Estructura de Datos I/SistemaDeTrafico/build" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/Users/jenniferbueso/Library/CloudStorage/OneDrive-Personal/Documents/Estructura de Datos I/SistemaDeTrafico" "/Users/jenniferbueso/Library/CloudStorage/OneDrive-Personal/Documents/Estructura de Datos I/SistemaDeTrafico" "/Users/jenniferbueso/Library/CloudStorage/OneDrive-Personal/Documents/Estructura de Datos I/SistemaDeTrafico/build" "/Users/jenniferbueso/Library/CloudStorage/OneDrive-Personal/Documents/Estructura de Datos I/SistemaDeTrafico/build" "/Users/jenniferbueso/Library/CloudStorage/OneDrive-Personal/Documents/Estructura de Datos I/SistemaDeTrafico/build/CMakeFiles/TrafficSimulation.dir/DependInfo.cmake" "--color=$(COLOR)"
.PHONY : CMakeFiles/TrafficSimulation.dir/depend

