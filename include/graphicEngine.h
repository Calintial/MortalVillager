#ifndef GRAPHICENGINE_H
#define GRAPHICENGINE_H
#include "mainMenu.h"
#include "mapa2D.h"
#include "gameEngine.h"
#include "hud.h"
#include <iostream>
using namespace std;

class mainMenu;
class mapa2D;

const int dimensionPantallaX = 800;
const int dimensionPantallaY = 600;

class graphicEngine {
public:
	graphicEngine();
	~graphicEngine();
	int DrawMainMenu();
	int DrawMap();

private:
	IrrlichtDevice * IrrDevice;
	mainMenu* menu;
	mapa2D* mapa;
	hud * hudmap;
};

#endif
