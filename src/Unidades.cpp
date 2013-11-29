#include "Unidades.h"

Unidades::Unidades()
{
	life = 100;
	position[0] = 1;
	position[1] = 1;
	state = 0;
	last_clicked[0] = 1;
	last_clicked[1] = 1;
}

Unidades::Unidades(int x, int y)
{
	life = 100;
	position[0] = x;
	position[1] = y;
	state = 0;
	last_clicked[0] = x;
	last_clicked[1] = y;
}

Unidades::~Unidades()
{
	life = 0;
	position[0] = 0;
	position[1] = 0;
	last_clicked[0] = 0;
	last_clicked[1] = 0;
	state = 0;
}


void Unidades::Move(int x, int y)
{
	state = MOVE;
	/*Moverse a una posicion establecida*/
	if(x > position[0])
		position[0]++;
	else if(x < position[0])
		position[0]--;

	if(y > position[1])
		position[1]++;
	else if(y < position[1])
		position[1]--;

	cout<<"New position:"<<position[0]<<","<<position[1]<<endl;
	last_clicked[0] = x;
	last_clicked[1] = y;
}

void Unidades::Attack(int x, int y)
{
	//if(enemy_in_range(x,y))
		/*Hay un enemigo, atacar*/
	cout<<"Attacking!!"<<endl;
	life--;
	cout<<"life: "<<life<<endl;
}


int* Unidades::getPosition()
{
	return position;
}

bool Unidades::enemy_in_attack_range(int x,int y)
{
	/*Comprobar si es posicion adyacente a la unidad*/
	if(x == position[0] + 1 || x == position[0] - 1 || y == position[1] + 1 || y == position[1] - 1)
	{
		/*si lo es, comprobar si hay un enemigo*/
		return true;
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

void Unidades::setPosition(int x,int y)
{
	position[0] = x;
	position[1] = y;	
}

void Unidades::Pintar(IVideoDriver* driver)
{
	setTextura(driver->getTexture("../media/Texturas/units/user_unit_test.png"));
}

void Unidades::updateUnit()
{
	if(state == MOVE)
	{
		Move(last_clicked[0],last_clicked[1]);
		if(position[0] == last_clicked[0] && position[1] == last_clicked[1])
		{
			state = NOTHING;
		}
	}
}