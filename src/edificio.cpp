#include "edificio.h"

edificio::edificio(int t)
{
	setTipo(t);
	setPosition(0,0);
}

edificio::edificio(int t,int x,int y)
{
	setTipo(t);
	setPosition(x,y);
}


edificio::~edificio()
{
}
