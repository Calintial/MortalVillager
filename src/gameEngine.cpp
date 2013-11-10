#include "gameEngine.h"

gameEngine::gameEngine()
{
	gameState = MAIN;
	graphics = new graphicEngine();
}

gameEngine::~gameEngine()
{
	delete graphics;
}

void gameEngine::run()
{
	//Bucle principal del juego. Mientras el estado no cambia a FINISH el programa no termina.
	//En cada estado se llamará a los motores necesarios(IA,Graficos,etc...)
	while(gameState != FINISH)
	{
		switch(gameState)
		{
			
			case MAIN: gameState = graphics->DrawMainMenu();
					   break;
			case INGAME: cout<<"Jugando"<<endl; break;
			case PAUSE: break;
			default: break;
		}
	}
}
