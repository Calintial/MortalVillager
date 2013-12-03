#ifndef PAUSA_H
#define PAUSA_H

#include <iostream>
#include <irrlicht.h>
#include "gameEngine.h"

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

using namespace std;


enum{
	/*Elementos menu pausa*/
	GUI_PAUSA_BOTON_REANUDAR = 0,
	GUI_PAUSA_BOTON_SALIR=1
};


class pausa : public IEventReceiver
{
public:
	pausa(IrrlichtDevice * IrrDevice);
	~pausa();

	int run();
	virtual bool OnEvent(const SEvent& event);

private:
	IrrlichtDevice * PausaDevice;
	video::IVideoDriver* driver;
	gui::IGUIEnvironment* env;
	IGUISkin* skin;
	IGUIFont* font;
	video::ITexture* images;

	int gameState;

	void PintaPausa();
};

#endif
