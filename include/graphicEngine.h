#ifndef GRAPHICENGINE_H
#define GRAPHICENGINE_H
#include "mainMenu.h"
#include "pausa.h"
#include "gameEngine.h"
#include "IDibujable.h"
#include "DebugMenu.h"
#include <iostream>
#include "pantalla.h"
using namespace std;

class mainMenu;

class Pantalla;

class DebugMenu;

class pausa;

const int dimensionPantallaX = 800;
const int dimensionPantallaY = 600;

class graphicEngine {
public:
	graphicEngine();
	~graphicEngine();
	void DrawMainMenu();
	void DrawMap(vector<IDibujable*>*,vector<IDibujable*>*);
	void DrawPausa();

private:
	IrrlichtDevice * IrrDevice;
	mainMenu* menu;

	Pantalla * pantalla;

	DebugMenu* debug;

	pausa* pause;
};

#endif
