// Facade pattern to separate graphic engine from the rest of the game
#include "mainMenu.h"
#include "gameScreen.h"
#include <iostream>

class graphicEngine {
public:
	graphicEngine();
	~graphicEngine();
	/*graphicEngine(const graphicEngine&) {};
	graphicEngine& operator=(const graphicEngine&) {};*/
	bool updateOnce();
	bool pintarMenu();
	//void pintarCubo();

private:
	mainMenu menu;
	gameScreen* game;
};
