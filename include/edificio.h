#ifndef EDIFICIO_H
#define EDIFICIO_H

/*
	Clase para gestionar los distintos edificios
*/
#include "IDibujable.h"
#include <iostream>

class edificio  : public IDibujable{
public:
	edificio(int t);
	~edificio();
	edificio(const edificio&) {};
	edificio& operator=(const edificio&) {};

	void Pintar(IVideoDriver* driver);

	//void doSomething();

private:
};

#endif
