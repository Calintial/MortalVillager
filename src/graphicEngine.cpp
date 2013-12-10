#include "graphicEngine.h"

graphicEngine::graphicEngine()
{
    //Create an Irrlicht Device.
    IrrDevice = createDevice(EDT_OPENGL,dimension2d<u32>(dimensionPantallaX+2166,dimensionPantallaY+178),16,false,false,false,0);
	IrrDevice->setWindowCaption(L"Demo de Mapa Mortal Villager");
    IrrDevice->setResizable(true);


	menu = NULL;
	mapa = NULL;
	debug = NULL;
	pantalla = NULL;
    //menu = new mainMenu(IrrDevice);
    //mapa = new mapa2D(IrrDevice);
}

graphicEngine::~graphicEngine()
{
    delete menu;
    delete mapa;
    delete debug;
}

//Funcion encargada de pintar el menu principal
int graphicEngine::DrawMainMenu()
{
	if(menu == NULL)
		menu = new mainMenu(IrrDevice);
		
    int status = menu->run();
    
    /*if(status == INGAME)
		DrawMap();*/
    return status;
    
}

int graphicEngine::DrawMap(vector<IDibujable*>* ia_units,vector<IDibujable*>* user_units)
{

	if(pantalla == NULL){
	    pantalla= new Pantalla(IrrDevice);
	}

	int status = pantalla->pintarPantalla(ia_units,user_units);


	return status;
}
