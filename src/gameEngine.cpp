#include "gameEngine.h"

float gameEngine::volumen = 0.5;
int gameEngine::game_speed = 100;
Current gameEngine::stado;

vector<battleIA*> gameEngine::Add_IAUnits;
vector<Unidades*> gameEngine::Add_UserUnits;


gameEngine::gameEngine()
{
	battleIA* IAunit = new battleIA();
	battleIA* IAunit2 = new battleIA(10,10);
	IAUnits.push_back(IAunit);
	IAUnits.push_back(IAunit2);

	Unidades* unit = new Unidades(24,12);
	UserUnits.push_back(unit);

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
	char aux = 0;
	
	int i=0;
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

IDibujable* gameEngine::addIAUnit(int x,int y)
{	
	battleIA* new_unit = new battleIA(x,y);
	Add_IAUnits.push_back(new_unit);
	return new_unit;
}

IDibujable* gameEngine::addUserUnit(int x,int y)
{
	Unidades* new_unit = new Unidades(x,y);
	Add_UserUnits.push_back(new_unit);
	return new_unit;
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
}

