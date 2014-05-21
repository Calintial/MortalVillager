#include "Granja.h"


Granja::Granja() : edificio(1)
{
}

Granja::Granja(int x, int y, bool usuario) : edificio(1,x,y,usuario)
{
}

Granja::~Granja()
{

}

void Granja::Pintar(IVideoDriver* driver,int TPositionX,int TPositionY)
{
	ITexture *TTexture = getTextura();
	driver->draw2DImage(TTexture, position2di(TPositionX, TPositionY), rect<s32>(0, 0, TTexture->getSize().Width, TTexture->getSize().Height), 0, SColor((u32)((1.0f - 0.0f) * 255), 255, 255, 255), true);
}

void Granja::aplicarTextura(IVideoDriver* driver)
{
	setTextura(driver->getTexture("../media/Texturas/building/farm.png"));
}

bool Granja::isTransitable()
{
	return false;
}
