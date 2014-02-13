#ifndef GRAPHICENGINE_H
#define GRAPHICENGINE_H
#include "mainMenu.h"
#include "pausa.h"
#include "gameEngine.h"
#include "IDibujable.h"
#include "DebugMenu.h"
#include "pantalla.h"
#include <iostream>
#include <memory>
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
	void setPantalla(shared_ptr<Pantalla> _pantalla);

private:
	IrrlichtDevice * IrrDevice;
	mainMenu* menu;

	shared_ptr<Pantalla> pantalla;

	DebugMenu* debug;

	pausa* pause;
};

#endif
