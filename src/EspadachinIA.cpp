#include "EspadachinIA.h"

EspadachinIA::EspadachinIA()
{
	cout << "ConstruirEspadachinIA" << endl;
	setLife(100);
	vision_range = 3;
	attack_range = 1;
	attack_value = 1;
	current_sprite = 0;
	sprite_Width = 57;
	sprite_Height = 51;
	delay_sprite = 0;
}

EspadachinIA::EspadachinIA(int x, int y) : battleIA(x,y)
{
	cout << "ConstruirEspadachinIA" << endl;
	setLife(100);
	vision_range = 3;
	attack_range = 1;
	attack_value = 1;
	current_sprite = 0;
	sprite_Width = 57;
	sprite_Height = 51;
	delay_sprite = 0;
}

EspadachinIA::~EspadachinIA()
{
	cout << "DestruirEspadachinIA" << endl;
	setLife(0);
	vision_range = 0;
	attack_range = 0;
	attack_value = 0;
	current_sprite = 0;
	sprite_Width = 0;
	sprite_Height = 0;
	delay_sprite = 0;
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
	setLife(getLife()+1);
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
	ITexture *TTexture_Suelo = getTextura();
	
	int pos_sprite = current_sprite * sprite_Width;

	driver->draw2DImage(TTexture_Suelo, position2di(TPositionX, TPositionY), rect<s32>(0, 0, TTexture_Suelo->getSize().Width, TTexture_Suelo->getSize().Height), 0, SColor((u32)((1.0f - 0.0f) * 255), 255, 255, 255), true);
	driver->draw2DImage(TTexture, position2di(TPositionX + 2, TPositionY - 20), rect<s32>(pos_sprite, 0, pos_sprite + sprite_Width, sprite_Height), 0, SColor((u32)((1.0f - 0.0f) * 255), 255, 255, 255), true);
	nextSprite();
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
	TTexture = driver->getTexture("../media/Texturas/units/swordman_ia.png");
	setTextura(driver->getTexture("../media/Texturas/units/ia_swordman.png"));
}

void EspadachinIA::nextSprite()
{

	if(getState() == NOTHING && delay_sprite == MAX_DELAY)
	{

		if(current_sprite >= 9)
		{
			current_sprite = 0;
		}
		else
		{
			current_sprite++;
		}
		delay_sprite = 0;
	}
	else if(getState() == MOVE && delay_sprite == MAX_DELAY)
	{

		if(current_sprite <= 9)
		{
			current_sprite = 10;
		}
		else if(current_sprite >= 19)
		{
			current_sprite = 10;
		}
		else
		{
			current_sprite++;
		}	
		delay_sprite = 0;	
	}
	else if(getState() == ATTACKING && delay_sprite == MAX_DELAY)
	{
		if(current_sprite <= 19)
		{
			current_sprite = 20;
		}
		else if(current_sprite >= 29)
		{
			current_sprite = 20;
		}
		else
		{
			current_sprite++;
		}	
		delay_sprite = 0;
	}
	else if(getState() == DEAD && delay_sprite == MAX_DELAY)
	{
		if(current_sprite <= 29)
		{
			current_sprite = 30;
		}
		else if(current_sprite >= 39)
		{
			current_sprite = 30;
		}
		else
		{
			current_sprite++;
		}
		delay_sprite = 0;			
	}
	else
	{
		delay_sprite++;
	}

	
}