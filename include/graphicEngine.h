// Facade pattern to separate graphic engine from the rest of the game
#include <irrlicht.h>

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace irr;
using namespace gui;

class graphicEngine {
public:
	graphicEngine();
	~graphicEngine() {};
	graphicEngine(const graphicEngine&) {};
	graphicEngine& operator=(const graphicEngine&) {};
	bool updateOnce();
	void pintarMenu();
	void pintarCubo();

private:
	IrrlichtDevice * device;
	ISceneManager * smgr;
	IVideoDriver * driver;
	ISceneNode * node;
	IGUIEnvironment* env;
	s32				counter;
	IGUIListBox*	listbox;
	int dimensionPantallaX; 
	int dimensionPantallaY; 
	IGUISkin* skin;
	IGUIFont* font;
};
enum{
	GUI_BOTON_JUGAR = 101,
	GUI_BOTON_OPCIONES,
	GUI_BOTON_CREDITOS,
	GUI_BOTON_SALIR
};
struct SAppContext
{
	IrrlichtDevice *device;

};

class MyEventReceiver : public IEventReceiver
{
public:
	MyEventReceiver(SAppContext & context) : Context(context) { }

	virtual bool OnEvent(const SEvent& event)
	{
		printf("Hola");
	/*
		if (event.EventType == EET_GUI_EVENT)
		{
			s32 id = event.GUIEvent.Caller->getID();
			IGUIEnvironment* env = Context.device->getGUIEnvironment();

			switch(event.GUIEvent.EventType)
			{

			case GUI_BOTON_JUGAR:
				
				break;

			case GUI_BOTON_OPCIONES:					
			
				break;

			case GUI_BOTON_CREDITOS:
				
				break;
			case GUI_BOTON_SALIR:
				//Context.device->closeDevice();
				break;

			default:
				break;
			}
		}
*/
		return false;
	}

private:
	SAppContext & Context;
};