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
	GUI_BOTON_JUGAR = 0,
	GUI_BOTON_OPCIONES=1,
	GUI_BOTON_CREDITOS=2,
	GUI_BOTON_SALIR=3
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
		
	
		if (event.GUIEvent.EventType == EGET_BUTTON_CLICKED)
		{

			s32 id = event.GUIEvent.Caller->getID();
			IGUIEnvironment* env = Context.device->getGUIEnvironment();
			
			switch(id)
			{
				case 0:
					
					break;

				case 1:					
				
					break;

				case 2:
					
					break;
				case 3:	
					Context.device->closeDevice();
					exit(0);
					break;

				default:
					break;
			}
		}

		return false;
	}

private:
	SAppContext & Context;
};