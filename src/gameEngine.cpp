#include "gameEngine.h"

float gameEngine::volumen = 0.5;
int gameEngine::game_speed = 100;
vector<battleIA*> gameEngine::IAUnits;
vector<Unidades*> gameEngine::UserUnits;

gameEngine::gameEngine()
{
	battleIA* IAunit = new battleIA();
	battleIA* IAunit2 = new battleIA(10,10);
	IAUnits.push_back(IAunit);
	IAUnits.push_back(IAunit2);

	Unidades* unit = new Unidades(24,18);
	UserUnits.push_back(unit);

	
	gameState = MAIN;

	graphics = new graphicEngine();



	ia = new intelEngine(&IAUnits[0],&UserUnits[0]);
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
	while(gameState != FINISH)
	{
		switch(gameState)
		{
			
			case MAIN: gameState = graphics->DrawMainMenu();
					   break;

			case INGAME: updatePlayer();
						 ia->updateBattleIA();
						 gameState = graphics->DrawMap((IDibujable**)&IAUnits[0],(IDibujable**)&UserUnits[0]);
						 this->sleep(100-game_speed);
						 break;

			case PAUSE: break;
			default: break;
		}
		
	}
}

void gameEngine::setVolume(float vol)
{
	volumen = vol;
}

float gameEngine::getVolume()
{
	return volumen;
}

int gameEngine::getNumberIAUnits()
{
	return IAUnits.size();
}

int gameEngine::getNumberUserUnits()
{
	return UserUnits.size();
}

void gameEngine::updatePlayer()
{
	for(Unidades* u : UserUnits)
	{
		u->updateUnit();
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