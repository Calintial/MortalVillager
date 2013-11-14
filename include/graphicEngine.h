#ifndef GRAPHICENGINE_H
#define GRAPHICENGINE_H

#include "mainMenu.h"
#include "mapa2D.h"
#include "gameEngine.h"
#include <iostream>
using namespace std;

class mainMenu;
class mapa2D;

class graphicEngine {
public:
	graphicEngine();
	~graphicEngine();
	int DrawMainMenu();
	int DrawMap();

private:
	mainMenu* menu;
	mapa2D* mapa;
};

#endif
