#include "battleIA.h"
#include "mapa2D.h"

battleIA::battleIA()
{
	stateIA = 0;
	stadoIA = new CurrentIA();
	setTipo(4);
}

battleIA::battleIA(int x, int y)
{
	setPosition(x,y);
	stateIA = 0;
	stadoIA = new CurrentIA();
	setTipo(4);
}

battleIA::~battleIA()
{
}

void battleIA::updateIA(std::shared_ptr<mapa2D> mapa)
{

	shared_ptr<IDibujable> casenemy = searchEnemy(mapa);
	
	stateIA=stadoIA->doSomething(this, casenemy);
	cout << "STADO ES -->" << stateIA;
	if(stateIA == 0)
	{
		cout << "SU STADO BELICO ES --> " << gameEngine::state_war_ia << endl;
		if(gameEngine::state_war_ia == 1)
		{
			//CC de usuario
			this->Move(9,7);
			this->setState(MOVE);
		}
		else if(gameEngine::state_war_ia == 2)
		{
			this->Move(177,192);
			this->setState(MOVE);
		}
	}
}

shared_ptr<IDibujable> battleIA::searchEnemy(std::shared_ptr<mapa2D> mapa)
{
	//Busca a un enemigo en su rango establecido y devuelve un puntero con un array de sus coordenadas
	position2di mypos = getPosition();
	
	int v_range = getVisionRange();
	
	//Bucle de busqueda en vector de mapa
	for(int x=mypos.X - v_range; x<=mypos.X + v_range; x++)
	{
		for(int y=mypos.Y - v_range; y<=mypos.Y + v_range; y++)
		{
			if(x>=0 && y>=0 && x<=WIDTH && y<=HEIGHT)
			{
				if(mapa->getTile(x,y)->getVinculado()!=NULL)
				{
					if(mapa->getTile(x,y)->getVinculado()->getTipo()==3)
					{
						return mapa->getTile(x,y);
					}
				}
			}
		}
	}
	
	return NULL;
}


int battleIA::getStateIA()
{
	return stateIA;
}

