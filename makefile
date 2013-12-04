OPTS=-g -Wall --std=c++0x
INCLUDES=-I/usr/include/irrlicht/ -Iinclude -I/usr/include/fmodex/
LINKS=-lIrrlicht -lGL -lGLU -lX11 -lXxf86vm -lfmodex -lboost_graph
OBJECTS = $(wildcard *.o)

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
