#include "graphicEngine.h"
#include "pantallaBasica.h"

graphicEngine::graphicEngine()
{
    //Create an Irrlicht Device.
    IrrDevice = createDevice(EDT_OPENGL,dimension2d<u32>(dimensionPantallaX,dimensionPantallaY),16,false,false,false,0);
	IrrDevice->setWindowCaption(L"Demo de Mapa Mortal Villager");

    //IrrDevice->setResizable(true);
	
	pantalla=NULL;

    IrrDevice->setResizable(true);


	menu = NULL;

	debug = NULL;
	
	pause = NULL;

    (gameEngine::addIAUnit(0,0,0))->aplicarTextura(IrrDevice->getVideoDriver());
    (gameEngine::addIAUnit(10,10,0))->aplicarTextura(IrrDevice->getVideoDriver());
    (gameEngine::addUserUnit(24,12,0))->aplicarTextura(IrrDevice->getVideoDriver());
    (gameEngine::addUserUnit(30,15,0))->aplicarTextura(IrrDevice->getVideoDriver());
    (gameEngine::addUserUnit(40,20,0))->aplicarTextura(IrrDevice->getVideoDriver());
    (gameEngine::addUserUnit(34,17,0))->aplicarTextura(IrrDevice->getVideoDriver());
    (gameEngine::addBuildings(16,3,0))->aplicarTextura(IrrDevice->getVideoDriver());

    //menu = new mainMenu(IrrDevice);
    //mapa = new mapa2D(IrrDevice);
}

graphicEngine::~graphicEngine()
{

	//delete pantalla;

    delete menu;

    delete debug;
    
	delete pause;

}

//Funcion encargada de pintar el menu principal
void graphicEngine::DrawMainMenu()
{
	if(menu == NULL)
		menu = new mainMenu(IrrDevice);
    menu->run();
}


void graphicEngine::DrawPausa()
{
	if(pause == NULL)
		pause = new pausa(IrrDevice);
		
    pause->run();
}

void graphicEngine::DrawMap(vector<IDibujable*>* ia_units,vector<IDibujable*>* user_units, vector<IDibujable*>* buildings)
{
	if(pantalla == NULL){
		pantalla= new PantallaBasica(IrrDevice,this, NULL,0);
	}
	pantalla->pintarPantalla(ia_units,user_units,buildings);
	pause = NULL;
	menu = NULL;
}

void graphicEngine::setPantalla(Pantalla* _pantalla){
	pantalla->dispose();
	pantalla = _pantalla;
}
