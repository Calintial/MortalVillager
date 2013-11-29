#ifndef GRAPHICENGINE_H
#define GRAPHICENGINE_H
#include "mainMenu.h"
#include "gameEngine.h"
#include "IDibujable.h"
#include <iostream>
#include "pantalla.h"
using namespace std;

class mainMenu;
class Pantalla;

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
	Pantalla * pantalla;
	
};

#endif
