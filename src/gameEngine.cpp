#include "gameEngine.h"

float gameEngine::volumen = 0.5;

gameEngine::gameEngine()
{
	gameState = MAIN;
	graphics = new graphicEngine();

	vector<battleIA*> units;
	battleIA* unit = new battleIA();
	units.push_back(unit);
	ia = new intelEngine(units);
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

			case INGAME: cout<<"Jugando"<<endl; gameState = graphics->DrawMap(); ia->updateBattleIA();break;

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
