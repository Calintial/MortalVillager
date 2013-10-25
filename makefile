hello: src/HelloWorld.cpp
	g++ -o bin/hello src/HelloWorld.cpp -lIrrlicht -lGL -lGLU -lX11 -lXxf86vm -I/usr/include/irrlicht/

clean:
	rm hello