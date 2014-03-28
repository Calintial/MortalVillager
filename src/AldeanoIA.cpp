#include "AldeanoIA.h"

AldeanoIA::AldeanoIA()
{
	cout << "ConstruirAldeanoIA" << endl;
	life = 100;
	vision_range = 3;
	attack_range = 1;
	attack_value = 1;
}

AldeanoIA::AldeanoIA(int x, int y) : battleIA(x,y)
{
	cout << "ConstruirAldeanoIA" << endl;
	life = 100;
	vision_range = 3;
	attack_range = 1;
	attack_value = 1;
}

AldeanoIA::~AldeanoIA()
{
	cout << "DestruirAldeanoIA" << endl;
	life = 0;
	vision_range = 0;
	attack_range = 0;
	attack_value = 0;
}

void AldeanoIA::Attack(position2di pos)
{
	if(enemy_in_attack_range(pos))
		life--;
}

bool AldeanoIA::enemy_in_attack_range(position2di pos)
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

void AldeanoIA::Recovery()
{
	life++;
}

int AldeanoIA::getLife()
{
	return life;
}

int AldeanoIA::getVisionRange()
{
	return vision_range;
}

int AldeanoIA::getAttackRange()
{
	return attack_range;
}

int AldeanoIA::getAttackValue()
{
	return attack_value;
}

int AldeanoIA::getType()
{
	return 0;
}

void AldeanoIA::Pintar(IVideoDriver* driver,int TPositionX,int TPositionY)
{
	ITexture *TTexture = getTextura();
	driver->draw2DImage(TTexture, position2di(TPositionX, TPositionY), rect<s32>(0, 0, TTexture->getSize().Width, TTexture->getSize().Height), 0, SColor((u32)((1.0f - 0.0f) * 255), 255, 255, 255), true);
}

void AldeanoIA::TexturaSeleccionada(IVideoDriver* driver,bool selected)
{
	if(selected)
		setTextura(driver->getTexture("../media/Texturas/units/ia_unit_selected.png"));
	else
		setTextura(driver->getTexture("../media/Texturas/units/ia_villager.png"));
}

void AldeanoIA::aplicarTextura(IVideoDriver* driver)
{
	setTextura(driver->getTexture("../media/Texturas/units/ia_villager.png"));
}
