OPTS=-g  -std=c++11
INCLUDES=-I/usr/include/irrlicht/ -Iinclude -I/usr/include/fmodex/
LINKS=-lIrrlicht -lGL -lGLU -lX11 -lXxf86vm -lfmodex -lboost_graph


OBJECTS=graphicEngine.o gameEngine.o intelEngine.o edificio.o mainMenu.o Unidades.o battleIA.o suelo.o mapa2D.o IDibujable.o DebugMenu.o hud.o pantalla.o pausa.o state.o muro.o

.PHONY: all clean

main: bin/main

bin/main: src/main.cpp $(OBJECTS)

	mkdir -p bin
	g++ -o bin/main $^ $(OPTS) $(INCLUDES) $(LINKS) #$ ^ es la lista de todas las dependencias

# To obtain object files
%.o: src/%.cpp include/%.h
	g++ -c $< $(OPTS) $(INCLUDES) -o $@

# bin/hello: src/HelloWorld.cpp
# 	mkdir -p bin;g++ -o bin/hello src/HelloWorld.cpp $(OPTS) $(INCLUDES) $(LINKS)

clean:
	rm *.o
	rm -rf bin
