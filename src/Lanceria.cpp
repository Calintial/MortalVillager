#include "Lanceria.h"


Lanceria::Lanceria() : edificio(4)
{
}

Lanceria::Lanceria(int x, int y, bool usuario) : edificio(3,x,y,usuario)
{
}

Lanceria::~Lanceria()
{

}

void Lanceria::Pintar(IVideoDriver* driver,int TPositionX,int TPositionY)
{
	ITexture *TTexture = getTextura();
	driver->draw2DImage(TTexture, position2di(TPositionX, TPositionY), rect<s32>(0, 0, TTexture->getSize().Width, TTexture->getSize().Height), 0, SColor((u32)((1.0f - 0.0f) * 255), 255, 255, 255), true);
}

void Lanceria::aplicarTextura(IVideoDriver* driver)
{
	setTextura(driver->getTexture("../media/Texturas/building/spear_build.png"));
}

bool Lanceria::isTransitable()
{
	return false;
}
