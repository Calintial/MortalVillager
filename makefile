CC=g++
OPTS=-g -Wall -std=c++11 

INCLUDES=-I/usr/include/irrlicht/ -Iinclude -I/usr/include/fmodex/
LINKS=-lIrrlicht -lGL -lGLU -lX11 -lXxf86vm -lfmodex -lboost_graph

OBJECTS=graphicEngine.o gameEngine.o intelEngine.o edificio.o mainMenu.o Unidades.o battleIA.o suelo.o mapa2D.o IDibujable.o DebugMenu.o hud.o pausa.o state.o muro.o stateIA.o Region.o Enlace.o Camino.o pathfinding.o Nodo.o
OBJECTS_MAIN=pantalla.o $(OBJECTS)
OBJECTS_PATHFINDING=pantallaPathfinding.o InterfazPathfinding.o $(OBJECTS)

.PHONY: all clean

all: bin/main bin/pathfinding


pathfinding: bin/pathfinding
	

main: bin/main


bin/main: src/main.cpp $(OBJECTS_MAIN)
	mkdir -p bin
	$(CC) -o bin/main $^ $(OPTS) $(INCLUDES) $(LINKS) #$ ^ es la lista de todas las dependencias

bin/pathfinding: src/main.cpp $(OBJECTS_PATHFINDING)
	mkdir -p bin
	$(CC) -o bin/pathfinding $^ $(OPTS) $(INCLUDES) $(LINKS) #$ ^ es la lista de todas las dependencias

# To obtain object files
%.o: src/%.cpp include/%.h
	$(CC) -c $< $(OPTS) $(INCLUDES) -o $@

clean:
	rm -f *.o
	rm -rf bin
