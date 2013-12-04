#ifndef GRAPHICENGINE_H
#define GRAPHICENGINE_H

#include "mainMenu.h"
#include "mapa2D.h"
#include "gameEngine.h"
#include "IDibujable.h"
#include "DebugMenu.h"
#include <iostream>
using namespace std;

class mainMenu;
class mapa2D;
class DebugMenu;

const int dimensionPantallaX = 800;
const int dimensionPantallaY = 600;

class graphicEngine {
public:
	graphicEngine();
	~graphicEngine();
	int DrawMainMenu();
	int DrawMap(IDibujable**,IDibujable**);
private:
	IrrlichtDevice * IrrDevice;
	mainMenu* menu;
	mapa2D* mapa;
	DebugMenu* debug;
};

#endif
