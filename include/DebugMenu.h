#ifndef DEBUG_H
#define DEBUG_H

#include <iostream>
#include <irrlicht.h>
#include <fmod.hpp>
#include <string>
#include <vector>
#include <memory>
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
	CB_VISION_RANGE = 0,
	CB_ATTACK_RANGE = 1,
	SCROLL_SPEED = 2,
	BUTTON_ADD_IA = 3,
	BUTTON_ADD_UNIT = 4,
	BUTTON_ADD_BUILDING = 5,
	SPBOX_COORDX = 6,
	SPBOX_COORDY = 7,
	COMBO_UNIDADES = 8
};

class mapa2D;

class DebugMenu : public IEventReceiver
{
private:
	vector<IDibujable*>* vUnits;

	IrrlichtDevice * DebugDevice;
	video::IVideoDriver* driver;
	gui::IGUIEnvironment* env;
	IGUIFont* font;
	/*Imagenes de estados del MEF*/
	video::ITexture* state_search;
	video::ITexture* state_approach;
	video::ITexture* state_attack;
	video::ITexture* state_flee;
	video::ITexture* state_recovery;

	shared_ptr<mapa2D> mapa;

	bool drawVision;
	bool drawAttackVision;




public:
	DebugMenu(IrrlichtDevice * IrrDevice,vector<IDibujable*>* ia_units,shared_ptr<mapa2D>);
	~DebugMenu();
	void initDebugMenu();
	void Draw();
	void DrawMEF();
	void DrawParameters();
	void DrawVisions();
	virtual bool OnEvent(const SEvent& event);
};

#endif