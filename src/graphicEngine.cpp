#include "graphicEngine.h"

graphicEngine::graphicEngine()
{
    //Create an Irrlicht Device.
    IrrDevice = createDevice(EDT_OPENGL,dimension2d<u32>(dimensionPantallaX,dimensionPantallaY),16,false,false,false,0);
	IrrDevice->setWindowCaption(L"Demo de Mapa Mortal Villager");
    //IrrDevice->setResizable(true);
	
pantalla=NULL;
    //menu = new mainMenu(IrrDevice);
    //mapa = new mapa2D(IrrDevice);
}

graphicEngine::~graphicEngine()
{
	delete pantalla;
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
    return status;
    
}

int graphicEngine::DrawMap(IDibujable** ia_units,IDibujable** user_units)
{
	if(pantalla == NULL){
		pantalla= new Pantalla(IrrDevice);
	}
	pantalla->pintarPantalla(ia_units,user_units);
	/*
	if(mapa == NULL){
		mapa = new mapa2D(IrrDevice,ia_units,user_units);
		hudmap= new hud(IrrDevice);
	}

	IrrDevice->getVideoDriver()->beginScene(true, true, SColor(0,200,200,200));

	mapa->Pintar();
	hudmap->paint();

	IrrDevice->getVideoDriver()->endScene();   
*/
	int status = INGAME;
	return status;
}
