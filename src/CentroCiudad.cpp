#include "CentroCiudad.h"


CentroCiudad::CentroCiudad() : edificio(0)
{
}

CentroCiudad::CentroCiudad(int x, int y, bool usuario) : edificio(3,x,y,usuario)
{
}

CentroCiudad::~CentroCiudad()
{

}

void CentroCiudad::Pintar(IVideoDriver* driver,int TPositionX,int TPositionY)
{
	int tamX = 64;
	int tamY = 192;
	ITexture *TTexture = getTextura();
	driver->draw2DImage(TTexture, position2di(TPositionX, TPositionY), rect<s32>(0,0,TTexture->getSize().Width, TTexture->getSize().Height), 0, SColor((u32)((1.0f - 0.0f) * 255), 255, 255, 255), true);

}	

void CentroCiudad::aplicarTextura(IVideoDriver* driver)
{
	setTextura(driver->getTexture("../media/Texturas/building/city_center.png"));
}

bool CentroCiudad::isTransitable()
{
	return false;
}
