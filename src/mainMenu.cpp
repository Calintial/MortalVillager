#include "mainMenu.h"

mainMenu::mainMenu(){
	dimensionPantallaX=800;
    dimensionPantallaY=600;

	//Create an Irrlicht Device.
    MenuDevice = createDevice(EDT_OPENGL,dimension2d<u32>(dimensionPantallaX,dimensionPantallaY));

    env = MenuDevice->getGUIEnvironment();
    MenuDevice->setWindowCaption(L"Demo de Mortal Villager");
    MenuDevice->setResizable(true);

    //Get the Scene Manager from the MenuDevice.
    smgr = MenuDevice->getSceneManager();

    //Get the Video Driver from the MenuDevice.
    driver = MenuDevice->getVideoDriver();

    video::IVideoDriver* driver = MenuDevice->getVideoDriver();
    env = MenuDevice->getGUIEnvironment();

    start = false;
}

mainMenu::~mainMenu(){
	delete MenuDevice;
	delete driver;
	delete smgr;
	delete env;
	delete skin;
	delete font;
}

bool mainMenu::OnEvent(const SEvent& event)
{
	

	if (event.GUIEvent.EventType == EGET_BUTTON_CLICKED)
	{

		s32 id = event.GUIEvent.Caller->getID();
		IGUIEnvironment* env = MenuDevice->getGUIEnvironment();
		
		switch(id)
		{
			case GUI_BOTON_JUGAR:
				start = true;
				MenuDevice->closeDevice();
				break;

			case GUI_BOTON_OPCIONES:					
			
				break;

			case GUI_BOTON_CREDITOS:
				
				break;
			case GUI_BOTON_SALIR:	
				MenuDevice->closeDevice();
				exit(0);
				break;

			default:
				break;
		}
	}

	return false;
}

bool mainMenu::run(){
    //Cargar fondo del menu principal
    video::ITexture* images = driver->getTexture("../media/Imagenes/Fondo.png");
    skin = env->getSkin();
    font = env->getFont("../media/fonthaettenschweiler.bmp");
    if (font)
        skin->setFont(font);

    skin->setFont(env->getBuiltInFont(), EGDF_TOOLTIP);
        
    env->addButton(rect<s32>((dimensionPantallaX/2-100),dimensionPantallaY/2,(dimensionPantallaX/2+100),dimensionPantallaY/2 + 32), 0, GUI_BOTON_JUGAR,
        L"Jugar", L"Empezar partida");
    env->addButton(rect<s32>((dimensionPantallaX/2-100),dimensionPantallaY/2+40,(dimensionPantallaX/2+100),dimensionPantallaY/2 + 72), 0,GUI_BOTON_OPCIONES,
        L"Opciones", L"Opciones de juego");       
    env->addButton(rect<s32>((dimensionPantallaX/2-100),dimensionPantallaY/2+80,(dimensionPantallaX/2+100),dimensionPantallaY/2 + 112), 0, GUI_BOTON_CREDITOS,
        L"Creditos", L"Información del juego"); 
    env->addButton(rect<s32>((dimensionPantallaX/2-100),dimensionPantallaY/2+120,(dimensionPantallaX/2+100),dimensionPantallaY/2 + 152), 0, GUI_BOTON_SALIR,
        L"Salir", L"Salir del juego");

    MenuDevice->setEventReceiver(this); 
    while(MenuDevice->run() && driver)
    {
        if (MenuDevice->isWindowActive())
        {
            //Esta instrucción borra la pantalla y la repinta ;) (Cada vez que cambiemos de menu deberiamos usarla)
            driver->beginScene(true, true, SColor(0,200,200,200));

            //Pinta el fondo del menu principal
            driver->draw2DImage(images, core::position2d<s32>(0,0),
                core::rect<s32>(0,0,800 ,600), 0,
                video::SColor(255,255,255,255), true);

            //Pinta los botones antes definidos
            env->drawAll();

            driver->endScene();
        }
    }

    MenuDevice->drop();
    return start;
}