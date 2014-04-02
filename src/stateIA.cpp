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

int CurrentIA::doSomething(battleIA* bIA, IDibujable* &casilla)
{
	int st = current->doSomething(bIA, casilla);
	return st;
}


//---BUSCANDO--//
BUSCANDO::BUSCANDO()
{
	cout << "BUSCANDO-ctor " << endl;
}

int BUSCANDO::doSomething(battleIA* bIA, IDibujable* &casilla)
{
	Unidades* enemy = (Unidades*)casilla->getVinculado();
	if(!(enemy->getPosition().X == -1 && enemy->getPosition().Y == -1))
	{
		bIA->stadoIA->acercarse();
	}
	return SEARCHING;
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

int ACERCARSE::doSomething(battleIA* bIA, IDibujable* &casilla)
{
	Unidades* enemy = (Unidades*)casilla->getVinculado();
	if(enemy->getPosition().X == -1 && enemy->getPosition().Y == -1)
	{
		bIA->stadoIA->buscando();
	}
	else
	{
		/*Comprobar si el enemigo está dentro de rango*/
		if(bIA->enemy_in_attack_range(enemy->getPosition()))
		{
			bIA->stadoIA->atacar();
		}
		else
		{
			bIA->Move(enemy);
		}
	}
	
	return APPROACH;
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

int ATACAR::doSomething(battleIA* bIA, IDibujable* &casilla)
{
	Unidades* enemy = (Unidades*)casilla->getVinculado();
	if(!(enemy->getPosition().X == -1 && enemy->getPosition().Y == -1))
	{
		if(bIA->enemy_in_attack_range(enemy->getPosition()) && bIA->getLife() > 25)
		{
			 int danyo = bIA->Attack(enemy);
		}
		else if(!bIA->enemy_in_attack_range(enemy->getPosition()))
		{
			bIA->stadoIA->acercarse();
		}		
		else if(bIA->getLife() <= 25)
		{
			bIA->stadoIA->huir();
		}
	}
	bIA->stadoIA->buscando();
	
	
	cout << "ATTACK" << endl;
	return ATTACK;
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

int HUIR::doSomething(battleIA* bIA, IDibujable* &casilla)
{
	Unidades* enemy = (Unidades*)casilla->getVinculado();
	cout << "HUIR" << endl;
	if(enemy->getPosition().X == -1 && enemy->getPosition().Y == -1)
	{
		bIA->stadoIA->recuperarse();
	}
	else
	{
		bIA->Move(0,0);
	}
	
	return FLEE;
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

int RECUPERARSE::doSomething(battleIA* bIA, IDibujable* &casilla)
{
	Unidades* enemy = (Unidades*)casilla->getVinculado();
	if(enemy->getPosition().X != -1 && enemy->getPosition().Y != -1)
	{
		bIA->stadoIA->huir();
	}
	else
	{	
		//cout << "VIDA:" << bIA->getLife() << endl;
		if(bIA->getLife() != 100)
		{
			bIA->Recovery();
		}
		else
		{
			bIA->stadoIA->buscando();
		}
	}
	
	return RECOVERY;
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
