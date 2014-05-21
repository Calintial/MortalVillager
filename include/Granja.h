#ifndef GRANJA_H
#define GRANJA_H

/*
	Clase para gestionar los distintos edificios
*/
#include "edificio.h"
#include <iostream>

class Granja  : public edificio{
public:
	Granja();
	Granja(int, int, bool);
	~Granja();

	virtual void Pintar(IVideoDriver*,int,int);
	virtual void aplicarTextura(IVideoDriver* driver);
	virtual bool isTransitable();
	
};

#endif
