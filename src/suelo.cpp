#include "suelo.h"


Suelo::Suelo(int t)
{
	setTipo(t);
}

Suelo::~Suelo()
{
}

void Suelo::Pintar(IVideoDriver* driver)
{
	if(getTipo()==0)
		setTextura(driver->getTexture("../media/Texturas/map/grass0.png"));
	else if(getTipo()==1)
		setTextura(driver->getTexture("../media/Texturas/map/mountains0.png"));
}
