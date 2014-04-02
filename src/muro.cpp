#include "muro.h"
Muro::Muro(int posicionX, int posicionY){
	setTipo(1);
	position2di p(posicionX,posicionY);
	setPosition(p);
}

Muro::~Muro(){}

bool Muro::isTransitable(){
	return false;
}

void Muro::Pintar(IVideoDriver* driver,int TPositionX,int TPositionY)
{
	ITexture *TTexture = getTextura();

	driver->draw2DImage(TTexture_Suelo, position2di(TPositionX, TPositionY), rect<s32>(0, 0, TTexture_Suelo->getSize().Width, TTexture_Suelo->getSize().Height), 0, SColor((u32)((1.0f - 0.0f) * 255), 255, 255, 255), true);
	driver->draw2DImage(TTexture, position2di(TPositionX, TPositionY), rect<s32>(0, 0, TTexture->getSize().Width, TTexture->getSize().Height), 0, SColor((u32)((1.0f - 0.0f) * 255), 255, 255, 255), true);

}

void Muro::aplicarTextura(IVideoDriver* driver)
{
	setTextura(driver->getTexture("../media/Texturas/suelo/tree.png"));
	TTexture_Suelo = driver->getTexture("../media/Texturas/suelo/grass2.png");
}
