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

void CurrentIA::doSomething(battleIA bIA, vector<IDibujable*>* user)
{
	current->doSomething(bIA, user);
}


//---BUSCANDO--//
BUSCANDO::BUSCANDO()
{
	cout << "BUSCANDO-ctor " << endl;
}

void BUSCANDO::doSomething(battleIA bIA, vector<IDibujable*>* user)
{
	
}

void BUSCANDO::acercarse(CurrentIA *c)
{
	cout << "cambio de BUSCANDO a ACERCARSE" << endl;
	c->setCurrent(new ACERCARSE());
	delete this;
}

//---ACERCARSE--//
ACERCARSE::ACERCARSE()
{
	cout << "ACERCARSE-ctor " << endl;
}

void ACERCARSE::doSomething(battleIA bIA, vector<IDibujable*>* user)
{
	
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

void ATACAR::doSomething(battleIA bIA, vector<IDibujable*>* user)
{
	
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

void HUIR::doSomething(battleIA bIA, vector<IDibujable*>* user)
{
	
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

void RECUPERARSE::doSomething(battleIA bIA, vector<IDibujable*>* user)
{
	
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
	c->setCurrent(new HUIR());
	delete this;
}
