#include "mainMenu.h"

mainMenu::mainMenu(IrrlichtDevice * IrrDevice)
{
    credits = false;

    //dimensionPantallaX=800;
    //dimensionPantallaY=600;

    //Create an Irrlicht Device.
    //MenuDevice = createDevice(EDT_OPENGL,dimension2d<u32>(dimensionPantallaX,dimensionPantallaY),16,false,false,false,0);

	MenuDevice = IrrDevice;

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

    //Init sound engine
    FMOD::System_Create(&system);
    system->init(32, FMOD_INIT_NORMAL, 0);

    system->createSound("../media/Sonido/blop.mp3", FMOD_HARDWARE, 0, &sound1);
    sound1->setMode(FMOD_LOOP_OFF);

    gameState = MAIN;  

    initMainMenu();
}

mainMenu::~mainMenu()
{
	//delete MenuDevice;
	delete driver;
	//delete smgr;
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
			case GUI_MENU_BOTON_JUGAR:
                 gameState = INGAME;
				 break;

			case GUI_MENU_BOTON_OPCIONES:					
			     initOptionsMenu();
				 break;

			case GUI_MENU_BOTON_CREDITOS:
                 initCreditsMenu();
				 break;

			case GUI_MENU_BOTON_SALIR:	
                 gameState = FINISH;
				 break;

            case GUI_OPCIONES_BOTON_ATRAS:
                 initMainMenu();
                 break;
		}
	}
    else if(event.GUIEvent.EventType == EGET_SCROLL_BAR_CHANGED)
    {
        s32 id = event.GUIEvent.Caller->getID();
        IGUIEnvironment* env = MenuDevice->getGUIEnvironment();

        switch(id)
        {
            case GUI_OPCIONES_SCROLL_SONIDO: 
                 s32 pos = ((IGUIScrollBar*)event.GUIEvent.Caller)->getPos();
                 gameEngine::setVolume(pos/100.0);

                 //Emitir un sonido
                 FMOD::Channel* channel;
                 system->getChannel(0,&channel);
                 system->playSound(FMOD_CHANNEL_FREE, sound1, false, &channel);
                 channel->setVolume(pos/100.0);
                 channel->setPaused(false);
                 system->update();
                 break;

        }        
    }

	return false;
}

int mainMenu::run()
{
    if (MenuDevice->run())
    {        
        if(MenuDevice->isWindowActive() && driver)
        {
            //Esta instrucción borra la pantalla y la repinta ;) (Cada vez que cambiemos de menu deberiamos usarla)
            driver->beginScene(true, true, SColor(0,200,200,200));

            //Pinta el fondo del menu principal
            driver->draw2DImage(images, core::position2d<s32>(0,0),
                core::rect<s32>(0,0,800 ,600), 0,
                video::SColor(255,255,255,255), true);

            //Si estamos en la pantalla de creditos, pintamos el texto
            if(credits)
            {
                font->draw(L"Juego creado por el grupo Calintial",
                    core::rect<s32>((dimensionPantallaX/2-100),dimensionPantallaY/2,(dimensionPantallaX/2+100),dimensionPantallaY/2 + 72),
                    video::SColor(255,255,255,255));

                font->draw(L"Silvia De Gregorio Medrano",
                    core::rect<s32>((dimensionPantallaX/2-100),dimensionPantallaY/2+20,(dimensionPantallaX/2+100),dimensionPantallaY/2 + 72),
                    video::SColor(255,255,255,255));

                font->draw(L"Victor Guzmán Pedrajas",
                    core::rect<s32>((dimensionPantallaX/2-100),dimensionPantallaY/2+40,(dimensionPantallaX/2+100),dimensionPantallaY/2 + 72),
                    video::SColor(255,255,255,255));

                font->draw(L"Adrián Medina Gonzalez",
                    core::rect<s32>((dimensionPantallaX/2-100),dimensionPantallaY/2+60,(dimensionPantallaX/2+100),dimensionPantallaY/2 + 72),
                    video::SColor(255,255,255,255));

                font->draw(L"Adrián Escolano Díaz",
                    core::rect<s32>((dimensionPantallaX/2-100),dimensionPantallaY/2+80,(dimensionPantallaX/2+100),dimensionPantallaY/2 + 72),
                    video::SColor(255,255,255,255));            
            }


            //Pinta los botones antes definidos
            env->drawAll();

            driver->endScene();
        }

    }
    else
    {
        gameState = FINISH;
    }

    if(gameState != MAIN)
    {
        if(sound1 != NULL)
        {
            sound1->release();
            system->close();
            system->release();
            sound1 = NULL;
        }
        //MenuDevice->drop();
    }
    return gameState;
}

void  mainMenu::initMainMenu()
{
    credits = false;
    env->clear();

    env->addButton(rect<s32>((dimensionPantallaX/2-100),dimensionPantallaY/2,(dimensionPantallaX/2+100),dimensionPantallaY/2 + 32), 0, GUI_MENU_BOTON_JUGAR,
        L"Jugar", L"Empezar partida");
    env->addButton(rect<s32>((dimensionPantallaX/2-100),dimensionPantallaY/2+40,(dimensionPantallaX/2+100),dimensionPantallaY/2 + 72), 0,GUI_MENU_BOTON_OPCIONES,
        L"Opciones", L"Opciones de juego");       
    env->addButton(rect<s32>((dimensionPantallaX/2-100),dimensionPantallaY/2+80,(dimensionPantallaX/2+100),dimensionPantallaY/2 + 112), 0, GUI_MENU_BOTON_CREDITOS,
        L"Creditos", L"Información del juego"); 
    env->addButton(rect<s32>((dimensionPantallaX/2-100),dimensionPantallaY/2+120,(dimensionPantallaX/2+100),dimensionPantallaY/2 + 152), 0, GUI_MENU_BOTON_SALIR,
        L"Salir", L"Salir del juego");
}

void mainMenu::initOptionsMenu()
{
    env->clear();
    env = MenuDevice->getGUIEnvironment();

    IGUIScrollBar* volume_bar = env->addScrollBar(true,rect<s32>((dimensionPantallaX/2-100),dimensionPantallaY/2,(dimensionPantallaX/2+100),dimensionPantallaY/2 + 32), 0, GUI_OPCIONES_SCROLL_SONIDO);

    volume_bar->setPos(gameEngine::getVolume() * 100);

    env->addButton(rect<s32>((dimensionPantallaX/2-100),dimensionPantallaY/2+40,(dimensionPantallaX/2+100),dimensionPantallaY/2 + 72), 0, GUI_OPCIONES_BOTON_ATRAS,
        L"Volver", L"Volver al menu principal");
}

void mainMenu::initCreditsMenu()
{
    credits = true;

    env->clear();

    env->addButton(rect<s32>((dimensionPantallaX/2-100),dimensionPantallaY/2+120,(dimensionPantallaX/2+100),dimensionPantallaY/2 + 152), 0, GUI_OPCIONES_BOTON_ATRAS,
        L"Volver", L"Volver al menu principal");

}
