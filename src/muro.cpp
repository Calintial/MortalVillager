#include "muro.h"
Muro::Muro(int tipo, int posicionX, int posicionY){
	setTipo(tipo);
	position2di p(posicionX,posicionY);
	setPosition(p);
}

Muro::~Muro(){}

bool Muro::isTransitable(){
	return false;
}

void Muro::Pintar(IVideoDriver* driver)
{
	setTextura(driver->getTexture("../media/Texturas/map/mountains0.png"));
}