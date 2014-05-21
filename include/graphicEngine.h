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
	void DrawMap(vector<shared_ptr<IDibujable>>*,vector<shared_ptr<IDibujable>>*,vector<shared_ptr<IDibujable>>*);
	void DrawPausa();
	void setPantalla(Pantalla* _pantalla);
	video::IVideoDriver* getDriver(){return IrrDevice->getVideoDriver();};

//private:
	IrrlichtDevice * IrrDevice;
	mainMenu* menu;

	Pantalla* pantalla;

	DebugMenu* debug;

	pausa* pause;
	
	std::shared_ptr<mapa2D> mapa;
};

#endif
