#include "edificio.h"

edificio::edificio(int t)
{
	setTipo(2);
	setClase(t);
	setPosition(0,0);
}

edificio::edificio(int t,int x,int y)
{
	setTipo(2);
	setClase(t);
	setPosition(x,y);
}


edificio::~edificio()
{
}

bool edificio::isTransitable(){
	return false;
}
