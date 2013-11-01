/*
	Clase para gestionar los distintos personajes
*/
#include <iostream>

class personaje {
public:
	personaje();
	~personaje() {};
	personaje(const personaje&) {};
	personaje& operator=(const personaje&) {};

	void doSomething();

private:
};