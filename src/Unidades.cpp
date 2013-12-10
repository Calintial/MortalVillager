#include "Unidades.h"

Unidades::Unidades()
{
	life = 100;
	setPosition(1,1);
	state = 0;
	last_clicked.X = 1;
	last_clicked.Y = 1;
	vision_range = 3;
	attack_range = 1;
}

Unidades::Unidades(int x, int y)
{
	life = 100;
	setPosition(x,y);
	state = 0;
	last_clicked.X = x;
	last_clicked.Y = y;
	vision_range = 3;
	attack_range = 1;
}

Unidades::~Unidades()
{
	life = 0;
	setPosition(0,0);
	last_clicked.X = 0;
	last_clicked.Y = 0;
	state = 0;
	vision_range = 0;
	attack_range = 0;
}


void Unidades::Move(int x, int y)
{
	position2di position = getPosition();
	state = MOVE;
	/*Moverse a una posicion establecida*/
	if(x<26 && y<20)
	{
		if(x > position.X)
			position.X++;
		else if(x < position.X)
			position.X--;

		if(y > position.Y)
			position.Y++;
		else if(y < position.Y)
			position.Y--;
			
		setPosition(position);
		cout<<"New position:"<<position.X<<","<<position.Y<<endl;
		last_clicked.X = x;
		last_clicked.Y = y;		
	}
}

void Unidades::Attack(position2di pos)
{
	if(enemy_in_attack_range(pos))
		life--;
		/*Hay un enemigo, atacar*/
	//cout<<"Attacking!!"<<endl;
	
	//cout<<"life: "<<life<<endl;
}

bool Unidades::enemy_in_attack_range(position2di pos)
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

int Unidades::getLife()
{
	return life;
}

void Unidades::Recovery()
{
	life++;
}

void Unidades::Pintar(IVideoDriver* driver)
{
	setTextura(driver->getTexture("../media/Texturas/units/user_unit_test.png"));
}

void Unidades::updateUnit()
{
	position2di position = getPosition();
	if(state == MOVE)
	{
		Move(last_clicked.X,last_clicked.Y);
		if(position.X == last_clicked.X && position.Y == last_clicked.Y)
		{
			state = NOTHING;
		}
	}
}

int Unidades::getVisionRange()
{
	return vision_range;
}

int Unidades::getAttackRange()
{
	return attack_range;
}