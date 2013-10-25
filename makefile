hello: src/HelloWorld.cpp
	mkdir bin;g++ -o bin/hello src/HelloWorld.cpp -lIrrlicht -lGL -lGLU -lX11 -lXxf86vm -I/usr/include/irrlicht/

clean:
	rm hello
