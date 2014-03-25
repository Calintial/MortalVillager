#include "Unidades.h"

Unidades::Unidades()
{
	setPosition(1,1);
	state = 0;
	last_clicked.X = 1;
	last_clicked.Y = 1;
}

Unidades::Unidades(int x, int y)
{
	setPosition(x,y);
	state = 0;
	last_clicked.X = x;
	last_clicked.Y = y;
}

Unidades::~Unidades()
{
	setPosition(0,0);
	last_clicked.X = 0;
	last_clicked.Y = 0;
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

void Unidades::updateUnit()
{
	//position2di position = getPosition();
	if(state == MOVE)
	{
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
