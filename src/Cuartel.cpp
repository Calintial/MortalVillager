#include "Cuartel.h"


Cuartel::Cuartel() : edificio(2)
{
}

Cuartel::Cuartel(int x, int y, bool usuario) : edificio(2,x,y,usuario)
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
	setTextura(driver->getTexture("../media/Texturas/building/barracks.png"));
}

bool Cuartel::isTransitable()
{
	return false;
}