#include "Unidades.h"

Unidades::Unidades()
{
	camino = NULL;
	objetivo = NULL;
	setPosition(1,1);
	state = 0;
	select = false;
	last_clicked.X = 1;
	last_clicked.Y = 1;
	setTipo(3);
}

Unidades::Unidades(int x, int y)
{
	camino = NULL;
	objetivo = NULL;
	setPosition(x,y);
	state = 0;
	select = false;
	last_clicked.X = x;
	last_clicked.Y = y;
	setTipo(3);
}

Unidades::~Unidades()
{
	delete camino;
	setPosition(0,0);
	last_clicked.X = 0;
	last_clicked.Y = 0;
	select = false;
	state = 0;
}


void Unidades::Move(int x, int y)
{
	Move(pathfinding->calcularCamino(getPosition(),position2di(x,y)));
}

void Unidades::Move(Camino* _camino){
	if (_camino != NULL && _camino->getPeso() > 0)
	{
		state = MOVE;
		position2di pos = _camino->darPaso();
		setPosition(pos);
		camino = _camino;
	}
}

void Unidades::Move(Unidades* _objetivo){
	if(_objetivo != NULL){
		state = MOVE;
		objetivo = _objetivo;
		Move(_objetivo->getPosition().X,_objetivo->getPosition().Y);
	}
}

void Unidades::updateUnit()
{
	//position2di position = getPosition();
	if(state == MOVE)
	{
		if (objetivo != NULL)
		{
			Camino* nuevoCamino = pathfinding->calcularCamino(getPosition(),objetivo->getPosition());
			if (nuevoCamino == NULL || nuevoCamino->getFinal() != camino->getFinal())
			{
				delete camino;
				camino = nuevoCamino;
			}else{
				delete nuevoCamino;
			}
		
			if (camino == NULL || camino->getPeso() < 2)
			{
				objetivo = NULL;
			}
		}
		if (camino != NULL)
		{
			position2di nuevaPos = pathfinding->posicionDisponible(camino->getFinal());
			if (nuevaPos != camino->getFinal())
			{
				delete camino;
				camino = pathfinding->calcularCamino(getPosition(), nuevaPos);
			}
			Move(camino);
		}
		
		if (camino == NULL || camino->getPeso() <= 0)
		{
			if (camino)
			{
				delete camino;
				camino = NULL;
			}			
			state = NOTHING;
		}
	}
}

int Unidades::getState()
{
	return state;
}

int Unidades::Attack(Unidades* enemigo)
{
	cerr<<"Unidad: <"<<getPosition().X<<","<<getPosition().Y<<"> atacando a <"<<enemigo->getPosition().X<<","<<enemigo->getPosition().Y<<">"<<endl;
	int ataque = TrianguloArmas(enemigo);
	
	enemigo->PierdoVida(ataque+getAttackValue());
	return ataque+getAttackValue();
}

void Unidades::PierdoVida(int danyo)
{
	if(life-danyo<0)
	{
		life = 0;
		//DEBERIA DE MORIR
	}
	else
	{	
		life = life-danyo;
	}
}

//Saca tu factor de ataque
int Unidades::TrianguloArmas(Unidades* enemigo)
{
	switch(this->getType())
	{
		case 0:
			//Aldeano
			if(enemigo->getType()==0)
				return 2;
			if(enemigo->getType()==1 || enemigo->getType()==2 || enemigo->getType()==3)
				return 1;
			break;
		case 1:
			//Arquero
			if(enemigo->getType()==0)
				return 4;
			if(enemigo->getType()==1)
				return 2;
			if(enemigo->getType()==2)
				return 3;
			if(enemigo->getType()==3)
				return 1;
			break;
		case 2:
			//Espadachin
			if(enemigo->getType()==0)
				return 4;
			if(enemigo->getType()==1)
				return 1;
			if(enemigo->getType()==2)
				return 2;
			if(enemigo->getType()==3)
				return 3;
			break;
		case 3:
			//Lancero
			if(enemigo->getType()==0)
				return 4;
			if(enemigo->getType()==1)
				return 3;
			if(enemigo->getType()==2)
				return 1;
			if(enemigo->getType()==3)
				return 2;
			break;
		default:;
	};
	return 0;
}
