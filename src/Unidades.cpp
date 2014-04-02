#include "Unidades.h"

Unidades::Unidades()
{
	camino = NULL;
	objetivo = NULL;
	posicionObjetivo = position2di(0,0);
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
	posicionObjetivo = position2di(0,0);
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
	posicionObjetivo = position2di(0,0);
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
			objetivo = NULL;
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
			pesoComprobacion = _camino->getPeso()/2;
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
		posicionObjetivo = objetivo->getPosition();
		Move(posicionObjetivo.X,posicionObjetivo.Y);
	}
}

void Unidades::updateUnit()
{
	//position2di position = getPosition();
	if(state == MOVE)
	{
		if (objetivo)
		{
			if (camino)
			{
				if (camino->getPeso() <= pesoComprobacion){
					position2di nuevaPos = objetivo->getPosition();
					if (nuevaPos != posicionObjetivo)
					{
						cout << "### NUEVAPOS OBJETIVO = <"<<nuevaPos.X<<","<<nuevaPos.Y<<">"<<endl;
						delete camino;
						camino = pathfinding->calcularCamino(getPosition(), nuevaPos);
						if (camino)
						{
							pesoComprobacion = camino->getPeso()/2;
						}
					}
				}
			}else{
				position2di nuevaPos = objetivo->getPosition();
				cout << "### NUEVAPOS OBJETIVO = <"<<nuevaPos.X<<","<<nuevaPos.Y<<">"<<endl;
				camino = pathfinding->calcularCamino(getPosition(), nuevaPos);
				if (camino)
				{
					pesoComprobacion = camino->getPeso()/2;
				}
			}	
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
						pesoComprobacion = camino->getPeso()/2;
					}
				}
			}
			Move(camino);
		}
		
		if ((camino == NULL || camino->getPeso() <= 0) && !objetivo)
		{
			if (camino)
			{
				delete camino;
				objetivo = NULL;
				posicionObjetivo = position2di(0,0);
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
