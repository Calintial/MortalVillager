#include "edificio.h"

edificio::edificio(int t, IDibujable* p)
{
	setTipo(t);
	partes = p;
}

edificio::~edificio()
{
}

void edificio::Pintar(IVideoDriver* driver)
{
	//setTextura(driver->getTexture("../media/Texturas/map/mountains0.png"));
}
