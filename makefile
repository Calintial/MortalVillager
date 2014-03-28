CC=g++

OPTS=-Wall -std=c++11 -O0 -g
INCLUDES=-I/usr/include/irrlicht/ -Iinclude -I/usr/include/fmodex/
LINKS=-lIrrlicht -lGL -lGLU -lX11 -lXxf86vm -lfmodex -lboost_graph

OBJECTS=battleIA.o graphicEngine.o gameEngine.o intelEngine.o edificio.o mainMenu.o Unidades.o suelo.o mapa2D.o IDibujable.o hud.o pausa.o state.o muro.o stateIA.o Region.o Camino.o Pathfinding.o Nodo.o NodoLocal.o NodoRegional.o pantallaBasica.o
OBJECTS_CLASES=Arquero.o Lancero.o Aldeano.o Espadachin.o ArqueroIA.o LanceroIA.o AldeanoIA.o EspadachinIA.o
OBJECTS_EDIFICIOS=CentroCiudad.o Lanceria.o Arqueria.o Cuartel.o Granja.o
OBJECTS_MAIN=pantalla.o pantallaPathfinding.o InterfazPathfinding.o pantallaIABatalla.o DebugMenu.o $(OBJECTS) $(OBJECTS_CLASES) $(OBJECTS_EDIFICIOS)


.PHONY: all clean

all: main
	echo "COMPILADO ALL"

# pathfinding: bin/pathfinding
# 	echo "COMPILADO PATHFINDING"

# ia_batalla: bin/ia_batalla
# 	echo "COMPILADO IA_BATALLA"

main: bin/main
	echo "COMPILADO MAIN"

bin/main: src/main.cpp $(OBJECTS_MAIN)
	mkdir -p bin
	$(CC) -o bin/main $^ $(OPTS) $(INCLUDES) $(LINKS) #$ ^ es la lista de todas las dependencias

# bin/pathfinding: src/main.cpp $(OBJECTS_PATHFINDING)
# 	mkdir -p bin
# 	$(CC) -o bin/pathfinding $^ $(OPTS) $(INCLUDES) $(LINKS) #$ ^ es la lista de todas las dependencias

# bin/ia_batalla: src/main.cpp $(OBJECTS_IA_BATALLA)
# 	mkdir -p bin
# 	$(CC) -o bin/ia_batalla $^ $(OPTS) $(INCLUDES) $(LINKS) #$ ^ es la lista de todas las dependencias

# To obtain object files
Nodo.o: src/Nodo.cpp include/Nodo.h include/boost/graph/labeled_graph.hpp
	$(CC) -c $< $(OPTS) $(INCLUDES) -o $@

%.o: src/%.cpp include/%.h 
	$(CC) -c $< $(OPTS) $(INCLUDES) -o $@

clean:
	rm -f *.o
	rm -rf bin
