#include "Unidades.h"

Unidades::Unidades()
{
	life = 100;
	position[0] = 0;
	position[1] = 0;
}

Unidades::~Unidades()
{
	life = 0;
	position[0] = 0;
	position[1] = 0;
}


int* Unidades::searchEnemy()
{
	/*Busca a un enemigo en su rango establecido y devuelve un puntero con un array de sus coordenadas*/
	int prueba[2] = {0,2};
	return prueba;
}

void Unidades::Move(int x, int y)
{
	/*Moverse a una posicion establecida*/
	if(x > position[0])
		position[0]++;
	if(y > position[1])
		position[1]++;

	cout<<"New position:"<<position[0]<<","<<position[1]<<endl;
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