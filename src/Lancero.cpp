#include "Lancero.h"

Lancero::Lancero()
{
	life = 100;
	vision_range = 3;
	attack_range = 1;
	attack_value = 1;
}

Lancero::Lancero(int x, int y) : Unidades(x,y)
{
	life = 100;
	vision_range = 3;
	attack_range = 1;
	attack_value = 1;
}

Lancero::~Lancero()
{
	life = 0;
	vision_range = 0;
	attack_range = 0;
	attack_value = 0;
}

void Lancero::Attack(position2di pos)
{
	if(enemy_in_attack_range(pos))
		life--;
}

bool Lancero::enemy_in_attack_range(position2di pos)
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

void Lancero::Recovery()
{
	life++;
}

int Lancero::getLife()
{
	return life;
}

int Lancero::getVisionRange()
{
	return vision_range;
}

int Lancero::getAttackRange()
{
	return attack_range;
}

void Lancero::Pintar(IVideoDriver* driver,int TPositionX,int TPositionY)
{
	ITexture *TTexture = getTextura();
	driver->draw2DImage(TTexture, position2di(TPositionX, TPositionY), rect<s32>(0, 0, TTexture->getSize().Width, TTexture->getSize().Height), 0, SColor((u32)((1.0f - 0.0f) * 255), 255, 255, 255), true);
}

void Lancero::TexturaSeleccionada(IVideoDriver* driver,bool selected)
{
	if(selected)
		setTextura(driver->getTexture("../media/Texturas/units/user_unit_selected.png"));
	else
		setTextura(driver->getTexture("../media/Texturas/units/user_spearman.png"));
}

void Lancero::aplicarTextura(IVideoDriver* driver)
{
	setTextura(driver->getTexture("../media/Texturas/units/user_spearman.png"));
}