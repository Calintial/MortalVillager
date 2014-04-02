#ifndef EDIFICIO_H
#define EDIFICIO_H

/*
	Clase para gestionar los distintos edificios
*/
#include "IDibujable.h"
#include <iostream>

class edificio  : public IDibujable{
public:
	edificio(int,int,int);
	edificio(int);
	~edificio();

	virtual void Pintar(IVideoDriver*,int,int) = 0;
	virtual void aplicarTextura(IVideoDriver* driver) = 0;
	virtual bool isTransitable() = 0;
	
	void setClase(int t){clase = t;};
	int getClase(){return clase;};
		
private:
	int clase;
	
};

#endif
