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
	IDibujable* casenemy = searchEnemy(mapa);
	if(casenemy != NULL){
		stateIA=stadoIA->doSomething(this, casenemy);
	}
}

IDibujable* battleIA::searchEnemy(std::shared_ptr<mapa2D> mapa)
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


int battleIA::getState()
{
	return stateIA;
}

