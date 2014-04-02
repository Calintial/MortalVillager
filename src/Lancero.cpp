#include "Lancero.h"

Lancero::Lancero()
{
	cout << "ConstruirLancero" << endl;
	setLife(100);
	vision_range = 3;
	attack_range = 1;
	attack_value = 1;
}

Lancero::Lancero(int x, int y) : Unidades(x,y)
{
	cout << "ConstruirLancero" << endl;
	setLife(100);
	vision_range = 3;
	attack_range = 1;
	attack_value = 1;
}

Lancero::~Lancero()
{
	cout << "DestruirLancero" << endl;
	setLife(0);
	vision_range = 0;
	attack_range = 0;
	attack_value = 0;
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
	setLife(getLife()+1);
}

int Lancero::getVisionRange()
{
	return vision_range;
}

int Lancero::getAttackRange()
{
	return attack_range;
}

int Lancero::getAttackValue()
{
	return attack_value;
}

int Lancero::getType()
{
	return 3;
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
