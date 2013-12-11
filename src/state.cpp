#include "state.h"

Current::Current()
{
	current = new MAINS();
}

void Current::main()
{
	current->main(this);
}

void Current::ingame()
{
	current->ingame(this);
}

void Current::pause()
{
	current->pause(this);
}

void Current::finish()
{
	current->finish(this);
}

bool Current::inicial()
{
	return current->inicial();
}

bool Current::sfinal()
{
	return current->sfinal();
}

void Current::doSomething(gameEngine* ge, graphicEngine* graphics, intelEngine* ia)
{
	current->doSomething(ge, graphics,ia);
}

//---MAINS--/
MAINS::MAINS()
{
	cout << "MAINS-ctor " << endl;
}

void MAINS::doSomething(gameEngine* ge, graphicEngine* graphics, intelEngine* ia)
{
	graphics->DrawMainMenu();
	//cout << "MOSTRAR MENU";
}

void MAINS::ingame(Current *c)
{
	cout << "cambio de MAINS a INGAME" << endl;
	c->setCurrent(new INGAME());
	delete this;
}

void MAINS::finish(Current *c)
{
	cout << "cambio de MAINS a FINISH" << endl;
	c->setCurrent(new FINISH());
	delete this;
}

//---INGAME--/
INGAME::INGAME()
{
	cout << "INGAME-ctor " << endl;
}

void INGAME::doSomething(gameEngine* ge, graphicEngine* graphics, intelEngine* ia)
{
	ge->addNewUnits();
	ge->updatePlayer();
	ia->updateBattleIA();
	
	vector<IDibujable*> StIAUnits = ge->getIAUnits();
	vector<IDibujable*> StUserUnits = ge->getUserUnits();
	
	graphics->DrawMap(&StIAUnits,&StUserUnits);
	
	ge->sleep(100-gameEngine::getSpeed());
	//cout << "MOSTRAR PANTALLA DE JUEGO" << endl;
}


void INGAME::pause(Current *c)
{
	cout << "cambio de INGAME a PAUSE" << endl;
	c->setCurrent(new PAUSE());
	delete this;
}

//--PAUSE--//
PAUSE::PAUSE()
{
	cout << "PAUSE-ctor " << endl;
}

void PAUSE::doSomething(gameEngine* ge, graphicEngine* graphics, intelEngine* ia)
{
	graphics->DrawPausa();
	//cout << "MOSTRAR PANTALLA DE PAUSA" << endl;
}

void PAUSE::ingame(Current *c)
{
	cout << "cambio de PAUSE a INGAME" << endl;
	c->setCurrent(new INGAME());
	delete this;
}

void PAUSE::finish(Current *c)
{
	cout << "cambio de PAUSE a FINISH" << endl;
	c->setCurrent(new FINISH());
	delete this;
}

//--FINISH--//
