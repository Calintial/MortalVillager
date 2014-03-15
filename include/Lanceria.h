#ifndef LANCERIA_H
#define LANCERIA_H

/*
	Clase para gestionar los distintos edificios
*/
#include "edificio.h"
#include <iostream>

class Lanceria  : public edificio{
public:
	Lanceria();
	Lanceria(int, int);
	~Lanceria();

	virtual void Pintar(IVideoDriver*,int,int);
	virtual void aplicarTextura(IVideoDriver* driver);
	virtual bool isTransitable();
	
};

#endif
