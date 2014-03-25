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

enum{
	COMBO_EDIFICIOS = 9,
};

class mapa2D;
class hud : public IEventReceiver
{
public:
	hud(IrrlichtDevice * IrrDevice, shared_ptr<mapa2D>);
	~hud();
	void paint();
	void paintInformation(vector<Unidades*>*);
	void dibujaEnHUD(int ,Unidades* );
	void dibujarRecursos();
	virtual bool OnEvent(const SEvent& event);
	int P1X,P1Y,P2X,P2Y;
	position2di dimensionHUD1;
	position2di dimensionHUD2;
	void pintarMiniMapa();
	void selectButton(int);
private:
	IrrlichtDevice * MenuDevice;
	video::IVideoDriver* driver;
	scene::ISceneManager* smgr;
	gui::IGUIEnvironment* env;
	IGUISkin* skin;
	IGUIFont* font;
	video::ITexture* images;
	vector<Unidades*>* personajes;
	bool ensenyarInformacion;
	std::string mapa;
	shared_ptr<mapa2D> _mapa2D;
	ITexture *hud_sprite;
	ITexture *hud_buttons;
	int button_selected;
};

#endif
