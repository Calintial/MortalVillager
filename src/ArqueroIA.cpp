#include "ArqueroIA.h"

ArqueroIA::ArqueroIA()
{
	life = 100;
	vision_range = 5;
	attack_range = 2;
}

ArqueroIA::ArqueroIA(int x, int y) : battleIA(x,y)
{
	life = 100;
	vision_range = 5;
	attack_range = 2;
}

ArqueroIA::~ArqueroIA()
{
	life = 0;
	vision_range = 0;
	attack_range = 0;
}

void ArqueroIA::Attack(position2di pos)
{
	if(enemy_in_attack_range(pos))
		life--;
}

bool ArqueroIA::enemy_in_attack_range(position2di pos)
{
	position2di mypos = getPosition();
	/*Comprobar si esta en rango de ataque el enemigo*/
	for(int x = mypos.X - attack_range; x <= mypos.X + attack_range; x++)
	{
		for(int y = mypos.Y - attack_range; y <= mypos.Y + attack_range; y++)
		{
			if(pos.X == x && pos.Y == y)
			{
				return true;
			}
		}
	}
	return false;	
}

void ArqueroIA::Recovery()
{
	life++;
}

int ArqueroIA::getLife()
{
	return life;
}

int ArqueroIA::getVisionRange()
{
	return vision_range;
}

int ArqueroIA::getAttackRange()
{
	return attack_range;
}

void ArqueroIA::Pintar(IVideoDriver* driver,int TPositionX,int TPositionY)
{
	ITexture *TTexture = getTextura();
	driver->draw2DImage(TTexture, position2di(TPositionX, TPositionY), rect<s32>(0, 0, TTexture->getSize().Width, TTexture->getSize().Height), 0, SColor((u32)((1.0f - 0.0f) * 255), 255, 255, 255), true);
}

void ArqueroIA::TexturaSeleccionada(IVideoDriver* driver,bool selected)
{
	if(selected)
		setTextura(driver->getTexture("../media/Texturas/units/ia_unit_selected.png"));
	else
		setTextura(driver->getTexture("../media/Texturas/units/ia_archer.png"));
}

void ArqueroIA::aplicarTextura(IVideoDriver* driver)
{
	setTextura(driver->getTexture("../media/Texturas/units/ia_archer.png"));
}