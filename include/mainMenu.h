#include <irrlicht.h>

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;


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
	void initOptionsMenu();
};