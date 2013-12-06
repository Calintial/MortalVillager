#ifndef GAMEENGINE_H
#define GAMEENGINE_H
#include <irrlicht.h>
#include <iostream>

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

class gameScreen : public IEventReceiver
{
public:
	gameScreen();
	~gameScreen();

	bool run();
	virtual bool OnEvent(const SEvent& event);
private:
	IrrlichtDevice * GameDevice;
	video::IVideoDriver* driver;
	scene::ISceneManager* smgr;
	gui::IGUIEnvironment* env;
	IGUISkin* skin;
	IGUIFont* font;
	ISceneNode * node;

	int dimensionPantallaX; 
	int dimensionPantallaY; 
};
#endif