#include "battleIA.h"

battleIA::battleIA()
{
	state = 0;
	enemy_pos = NULL;
}

battleIA::~battleIA()
{
	delete enemy_pos;
}

int battleIA::updateIA()
{
	switch(state)
	{
		case SEARCHING: state = this->searching();
						break;

		case APPROACH:  state = this->approach();
						break;

		case ATTACK: 	state = this->attack();
						break;

		case FLEE: 		state = this->flee();
						break;

		case RECOVERY:  state = this->recovery();
						break;
	}
}

int battleIA::searching()
{
	cout<<"Searching"<<endl;
	enemy_pos = this->searchEnemy();
	if(enemy_pos == NULL)
	{
		return SEARCHING;
	}
	else
	{
		return APPROACH;
	}
}

int battleIA::approach()
{
	cout<<"Approach"<<endl;
	enemy_pos = this->searchEnemy();
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

int battleIA::attack()
{
	cout<<"Attack"<<endl;
	enemy_pos = this->searchEnemy();
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

int battleIA::flee()
{
	cout<<"Flee"<<endl;
	enemy_pos = this->searchEnemy();
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
	return SEARCHING;
}