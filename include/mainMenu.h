#include <irrlicht.h>

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;


enum{
	GUI_BOTON_JUGAR = 0,
	GUI_BOTON_OPCIONES=1,
	GUI_BOTON_CREDITOS=2,
	GUI_BOTON_SALIR=3
};

class mainMenu : public IEventReceiver
{
public:
	mainMenu();
	~mainMenu();

	bool run();
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

	bool start;

	void initMainMenu();
};