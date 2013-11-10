#ifndef MAINMENU_H
#define MAINMENU_H

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
	/*Elementos menu principal*/
	GUI_MENU_BOTON_JUGAR = 0,
	GUI_MENU_BOTON_OPCIONES=1,
	GUI_MENU_BOTON_CREDITOS=2,
	GUI_MENU_BOTON_SALIR=3,

	/*Elementos menu opciones*/
	GUI_OPCIONES_SONIDO=4,
	GUI_OPCIONES_COMBO_WIREFRAME=5
};


class mainMenu : public IEventReceiver
{
public:
	mainMenu();
	~mainMenu();

	int run();
	virtual bool OnEvent(const SEvent& event);

private:
	IrrlichtDevice * MenuDevice;
	video::IVideoDriver* driver;
	scene::ISceneManager* smgr;
	gui::IGUIEnvironment* env;
	IGUISkin* skin;
	IGUIFont* font;
	video::ITexture* images;

	int dimensionPantallaX; 
	int dimensionPantallaY; 

	int gameState;

	void initMainMenu();
	void initOptionsMenu();
};

#endif