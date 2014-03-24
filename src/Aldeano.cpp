#include "Aldeano.h"

Aldeano::Aldeano()
{
	life = 100;
	vision_range = 3;
	attack_range = 1;
	current_sprite = 0;
	sprite_Width = 28;
	sprite_Height = 43;
}

Aldeano::Aldeano(int x, int y) : Unidades(x,y)
{
	life = 100;
	vision_range = 3;
	attack_range = 1;
	current_sprite = 0;
	sprite_Width = 28;
	sprite_Height = 43;
}

Aldeano::~Aldeano()
{
	life = 0;
	vision_range = 0;
	attack_range = 0;
	current_sprite = 0;
	TTexture = NULL;
}

void Aldeano::Attack(position2di pos)
{
	if(enemy_in_attack_range(pos))
		life--;
}

bool Aldeano::enemy_in_attack_range(position2di pos)
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

void Aldeano::Recovery()
{
	life++;
}

int Aldeano::getLife()
{
	return life;
}

int Aldeano::getVisionRange()
{
	return vision_range;
}

int Aldeano::getAttackRange()
{
	return attack_range;
}

void Aldeano::Pintar(IVideoDriver* driver,int TPositionX,int TPositionY)
{
	ITexture *TTexture_Suelo = getTextura();
	
	int pos_sprite = current_sprite * sprite_Height;

	driver->draw2DImage(TTexture_Suelo, position2di(TPositionX, TPositionY), rect<s32>(0, 0, TTexture_Suelo->getSize().Width, TTexture_Suelo->getSize().Height), 0, SColor((u32)((1.0f - 0.0f) * 255), 255, 255, 255), true);
	driver->draw2DImage(TTexture, position2di(TPositionX + 20, TPositionY - 20), rect<s32>(0, pos_sprite, sprite_Width, pos_sprite + sprite_Height), 0, SColor((u32)((1.0f - 0.0f) * 255), 255, 255, 255), true);

	if(getState() == NOTHING)
	{
		cout<<"NOTHING"<<endl;
		if(current_sprite >= 9)
		{
			current_sprite = 0;
		}
		else
		{
			current_sprite++;
		}		
	}
	else if(getState() == MOVE)
	{
		cout<<"MOVE"<<endl;
		if(current_sprite == 9)
		{
			current_sprite = 10;
		}
		else if(current_sprite == 24)
		{
			current_sprite = 10;
		}
		else
		{
			current_sprite++;
		}		
	}

	
}

void Aldeano::TexturaSeleccionada(IVideoDriver* driver,bool selected)
{
	if(selected)
		setTextura(driver->getTexture("../media/Texturas/units/user_unit_selected.png"));
	else
		setTextura(driver->getTexture("../media/Texturas/units/user_villager.png"));
}

void Aldeano::aplicarTextura(IVideoDriver* driver)
{
	TTexture = driver->getTexture("../media/Texturas/units/villager.png");
	setTextura(driver->getTexture("../media/Texturas/units/user_villager.png"));
}