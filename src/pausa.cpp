#include "pausa.h"

pausa::pausa(IrrlichtDevice * IrrDevice)
{
	PausaDevice = IrrDevice;

    env = IrrDevice->getGUIEnvironment();
    env->clear();

    //Get the Scene Manager from the MenuDevice.
    //smgr = IrrDevice->getSceneManager();

    //Get the Video Driver from the MenuDevice.
    driver = IrrDevice->getVideoDriver();

    video::IVideoDriver* driver = IrrDevice->getVideoDriver();
    

    //Cargar fondo del menu principal
    images = driver->getTexture("../media/Imagenes/Fondo.png");
    skin = env->getSkin();
    font = env->getFont("../media/fonthaettenschweiler.bmp");
    if (font)
        skin->setFont(font);

    skin->setFont(env->getBuiltInFont(), EGDF_TOOLTIP);

    IrrDevice->setEventReceiver(this); 

    gameEngine::stado.pause();

    PintaPausa();
}

pausa::~pausa()
{
	//delete MenuDevice;
	delete driver;
	//delete smgr;
	delete env;
	delete skin;
	delete font;
}

bool pausa::OnEvent(const SEvent& event)
{
	if (event.GUIEvent.EventType == EGET_BUTTON_CLICKED)
	{
		s32 id = event.GUIEvent.Caller->getID();
		IGUIEnvironment* env = PausaDevice->getGUIEnvironment();
		
		switch(id)
		{
			case GUI_PAUSA_BOTON_REANUDAR :
				gameEngine::stado.ingame();
				cout << "INGAME" << endl;
				env->clear();
				
				break;

			case GUI_PAUSA_BOTON_SALIR :	
				gameEngine::stado.finish();
				break;
		}
	}

	return false;
}

void pausa::run()
{
    if (PausaDevice->run())
    {        
        if(PausaDevice->isWindowActive() && driver)
        {
            //Esta instrucción borra la pantalla y la repinta ;) (Cada vez que cambiemos de menu deberiamos usarla)
            driver->beginScene(true, true, SColor(0,200,200,200));

            //Pinta el fondo del menu principal
            driver->draw2DImage(images, core::position2d<s32>(0,0),
                core::rect<s32>(0,0,800 ,600), 0,
                video::SColor(30,255,255,255), true);


            //Pinta los botones antes definidos
            env->drawAll();

            driver->endScene();
        }

    }
    else
    {
        gameEngine::stado.finish();
    }
}

void pausa::PintaPausa()
{
	env->clear();
	
	env->addButton(rect<s32>((dimensionPantallaX/2-100),dimensionPantallaY/2,(dimensionPantallaX/2+100),dimensionPantallaY/2 + 32), 0, GUI_PAUSA_BOTON_REANUDAR,
        L"Reanudar", L"Reanudar partida");
    env->addButton(rect<s32>((dimensionPantallaX/2-100),dimensionPantallaY/2+40,(dimensionPantallaX/2+100),dimensionPantallaY/2 + 72), 0,GUI_PAUSA_BOTON_SALIR,
        L"Salir", L"Salir del juego");    
}
