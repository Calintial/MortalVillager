#include "EspadachinIA.h"

EspadachinIA::EspadachinIA()
{
	cout << "ConstruirEspadachinIA" << endl;
	setLife(100);
	vision_range = 3;
	attack_range = 1;
	attack_value = 1;
}

EspadachinIA::EspadachinIA(int x, int y) : battleIA(x,y)
{
	cout << "ConstruirEspadachinIA" << endl;
	setLife(100);
	vision_range = 3;
	attack_range = 1;
	attack_value = 1;
}

EspadachinIA::~EspadachinIA()
{
	cout << "DestruirEspadachinIA" << endl;
	setLife(0);
	vision_range = 0;
	attack_range = 0;
	attack_value = 0;
}


bool EspadachinIA::enemy_in_attack_range(position2di pos)
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

void EspadachinIA::Recovery()
{	
	if(getLife()<100){
		setLife(getLife()+1);
	}
	
}

int EspadachinIA::getVisionRange()
{
	return vision_range;
}

int EspadachinIA::getAttackRange()
{
	return attack_range;
}

int EspadachinIA::getAttackValue()
{
	return attack_value;
}

int EspadachinIA::getType()
{
	return 2;
}

void EspadachinIA::Pintar(IVideoDriver* driver,int TPositionX,int TPositionY)
{
	ITexture *TTexture = getTextura();
	driver->draw2DImage(TTexture, position2di(TPositionX, TPositionY), rect<s32>(0, 0, TTexture->getSize().Width, TTexture->getSize().Height), 0, SColor((u32)((1.0f - 0.0f) * 255), 255, 255, 255), true);
}

void EspadachinIA::TexturaSeleccionada(IVideoDriver* driver,bool selected)
{
	if(selected)
		setTextura(driver->getTexture("../media/Texturas/units/ia_unit_selected.png"));
	else
		setTextura(driver->getTexture("../media/Texturas/units/ia_swordman.png"));
}

void EspadachinIA::aplicarTextura(IVideoDriver* driver)
{
	setTextura(driver->getTexture("../media/Texturas/units/ia_swordman.png"));
}
