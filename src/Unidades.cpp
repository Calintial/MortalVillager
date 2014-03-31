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
	pesoComprobacion = 0;
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
	pesoComprobacion = 0;
}

Unidades::~Unidades()
{
	delete camino;
	setPosition(0,0);
	last_clicked.X = 0;
	last_clicked.Y = 0;
	select = false;
	state = 0;
	pesoComprobacion = 0;
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
	bool newPath = true;
	if (camino)
	{
		if (camino->getFinal().X == x && camino->getFinal().Y == y)
		{
			updateUnit();
			newPath = false;
		}else{
			delete camino;
			newPath = true;
		}
	}
	if (newPath)
	{
		pesoComprobacion = 0;
		Move(pathfinding->calcularCamino(getPosition(),position2di(x,y)));
	}
}

void Unidades::Move(Camino* _camino){
	if (_camino != NULL && _camino->getPeso() > 0)
	{
		if (camino == NULL || camino->getPeso() <= 0)
		{
			pesoComprobacion = _camino->getPeso()/3;
		}
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
		if (objetivo && camino)
		{
			if (camino->getPeso() <= pesoComprobacion){
				position2di nuevaPos = pathfinding->posicionDisponible(objetivo->getPosition());
				if (nuevaPos != camino->getFinal())
				{
					delete camino;
					camino = pathfinding->calcularCamino(getPosition(), nuevaPos);
					if (camino)
					{
						pesoComprobacion = camino->getPeso()/3;
					}
				}
			}

			/*if (camino == NULL || camino->getPeso() < 1)
			{
				objetivo = NULL;
			}*/
		}
		if (camino)
		{
			if (camino->getPeso() <= pesoComprobacion)
			{
				position2di nuevaPos = pathfinding->posicionDisponible(camino->getFinal());
				if (nuevaPos != camino->getFinal())
				{
					delete camino;
					camino = pathfinding->calcularCamino(getPosition(), nuevaPos);
					if (camino)
					{
						pesoComprobacion = camino->getPeso()/3;
					}
				}
			}
			Move(camino);
		}
		
		if (camino == NULL || camino->getPeso() <= 0)
		{
			if (camino)
			{
				delete camino;
				objetivo = NULL;
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
