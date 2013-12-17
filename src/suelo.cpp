#include "suelo.h"


Suelo::Suelo(int t, int i, int j)
{
	setTipo(t);
	position2di p;
	p.X = j;
	p.Y = i;
	setPosition(p);
}

Suelo::~Suelo()
{
}

void Suelo::Pintar(IVideoDriver* driver,int TPositionX,int TPositionY)
{
	ITexture *TTexture = getTextura();
	driver->draw2DImage(TTexture, position2di(TPositionX - (TTexture->getSize().Width), TPositionY - (TTexture->getSize().Height)), rect<s32>(0, 0, TTexture->getSize().Width, TTexture->getSize().Height), 0, SColor((u32)((1.0f - 0.0f) * 255), 255, 255, 255), true);
}

bool Suelo::isTransitable(){
	return true;
}

void Suelo::aplicarTextura(IVideoDriver* driver)
{
	setTextura(driver->getTexture("../media/Texturas/map/tiles.png"));
}
