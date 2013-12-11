#ifndef INTERFAZ_PF_H
#define INTERFAZ_PF_H

#include <iostream>
#include <irrlicht.h>
#include <fmod.hpp>
#include <string>
#include <vector>
#include "graphicEngine.h"
#include "mapa2D.h"

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

using namespace std;

enum{
	/*Estados de la IA*/
	CB_REGIONES = 0,
	CB_ENLACES = 1,
	CB_CAMINOS_INTERNOS = 2,
	CB_CAMINO_FINAL = 3,
	BUTTON_NEXT = 4
};

class InterfazPathfinding  : public IEventReceiver
{
private:
	IrrlichtDevice * device;
	video::IVideoDriver* driver;
	gui::IGUIEnvironment* env;
	IGUIFont* font;

	mapa2D* mapa;

	bool drawRegiones, drawEnlaces, drawCaminosInternos, drawCaminoFinal;
public:
	InterfazPathfinding(IrrlichtDevice * IrrDevice,mapa2D*);
	~InterfazPathfinding();

	void Draw();
	void init();
	virtual bool OnEvent(const SEvent& event);
};

#endif