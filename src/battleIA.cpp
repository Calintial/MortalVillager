#include "battleIA.h"

battleIA::battleIA()
{
	state = 0;
	enemy_pos = NULL;
}

battleIA::battleIA(int x, int y)
{
	setPosition(x,y);
	state = 0;
	enemy_pos = NULL;
}

battleIA::~battleIA()
{
	delete enemy_pos;
}

int battleIA::updateIA(Unidades** user)
{
	switch(state)
	{
		case SEARCHING: state = this->searching(user);
						break;

		case APPROACH:  state = this->approach(user);
						break;

		case ATTACK: 	state = this->attack(user);
						break;

		case FLEE: 		state = this->flee(user);
						break;

		case RECOVERY:  state = this->recovery();
						break;
	}
}

int battleIA::searching(Unidades** user)
{
	//cout<<"Searching"<<endl;
	enemy_pos = this->searchEnemy(user);
	if(enemy_pos == NULL)
	{
		return SEARCHING;
	}
	else
	{
		return APPROACH;
	}
}

int battleIA::approach(Unidades** user)
{
	cout<<"Approach"<<endl;
	enemy_pos = this->searchEnemy(user);
	if(enemy_pos == NULL)
	{
		return SEARCHING;
	}
	else
	{
		/*Comprobar si el enemigo está dentro de rango*/
		if(this->enemy_in_attack_range(enemy_pos[0],enemy_pos[1]))
		{
			return ATTACK;
		}
		else
		{
			this->Move(enemy_pos[0],enemy_pos[1]);
			return APPROACH;
		}

	}
}

int battleIA::attack(Unidades** user)
{
	cout<<"Attack"<<endl;
	enemy_pos = this->searchEnemy(user);
	if(enemy_pos == NULL)
	{
		return SEARCHING;
	}
	else
	{
		if(this->enemy_in_attack_range(enemy_pos[0],enemy_pos[1]) && this->getLife() > 25)
		{
			this->Attack(enemy_pos[0],enemy_pos[1]);
			return ATTACK;
		}
		else if(!this->enemy_in_attack_range(enemy_pos[0],enemy_pos[1]))
		{
			return APPROACH;
		}		
		else if(this->getLife() <= 25)
		{
			return FLEE;
		}
	}
}

int battleIA::flee(Unidades** user)
{
	cout<<"Flee"<<endl;
	enemy_pos = this->searchEnemy(user);
	if(enemy_pos == NULL)
	{
		return RECOVERY;
	}
	else
	{
		this->Move(0,0);
		return FLEE;
	}
}

int battleIA::recovery()
{
	cout<<"Recovery"<<endl;
	if(this->getLife() != 100)
	{
		this->Recovery();
		return RECOVERY;
	}
	else
	{
		return SEARCHING;
	}

}

int* battleIA::searchEnemy(Unidades** vUnits)
{
	/*Busca a un enemigo en su rango establecido y devuelve un puntero con un array de sus coordenadas*/
	int nUnits = gameEngine::getNumberUserUnits();
	int* mypos = getPosition();
	for(int i=0; i<nUnits; i++)
	{
		int* pos = vUnits[i]->getPosition();

		if((mypos[0] + 1 == pos[0] || mypos[0] + 2 == pos[0]) || (mypos[0] - 1 == pos[0] || mypos[0] -2 == pos[0]) ||
		   (mypos[1] + 1 == pos[1] || mypos[1] + 2 == pos[1]) || (mypos[1] - 1 == pos[1] || mypos[1] -2 == pos[1]))
		{
			return pos;
		}
	}
	return NULL;
}

void battleIA::Pintar(IVideoDriver* driver)
{
	setTextura(driver->getTexture("../media/Texturas/units/unit_test.png"));
}