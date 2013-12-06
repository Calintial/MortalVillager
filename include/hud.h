/*
	Clase para gestionar el hud
*/
#ifndef HUD_H
#define HUD_H
#include <iostream>
#include <irrlicht.h>
#include <fmod.hpp>
#include "IDibujable.h"
#include "Unidades.h"
#include "mapa2D.h"

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

using namespace std;
#define WIDTH 200
#define HEIGHT 200
class mapa2D;
class hud : public IEventReceiver
{
public:
	hud(IrrlichtDevice * IrrDevice, mapa2D *);
	~hud();
	void paint();
	void paintInformation(Unidades *);
	virtual bool OnEvent(const SEvent& event);
	int P1X,P1Y,P2X,P2Y;
	void pintarMiniMapa();
private:
	IrrlichtDevice * MenuDevice;
	video::IVideoDriver* driver;
	scene::ISceneManager* smgr;
	gui::IGUIEnvironment* env;
	IGUISkin* skin;
	IGUIFont* font;
	video::ITexture* images;
	Unidades * personaje;
	bool ensenyarInformacion;
	std::string mapa;
	mapa2D * _mapa2D;
};

#endif