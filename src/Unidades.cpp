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
	setTipo(3);
	pesoComprobacion = 0;
	eliminar_unidad = false;
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
	setTipo(3);
	pesoComprobacion = 0;
	eliminar_unidad = false;
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
	eliminar_unidad = false;
}


void Unidades::Move(int x, int y)
{
	bool newPath = true;
	if (camino)
	{
		if (camino->getFinal().X == x && camino->getFinal().Y == y)
		{
			cout<<"ok"<<endl;
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
		if(state != DEAD)
			state = MOVE;
		position2di pos = _camino->darPaso();
		setPosition(pos);
		camino = _camino;
	}
}

void Unidades::Move(shared_ptr<Unidades> _objetivo){
	if(_objetivo != NULL){
		if(state != DEAD)
			state = MOVE;
		objetivo = _objetivo;
		posicionObjetivo = objetivo->getPosition();
		Move(posicionObjetivo.X,posicionObjetivo.Y);
	}
}

void Unidades::Move(shared_ptr<edificio> _objetivo){
	if(_objetivo != NULL){
		if(state != DEAD)
			state = MOVE;
		CC_Objetivo = _objetivo;
		posicionObjetivo = _objetivo->getPosition();
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
			CC_Objetivo = NULL;
			if(enemy_in_attack_range(objetivo->getPosition()))
			{
				if(state != DEAD)
					state = ATTACKING;
				delete camino;
				camino = NULL;
			}
			else if (camino)
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
		else if(CC_Objetivo)
		{
			objetivo = NULL;
			if(CC_in_range(CC_Objetivo->getPosition()))
			{
				cerr<<"ATACAR CENTRO CIUDAD!"<<endl;
				if(state != DEAD)
					state = ATTACKING;
				delete camino;
				camino = NULL;
			}
			else if (camino)
			{
				if (camino->getPeso() <= pesoComprobacion){
					position2di nuevaPos = CC_Objetivo->getPosition();
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
				position2di nuevaPos = CC_Objetivo->getPosition();
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
		
		if ((camino == NULL || camino->getPeso() <= 0) && !objetivo && !CC_Objetivo)
		{
			if (camino)
			{
				delete camino;
				objetivo = NULL;
				CC_Objetivo = NULL;
				posicionObjetivo = position2di(0,0);
				camino = NULL;
			}
			if(state != DEAD)		
				state = NOTHING;
		}
	}
	else if(state == ATTACKING)
	{
		if(CC_Objetivo)
		{
			if(CC_in_range(CC_Objetivo->getPosition()))
			{
				shared_ptr<CentroCiudad> Centro_Ciudad = std::dynamic_pointer_cast<CentroCiudad>(CC_Objetivo);

				Centro_Ciudad->PierdoVida(getAttackValue());
			}
		}
		else if(objetivo)
		{
			if(enemy_in_attack_range(objetivo->getPosition()))
			{
				Attack(objetivo);
			}
		}
		else
		{
			if(state != DEAD)
				state = NOTHING;
			objetivo = NULL;
		}
	}
}

int Unidades::getState()
{
	return state;
}

int Unidades::Attack(shared_ptr<Unidades> enemigo)
{
//	cerr<<"Unidad: <"<<getPosition().X<<","<<getPosition().Y<<"> atacando a <"<<enemigo->getPosition().X<<","<<enemigo->getPosition().Y<<">"<<endl;
	int ataque = TrianguloArmas(enemigo);
	
	enemigo->PierdoVida(ataque+getAttackValue());
	return ataque+getAttackValue();
}

void Unidades::PierdoVida(int danyo)
{
	if(life-danyo<0)
	{
		life = 0;
		state = DEAD;
	}
	else
	{	
		life = life-danyo;
	}
}

//Saca tu factor de ataque
int Unidades::TrianguloArmas(shared_ptr<Unidades> enemigo)
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

bool Unidades::CC_in_range(position2di pos)
{
	position2di mypos = getPosition();

	for(int x = mypos.X - 1; x <= mypos.X + 1; x++)
	{
		for(int y = mypos.Y - 1; y <= mypos.Y + 1; y++)
		{
			for(int i = pos.X; i < pos.X +3; i++)
			{
				for(int j = pos.Y; j < pos.Y +3; j++)
				{
					if(i == x && j == y)
					{
						return true;
					}
				}
			}
		}
	}
	return false;


}
