INCLUDES=-I/usr/include/irrlicht/ -Iinclude
LINKS=-lIrrlicht -lGL -lGLU -lX11 -lXxf86vm

.PHONY: all clean

main: bin/main

bin/main: src/main.cpp graphicEngine.o
	mkdir -p bin
	g++ -o bin/main src/main.cpp graphicEngine.o $(INCLUDES) $(LINKS) 

graphicEngine.o: src/graphicEngine.cpp include/graphicEngine.h
	g++ -c src/graphicEngine.cpp $(INCLUDES)

# bin/hello: src/HelloWorld.cpp
# 	mkdir -p bin;g++ -o bin/hello src/HelloWorld.cpp $(INCLUDES) $(LINKS)

clean:
	rm *.o
	rm -rf bin

