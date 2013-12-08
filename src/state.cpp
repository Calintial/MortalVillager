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

void Current::doSomething(graphicEngine* graphics, intelEngine* ia)
{
	current->doSomething(graphics,ia);
}

//---MAINS--/
MAINS::MAINS()
{
	cout << "MAINS-ctor " << endl;
}

void MAINS::doSomething(graphicEngine* graphics, intelEngine* ia)
{
	graphics->DrawMainMenu();
	cout << "MOSTRARE MENU";
}

void MAINS::ingame(Current *c)
{
	cout << "cambio de MAINS a INGAME";
	c->setCurrent(new INGAME());
	delete this;
}

void MAINS::finish(Current *c)
{
	cout << "cambio de MAINS a FINISH";
	c->setCurrent(new FINISH());
	delete this;
}

//---INGAME--/
INGAME::INGAME()
{
	cout << "INGAME-ctor " << endl;
}

void INGAME::doSomething(graphicEngine* graphics, intelEngine* ia)
{
	gameEngine::addNewUnits();
	gameEngine::updatePlayer();
	ia->updateBattleIA();
	
	vector<IDibujable*> StIAUnits = gameEngine::getIAUnits();
	vector<IDibujable*> StUserUnits = gameEngine::getUserUnits();
	graphics->DrawMap(&StUserUnits,&StIAUnits);
	
	gameEngine::sleep(100-gameEngine::getSpeed());
	cout << "MOSTRARE PANTALLA DE JUEGO" << endl;
}


void INGAME::pause(Current *c)
{
	cout << "cambio de INGAME a PAUSE";
	c->setCurrent(new PAUSE());
	delete this;
}

//--PAUSE--//
PAUSE::PAUSE()
{
	cout << "PAUSE-ctor " << endl;
}

void PAUSE::doSomething(graphicEngine* graphics, intelEngine* ia)
{
	graphics->DrawPausa();
	cout << "MOSTRARE PANTALLA DE PAUSA" << endl;
}

void PAUSE::ingame(Current *c)
{
	cout << "cambio de PAUSE a INGAME";
	c->setCurrent(new INGAME());
	delete this;
}

void PAUSE::finish(Current *c)
{
	cout << "cambio de PAUSE a FINISH";
	c->setCurrent(new FINISH());
	delete this;
}

//--FINISH--//
