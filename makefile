INCLUDES=-I/usr/include/irrlicht/ -Iinclude -g
LINKS=-lIrrlicht -lGL -lGLU -lX11 -lXxf86vm

.PHONY: all clean

main: bin/main

bin/main: src/main.cpp graphicEngine.o intelEngine.o personaje.o edificio.o
	mkdir -p bin
	g++ -o bin/main $^ $(INCLUDES) $(LINKS) #$^ es la lista de todas las dependencias


graphicEngine.o: src/graphicEngine.cpp include/graphicEngine.h
	g++ -c src/graphicEngine.cpp $(INCLUDES)

intelEngine.o: src/intelEngine.cpp include/intelEngine.h
	g++ -c src/intelEngine.cpp $(INCLUDES)

personaje.o: src/personaje.cpp include/personaje.h
	g++ -c src/personaje.cpp $(INCLUDES)

edificio.o: src/edificio.cpp include/edificio.h
	g++ -c src/edificio.cpp $(INCLUDES)

# bin/hello: src/HelloWorld.cpp
# 	mkdir -p bin;g++ -o bin/hello src/HelloWorld.cpp $(INCLUDES) $(LINKS)

clean:
	rm *.o
	rm -rf bin

