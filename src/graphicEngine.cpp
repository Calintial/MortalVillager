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

    //menu = new mainMenu(IrrDevice);
    //mapa = new mapa2D(IrrDevice);
}

graphicEngine::~graphicEngine()
{

	delete pantalla;

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

void graphicEngine::DrawMap(vector<IDibujable*>* ia_units,vector<IDibujable*>* user_units)
{
	if(pantalla == NULL){
		pantalla= new PantallaBasica(IrrDevice,this);
	}
	pantalla->pintarPantalla(ia_units,user_units);
	pause = NULL;
	menu = NULL;
}

void graphicEngine::setPantalla(Pantalla* _pantalla){
       delete pantalla;
       pantalla = _pantalla;
}
