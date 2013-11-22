#include "graphicEngine.h"

graphicEngine::graphicEngine()
{
    //Create an Irrlicht Device.
    IrrDevice = createDevice(EDT_OPENGL,dimension2d<u32>(dimensionPantallaX,dimensionPantallaY),16,false,false,false,0);
	IrrDevice->setWindowCaption(L"Demo de Mapa Mortal Villager");
    IrrDevice->setResizable(true);
	
	menu = NULL;
	mapa = NULL;
    //menu = new mainMenu(IrrDevice);
    //mapa = new mapa2D(IrrDevice);
}

graphicEngine::~graphicEngine()
{
    delete menu;
    delete mapa;
}

//Funcion encargada de pintar el menu principal
int graphicEngine::DrawMainMenu()
{
	if(menu == NULL)
		menu = new mainMenu(IrrDevice);
		//hudmap= new hud(IrrDevice);
    int status = menu->run();
    
    /*if(status == INGAME)
		DrawMap();*/
    
}

int graphicEngine::DrawMap()
{
	if(mapa == NULL){
		mapa = new mapa2D(IrrDevice);
		hudmap= new hud(IrrDevice);
	}
	int status = INGAME;
}
