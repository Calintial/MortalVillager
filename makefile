INCLUDES=-I/usr/include/irrlicht/ -Iinclude
LINKS=-lIrrlicht -lGL -lGLU -lX11 -lXxf86vm

.PHONY: all clean

main: bin/main

bin/main: src/main.cpp graphicEngine.o
	mkdir -p bin
	g++ -o bin/main src/main.cpp graphicEngine.o edificio.o personaje.o $(INCLUDES) $(LINKS) 

graphicEngine.o: src/graphicEngine.cpp include/graphicEngine.h src/edificio.cpp include/edificio.h src/personaje.cpp include/personaje.h
	g++ -c src/graphicEngine.cpp src/personaje.cpp src/edificio.cpp $(INCLUDES)

# bin/hello: src/HelloWorld.cpp
# 	mkdir -p bin;g++ -o bin/hello src/HelloWorld.cpp $(INCLUDES) $(LINKS)

clean:
	rm *.o
	rm -rf bin

