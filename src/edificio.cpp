#include "edificio.h"

edificio::edificio(int t)
{
	setTipo(2);
	setClase(t);
	setPosition(0,0);
	setPintable(true);
	de_usuario = true;
}

edificio::edificio(int t,int x,int y,bool usuario)
{
	setTipo(2);
	setClase(t);
	setPosition(x,y);
	setPintable(true);
	de_usuario = usuario;
}


edificio::~edificio()
{
}

bool edificio::isTransitable(){
	return false;
}
