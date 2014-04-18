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


bool Current::is_ingame()
{
	return current->is_ingame();
}

void Current::doSomething(gameEngine* ge, graphicEngine* graphics, intelEngine* ia, std::shared_ptr<mapa2D> mapa)
{
	current->doSomething(ge, graphics,ia,mapa);
}

//---MAINS--/
MAINS::MAINS()
{
	cout << "MAINS-ctor " << endl;
}

void MAINS::doSomething(gameEngine* ge, graphicEngine* graphics, intelEngine* ia, std::shared_ptr<mapa2D> mapa)
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

void INGAME::doSomething(gameEngine* ge, graphicEngine* graphics, intelEngine* ia, std::shared_ptr<mapa2D> mapa)
{
	ge->addNewUnits();
	ge->updatePlayer();
	ia->updateBattleIA(mapa);
	vector<IDibujable*>* StIAUnits = ge->getIAUnits();
	vector<IDibujable*>* StUserUnits = ge->getUserUnits();
	vector<IDibujable*>* StBuildingsUnits = ge->getBuildings();
	
	graphics->DrawMap(StIAUnits,StUserUnits,StBuildingsUnits);
	
	ge->sleep(100-gameEngine::getSpeed());
	//cout << "MOSTRAR PANTALLA DE JUEGO" << endl;
}


void INGAME::pause(Current *c)
{
	cout << "cambio de INGAME a PAUSE" << endl;
	c->setCurrent(new PAUSE());
	delete this;
}

void INGAME::finish(Current *c)
{
	cout << "cambio de INGAME a FINISH" << endl;
	c->setCurrent(new FINISH());
	delete this;
}


//--PAUSE--//
PAUSE::PAUSE()
{
	cout << "PAUSE-ctor " << endl;
}

void PAUSE::doSomething(gameEngine* ge, graphicEngine* graphics, intelEngine* ia, std::shared_ptr<mapa2D> mapa)
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
