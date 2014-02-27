#include "Cuartel.h"


Cuartel::Cuartel() : edificio(3)
{
}

Cuartel::Cuartel(int x, int y) : edificio(3,x,y)
{
}

Cuartel::~Cuartel()
{

}

void Cuartel::Pintar(IVideoDriver* driver,int TPositionX,int TPositionY)
{
	ITexture *TTexture = getTextura();
	driver->draw2DImage(TTexture, position2di(TPositionX, TPositionY), rect<s32>(0, 0, TTexture->getSize().Width, TTexture->getSize().Height), 0, SColor((u32)((1.0f - 0.0f) * 255), 255, 255, 255), true);
}

void Cuartel::aplicarTextura(IVideoDriver* driver)
{
	setTextura(driver->getTexture("../media/Texturas/building/edificio.png"));
}

bool Cuartel::isTransitable()
{
	return false;
}