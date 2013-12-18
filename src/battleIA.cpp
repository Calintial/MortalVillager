#include "battleIA.h"

CurrentIA battleIA::stadoIA;

battleIA::battleIA()
{
	state = 0;
	enemy_pos.X = -1;
	enemy_pos.Y = -1;
}

battleIA::battleIA(int x, int y)
{
	setPosition(x,y);
	state = 0;
	enemy_pos.X = -1;
	enemy_pos.Y = -1;
}

battleIA::~battleIA()
{
	//delete enemy_pos;
}

int battleIA::updateIA(vector<IDibujable*>* user)
{
	stadoIA.doSomething(this, user);
	/*switch(state)
	{
		case SEARCHING: state = this->searching(user);
						break;

		case APPROACH:  state = this->approach(user);
						break;

		case ATTACK: 	state = this->attack(user);
						break;

		case FLEE: 		state = this->flee(user);
						break;

		case RECOVERY:  state = this->recovery(user);
						break;
	}*/
}

int battleIA::searching(vector<IDibujable*>* user)
{
	//cout<<"Searching"<<endl;
	enemy_pos = this->searchEnemy(user);
	if(enemy_pos.X == -1 && enemy_pos.Y == -1)
	{
		return SEARCHING;
	}
	else
	{
		return APPROACH;
	}
}

int battleIA::approach(vector<IDibujable*>* user)
{
	//cout<<"Approach"<<endl;
	enemy_pos = this->searchEnemy(user);
	if(enemy_pos.X == -1 && enemy_pos.Y == -1)
	{
		return SEARCHING;
	}
	else
	{
		/*Comprobar si el enemigo está dentro de rango*/
		if(this->enemy_in_attack_range(enemy_pos))
		{
			return ATTACK;
		}
		else
		{
			this->Move(enemy_pos.X,enemy_pos.Y);
			return APPROACH;
		}

	}
}

int battleIA::attack(vector<IDibujable*>* user)
{
	//cout<<"Attack"<<endl;
	enemy_pos = this->searchEnemy(user);
	if(enemy_pos.X == -1 && enemy_pos.Y == -1)
	{
		return SEARCHING;
	}
	else
	{
		if(this->enemy_in_attack_range(enemy_pos) && this->getLife() > 25)
		{
			this->Attack(enemy_pos);
			return ATTACK;
		}
		else if(!this->enemy_in_attack_range(enemy_pos))
		{
			return APPROACH;
		}		
		else if(this->getLife() <= 25)
		{
			return FLEE;
		}
	}
}

int battleIA::flee(vector<IDibujable*>* user)
{
	//cout<<"Flee"<<endl;
	enemy_pos = this->searchEnemy(user);
	if(enemy_pos.X == -1 && enemy_pos.Y == -1)
	{
		return RECOVERY;
	}
	else
	{
		this->Move(0,0);
		return FLEE;
	}
}

int battleIA::recovery(vector<IDibujable*>* user)
{
	//cout<<"Recovery"<<endl;
	enemy_pos = this->searchEnemy(user);
	if(enemy_pos.X != -1 && enemy_pos.Y != -1)
	{
		return FLEE;
	}
	else
	{
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

}

position2di battleIA::searchEnemy(vector<IDibujable*>* vUnits)
{
	/*Busca a un enemigo en su rango establecido y devuelve un puntero con un array de sus coordenadas*/
	int nUnits = vUnits->size();
	position2di mypos = getPosition();
	position2di pos;
	int v_range = getVisionRange();
	for(int i=0; i<nUnits; i++)
	{
		pos = ((Unidades*)vUnits->at(i))->getPosition();

		for(int x = mypos.X - v_range; x <= mypos.X + v_range; x++)
		{
			for(int y = mypos.Y - v_range; y <= mypos.Y + v_range; y++)
			{
				if(pos.X == x && pos.Y == y)
				{
					return pos;
				}
			}
		}
	}
	pos.X = -1;
	pos.Y = -1;
	return pos;
}

void battleIA::Pintar(IVideoDriver* driver)
{
	setTextura(driver->getTexture("../media/Texturas/units/unit_test.png"));
}

int battleIA::getState()
{
	return state;
}
