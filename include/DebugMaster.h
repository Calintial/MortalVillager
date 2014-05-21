#ifndef DEBUG_MASTER_H
#define DEBUG_MASTER_H

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


class mapa2D;

class DebugMaster : public IEventReceiver
{
private:
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
	DebugMaster(IrrlichtDevice * IrrDevice,shared_ptr<mapa2D>);
	~DebugMaster();
	void initDebugMenu();
	void Draw();
	void DrawMEF();
	void DrawParameters();
	void DrawVisions();
	virtual bool OnEvent(const SEvent& event);
};

#endif