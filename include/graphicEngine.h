#ifndef GRAPHICENGINE_H
#define GRAPHICENGINE_H

#include "mainMenu.h"
#include "gameEngine.h"
#include <iostream>
using namespace std;

class mainMenu;

class graphicEngine {
public:
	graphicEngine();
	~graphicEngine();
	int DrawMainMenu();

private:
	mainMenu* menu;
};

#endif