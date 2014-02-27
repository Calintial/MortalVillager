#ifndef ARQUERIA_h
#define ARQUERIA_h

/*
	Clase para gestionar los distintos edificios
*/
#include "edificio.h"
#include <iostream>

class Arqueria  : public edificio{
public:
	Arqueria();
	Arqueria(int, int);
	~Arqueria();

	virtual void Pintar(IVideoDriver*,int,int);
	virtual void aplicarTextura(IVideoDriver* driver);
	virtual bool isTransitable();
	
};

#endif
