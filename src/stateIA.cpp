#include "stateIA.h"

CurrentIA::CurrentIA()
{
	current = new BUSCANDO();
}
		
void CurrentIA::buscando()
{
	current->buscando(this);
}

void CurrentIA::acercarse()
{
	current->acercarse(this);
}

void CurrentIA::atacar()
{
	current->atacar(this);
}

void CurrentIA::huir()
{
	current->huir(this);
}

void CurrentIA::recuperarse()
{
	current->recuperarse(this);
}

bool CurrentIA::inicial()
{
	return current->inicial();
}

void CurrentIA::doSomething(battleIA* bIA, position2di enemy_pos)
{
	current->doSomething(bIA, enemy_pos);
}


//---BUSCANDO--//
BUSCANDO::BUSCANDO()
{
	cout << "BUSCANDO-ctor " << endl;
}

void BUSCANDO::doSomething(battleIA* bIA, position2di enemy_pos)
{
	cout << "BUSCANDO" << endl;
	if(!(enemy_pos.X == -1 && enemy_pos.Y == -1))
	{
		bIA->stadoIA->acercarse();
	}	
}

void BUSCANDO::acercarse(CurrentIA *c)
{
	//cout << "cambio de BUSCANDO a ACERCARSE" << endl;
	c->setCurrent(new ACERCARSE());
	delete this;
}

//---ACERCARSE--//
ACERCARSE::ACERCARSE()
{
	cout << "ACERCARSE-ctor " << endl;
}

void ACERCARSE::doSomething(battleIA* bIA, position2di enemy_pos)
{
	if(enemy_pos.X == -1 && enemy_pos.Y == -1)
	{
		bIA->stadoIA->buscando();
	}
	else
	{
		/*Comprobar si el enemigo está dentro de rango*/
		if(bIA->enemy_in_attack_range(bIA->enemy_pos))
		{
			bIA->stadoIA->atacar();
		}
		else
		{
			bIA->Move(bIA->enemy_pos.X,bIA->enemy_pos.Y);
		}
	}
}

void ACERCARSE::buscando(CurrentIA *c)
{
	cout << "cambio de ACERCARSE a BUSCANDO" << endl;
	c->setCurrent(new BUSCANDO());
	delete this;
}

void ACERCARSE::atacar(CurrentIA *c)
{
	cout << "cambio de ACERCARSE a ATACAR" << endl;
	c->setCurrent(new ATACAR());
	delete this;
}

//---ATACAR--//
ATACAR::ATACAR()
{
	cout << "ATACAR-ctor " << endl;
}

void ATACAR::doSomething(battleIA* bIA, position2di enemy_pos)
{
	if(!(enemy_pos.X == -1 && enemy_pos.Y == -1))
	{
		if(bIA->enemy_in_attack_range(bIA->enemy_pos) && bIA->getLife() > 25)
		{
			bIA->Attack(bIA->enemy_pos);
		}
		else if(!bIA->enemy_in_attack_range(bIA->enemy_pos))
		{
			bIA->stadoIA->acercarse();
		}		
		else if(bIA->getLife() <= 25)
		{
			bIA->stadoIA->huir();
		}
	}
	bIA->stadoIA->buscando();
	}

void ATACAR::buscando(CurrentIA *c)
{
	cout << "cambio de ATACAR a BUSCANDO" << endl;
	c->setCurrent(new BUSCANDO());
	delete this;
}

void ATACAR::acercarse(CurrentIA *c)
{
	cout << "cambio de ATACAR a ACERCARSE" << endl;
	c->setCurrent(new ACERCARSE());
	delete this;
}

void ATACAR::huir(CurrentIA *c)
{
	cout << "cambio de ATACAR a HUIR" << endl;
	c->setCurrent(new HUIR());
	delete this;
}

//---HUIR--//
HUIR::HUIR()
{
	cout << "HUIR-ctor " << endl;
}

void HUIR::doSomething(battleIA* bIA, position2di enemy_pos)
{
	if(enemy_pos.X == -1 && enemy_pos.Y == -1)
	{
		bIA->stadoIA->recuperarse();
	}
	else
	{
		bIA->Move(0,0);
	}
}

void HUIR::recuperarse(CurrentIA *c)
{
	cout << "cambio de HUIR a RECUPERARSE" << endl;
	c->setCurrent(new RECUPERARSE());
	delete this;
}


//---RECUPERARSE--//
RECUPERARSE::RECUPERARSE()
{
	cout << "RECUPERARSE-ctor " << endl;
}

void RECUPERARSE::doSomething(battleIA* bIA, position2di enemy_pos)
{
	if(enemy_pos.X != -1 && enemy_pos.Y != -1)
	{
		bIA->stadoIA->huir();
	}
	else
	{
		if(bIA->getLife() != 100)
		{
			bIA->Recovery();
		}
		else
		{
			bIA->stadoIA->buscando();
		}
	}
}

void RECUPERARSE::huir(CurrentIA *c)
{
	cout << "cambio de RECUPERARSE a HUIR" << endl;
	c->setCurrent(new HUIR());
	delete this;
}

void RECUPERARSE::buscando(CurrentIA *c)
{
	cout << "cambio de RECUPERARSE a BUSCANDO" << endl;
	c->setCurrent(new BUSCANDO());
	delete this;
}
