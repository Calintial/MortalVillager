#include "CentroCiudad.h"


CentroCiudad::CentroCiudad() : edificio(0)
{
	life = 100;
}

CentroCiudad::CentroCiudad(int x, int y, bool usuario) : edificio(0,x,y,usuario)
{
	life = 100;
}

CentroCiudad::~CentroCiudad()
{
	life = 0;
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

void CentroCiudad::PierdoVida(int danyo)
{
	if(life-danyo<0)
	{
		life = 0;
	}
	else
	{	
		life = life-danyo;
	}
}