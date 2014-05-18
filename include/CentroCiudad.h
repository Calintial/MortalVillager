#ifndef CENTROCIUDAD_H
#define CENTROCIUDAD_H

/*
	Clase para gestionar los distintos edificios
*/
#include "edificio.h"
#include <iostream>

class CentroCiudad  : public edificio{
public:
	CentroCiudad();
	CentroCiudad(int, int,bool);
	~CentroCiudad();

	virtual void Pintar(IVideoDriver*,int,int);
	virtual void aplicarTextura(IVideoDriver* driver);
	virtual bool isTransitable();
	
};

#endif
