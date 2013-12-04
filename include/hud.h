/*
	Clase para gestionar el hud
*/
#ifndef HUD_H
#define HUD_H
#include <iostream>
#include <irrlicht.h>
#include <fmod.hpp>


using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

using namespace std;

class hud : public IEventReceiver
{
public:
	hud(IrrlichtDevice * IrrDevice);
	~hud();
	void paint();
	void paintInformation();
	virtual bool OnEvent(const SEvent& event);
	void infoPersonaje(int infoX, int infoY);
	int P1X,P1Y,P2X,P2Y;
private:
	IrrlichtDevice * MenuDevice;
	video::IVideoDriver* driver;
	scene::ISceneManager* smgr;
	gui::IGUIEnvironment* env;
	IGUISkin* skin;
	IGUIFont* font;
	video::ITexture* images;
	
};

#endif