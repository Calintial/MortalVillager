#ifndef EDIFICIO_H
#define EDIFICIO_H

/*
	Clase para gestionar los distintos edificios
*/
#include "IDibujable.h"
#include <iostream>

class edificio  : public IDibujable{
public:
	edificio(int t, IDibujable* partes);
	~edificio();

	void Pintar(IVideoDriver*,int,int);
	void aplicarTextura(IVideoDriver* driver);
	
	//void doSomething();
	
private:
	IDibujable* partes;
};

#endif
