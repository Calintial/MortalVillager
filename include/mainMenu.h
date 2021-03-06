#ifndef MAINMENU_H
#define MAINMENU_H

#include <iostream>
#include <irrlicht.h>
#include <fmod.hpp>
#include "gameEngine.h"

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

using namespace std;


enum{
	/*Elementos menu principal*/
	GUI_MENU_BOTON_JUGAR = 0,
	GUI_MENU_BOTON_OPCIONES=1,
	GUI_MENU_BOTON_CREDITOS=2,
	GUI_MENU_BOTON_SALIR=3,

	/*Elementos menu opciones*/
	GUI_OPCIONES_SCROLL_SONIDO=4,
	GUI_OPCIONES_COMBO_WIREFRAME=5,
	GUI_OPCIONES_BOTON_ATRAS=6,
};


class mainMenu : public IEventReceiver
{
public:
	mainMenu(IrrlichtDevice * IrrDevice);
	~mainMenu();

	void run();
	virtual bool OnEvent(const SEvent& event);

private:
	IrrlichtDevice * MenuDevice;
	video::IVideoDriver* driver;
	gui::IGUIEnvironment* env;
	IGUISkin* skin;
	IGUIFont* font;
	video::ITexture* images;

	FMOD::System* system; 
    FMOD::Sound* sound1, *sound2;

	bool credits;

	void initMainMenu();
	void initOptionsMenu();
	void initCreditsMenu();
};

#endif
