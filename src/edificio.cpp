#include "edificio.h"

edificio::edificio(int t, IDibujable* p)
{
	setTipo(t);
	partes = p;
}

edificio::~edificio()
{
}

void edificio::Pintar(IVideoDriver* driver,int TPositionX,int TPositionY)
{
	ITexture *TTexture = getTextura();
	driver->draw2DImage(TTexture, position2di(TPositionX - (TTexture->getSize().Width), TPositionY - (TTexture->getSize().Height)), rect<s32>(0, 0, TTexture->getSize().Width, TTexture->getSize().Height), 0, SColor((u32)((1.0f - 0.0f) * 255), 255, 255, 255), true);
}

void edificio::aplicarTextura(IVideoDriver* driver)
{
	//setTextura(driver->getTexture("../media/Texturas/map/tiles.png"));
}