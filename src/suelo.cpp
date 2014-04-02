#include "suelo.h"


Suelo::Suelo(int i, int j)
{
	setTipo(0);
	position2di p;
	p.X = j;
	p.Y = i;
	setPosition(p);
	isometric = true;
}

Suelo::~Suelo()
{
}

void Suelo::Pintar(IVideoDriver* driver,int TPositionX,int TPositionY)
{
	ITexture *TTexture = getTextura();
	driver->draw2DImage(TTexture, position2di(TPositionX, TPositionY), rect<s32>(0,0,TTexture->getSize().Width, TTexture->getSize().Height), 0, SColor((u32)((1.0f - 0.0f) * 255), 255, 255, 255), true);
}

bool Suelo::isTransitable(){
	return true && (vinculado == NULL || vinculado->isTransitable());
}

void Suelo::aplicarTextura(IVideoDriver* driver)
{
	if(isometric)
		setTextura(driver->getTexture("../media/Texturas/suelo/grass2.png"));
	else
		setTextura(driver->getTexture("../media/Texturas/suelo/grass.png"));
}

void Suelo::setIsometric(bool iso)
{
	isometric = iso;
}
