#include "suelo.h"


Suelo::Suelo(int t, int i, int j)
{
	setTipo(t);
	position2di p;
	p.X = i;
	p.Y = j;
	setPosition(p);
}

Suelo::~Suelo()
{
}

void Suelo::Pintar(IVideoDriver* driver)
{
	setTextura(driver->getTexture("../media/Texturas/map/tiles.png"));
}
