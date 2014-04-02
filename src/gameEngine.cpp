#include "gameEngine.h"
#include "AldeanoDemo.h"

float gameEngine::volumen = 0.5;
int gameEngine::game_speed = 100;
Current gameEngine::stado;

vector<battleIA*> gameEngine::Add_IAUnits;
vector<Unidades*> gameEngine::Add_UserUnits;
vector<edificio*> gameEngine::Add_Buildings;

int gameEngine::recursos_jugador = 1000;
int gameEngine::recursos_ia = 1000;

gameEngine::gameEngine()
{
	/*battleIA* IAunit = new battleIA();
	battleIA* IAunit2 = new battleIA(10,10);
	IAUnits.push_back(IAunit);
	IAUnits.push_back(IAunit2);*/

	/*Unidades* unit = new Unidades(24,12);
	UserUnits.push_back(unit);*/

	gameState = 0;

	graphics = new graphicEngine();

	ia = new intelEngine(&IAUnits,&UserUnits);

}

gameEngine::~gameEngine()
{
	delete graphics;
}

void gameEngine::run()
{
	//Bucle principal del juego. Mientras el estado no cambia a FINISH el programa no termina.
	//En cada estado se llamará a los motores necesarios(IA,Graficos,etc...)
	while(!stado.sfinal())
	{
		stado.doSomething(this, graphics,ia);
	}
	/*while(gameState != FINISH)
	{
		switch(gameState)
		{
			
			case MAIN: gameState = graphics->DrawMainMenu();
					   break;

			case INGAME: addNewUnits();
					     updatePlayer();
						 ia->updateBattleIA();

						 gameState = graphics->DrawMap(&IAUnits,&UserUnits);
						 this->sleep(100-game_speed);
						 break;

			case PAUSE: gameState = graphics->DrawPausa();
						break;
			default: break;
		}		
	}*/
}

void gameEngine::setVolume(float vol)
{
	volumen = vol;
}

float gameEngine::getVolume()
{
	return volumen;
}

void gameEngine::updatePlayer()
{
	for(IDibujable* u : UserUnits)
	{
		((Unidades*)u)->updateUnit();
	}

}

void gameEngine::sleep(unsigned int mseconds)
{
    clock_t goal = (mseconds*(CLOCKS_PER_SEC/1000)) + clock();
    while (goal > clock());
}

void gameEngine::setSpeed(int speed)
{
	game_speed = speed;
}

int gameEngine::getSpeed()
{
	return game_speed;
}

IDibujable* gameEngine::addIAUnit(int x,int y,int tipo)
{	
	battleIA* new_unit;
	switch(tipo)
	{
		case 0: new_unit = new AldeanoIA(x,y); break;
		case 1: new_unit = new EspadachinIA(x,y); break;
		case 2: new_unit = new LanceroIA(x,y); break;
		case 3: new_unit = new ArqueroIA(x,y); break;
		case 4: new_unit = new AldeanoDemo(position2di(25,150),position2di(175,150)); break;

		
	}
	
	Add_IAUnits.push_back(new_unit);
	return new_unit;
}

IDibujable* gameEngine::addUserUnit(int x,int y, int tipo)
{
	Unidades* new_unit;
	switch(tipo)
	{
		case 0: new_unit = new Aldeano(x,y); break;
		case 1: new_unit = new Espadachin(x,y); break;
		case 2: new_unit = new Lancero(x,y); break;
		case 3: new_unit = new Arquero(x,y); break;
		
	}

	Add_UserUnits.push_back(new_unit);
	return new_unit;
}

IDibujable* gameEngine::addBuildings(int x,int y, int tipo)
{
	edificio* new_build;
	switch(tipo)
	{
		case 0: new_build = new CentroCiudad(x,y); break;
		case 1: new_build = new Granja(x,y); break;
		case 2: new_build = new Cuartel(x,y); break;
		case 3: new_build = new Arqueria(x,y); break;
		case 4: new_build = new Lanceria(x,y); break;
		
	}

	Add_Buildings.push_back(new_build);
	return new_build;
}

void gameEngine::addNewUnits()
{
	for(battleIA* ia : Add_IAUnits)
	{
		IAUnits.push_back(ia);
	}
	Add_IAUnits.clear();
	for(Unidades* unit : Add_UserUnits)
	{
		UserUnits.push_back(unit);
	}
	Add_UserUnits.clear();
	for(edificio* build : Add_Buildings)
	{
		buildings.push_back(build);
	}
	Add_Buildings.clear();
}

