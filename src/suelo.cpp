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
	setTextura(driver->getTexture("../media/Texturas/map/tiles.png"));
}
