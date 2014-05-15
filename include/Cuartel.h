#ifndef CUARTEL_H
#define CUARTEL_H

/*
	Clase para gestionar los distintos edificios
*/
#include "edificio.h"
#include <iostream>

class Cuartel  : public edificio{
public:
	Cuartel();
	Cuartel(int, int,bool);
	~Cuartel();

	virtual void Pintar(IVideoDriver*,int,int);
	virtual void aplicarTextura(IVideoDriver* driver);
	virtual bool isTransitable();
	
};

#endif
