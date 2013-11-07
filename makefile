OPTS=-g
INCLUDES=-I/usr/include/irrlicht/ -Iinclude
LINKS=-lIrrlicht -lGL -lGLU -lX11 -lXxf86vm

.PHONY: all clean

main: bin/main

bin/main: src/main.cpp graphicEngine.o intelEngine.o personaje.o edificio.o mainMenu.o
	mkdir -p bin
	g++ -o bin/main $^ $(OPTS) $(INCLUDES) $(LINKS) #\$^ es la lista de todas las dependencias


graphicEngine.o: src/graphicEngine.cpp include/graphicEngine.h
	g++ -c src/graphicEngine.cpp $(OPTS) $(INCLUDES)

mainMenu.o: src/mainMenu.cpp include/mainMenu.h
	g++ -c src/mainMenu.cpp $(OPTS) $(INCLUDES)

intelEngine.o: src/intelEngine.cpp include/intelEngine.h
	g++ -c src/intelEngine.cpp $(OPTS) $(INCLUDES)

personaje.o: src/personaje.cpp include/personaje.h
	g++ -c src/personaje.cpp $(OPTS) $(INCLUDES)

edificio.o: src/edificio.cpp include/edificio.h
	g++ -c src/edificio.cpp $(OPTS) $(INCLUDES)

# bin/hello: src/HelloWorld.cpp
# 	mkdir -p bin;g++ -o bin/hello src/HelloWorld.cpp $(OPTS) $(INCLUDES) $(LINKS)

clean:
	rm *.o
	rm -rf bin

