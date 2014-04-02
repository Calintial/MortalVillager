#include "Arquero.h"

Arquero::Arquero()
{
	cout << "ConstruirArquero" << endl;
	setLife(100);
	vision_range = 5;
	attack_range = 2;
	attack_value = 1;
}

Arquero::Arquero(int x, int y) : Unidades(x,y)
{
	cout << "ConstruirArquero" << endl;
	setLife(100);
	vision_range = 5;
	attack_range = 2;
	attack_value = 1;
}

Arquero::~Arquero()
{
	cout << "DestroirArquero" << endl;
	setLife(0);
	vision_range = 0;
	attack_range = 0;
	attack_value = 0;
}

bool Arquero::enemy_in_attack_range(position2di pos)
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

void Arquero::Recovery()
{
	setLife(getLife()+1);
}

int Arquero::getVisionRange()
{
	return vision_range;
}

int Arquero::getAttackRange()
{
	return attack_range;
}

int Arquero::getAttackValue()
{
	return attack_value;
}

int Arquero::getType()
{
	return 1;
}

void Arquero::Pintar(IVideoDriver* driver,int TPositionX,int TPositionY)
{
	ITexture *TTexture = getTextura();
	driver->draw2DImage(TTexture, position2di(TPositionX, TPositionY), rect<s32>(0, 0, TTexture->getSize().Width, TTexture->getSize().Height), 0, SColor((u32)((1.0f - 0.0f) * 255), 255, 255, 255), true);
}

void Arquero::TexturaSeleccionada(IVideoDriver* driver,bool selected)
{
	if(selected)
		setTextura(driver->getTexture("../media/Texturas/units/user_unit_selected.png"));
	else
		setTextura(driver->getTexture("../media/Texturas/units/user_archer.png"));
}

void Arquero::aplicarTextura(IVideoDriver* driver)
{
	setTextura(driver->getTexture("../media/Texturas/units/user_archer.png"));
}
