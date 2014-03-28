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
	// position2di position = getPosition();
	// state = MOVE;
	// /*Moverse a una posicion establecida*/
	// if(x<400 && y<400)
	// {
	// 	if(x > position.X)
	// 		position.X++;
	// 	else if(x < position.X)
	// 		position.X--;

	// 	if(y > position.Y)
	// 		position.Y++;
	// 	else if(y < position.Y)
	// 		position.Y--;
			
	// 	setPosition(position);
	// 	last_clicked.X = x;
	// 	last_clicked.Y = y;		
	// }
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
		}

		if (camino->getPeso() < 2)
		{
			objetivo = NULL;
		}

		Move(camino);
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
