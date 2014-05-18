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


	//TODO ESTO SE TIENE QUE PINTAR CUANDO SE PINTE TO
    /*(gameEngine::addIAUnit(0,0,0))->aplicarTextura(IrrDevice->getVideoDriver());
    (gameEngine::addIAUnit(10,10,0))->aplicarTextura(IrrDevice->getVideoDriver());
    (gameEngine::addUserUnit(24,12,0))->aplicarTextura(IrrDevice->getVideoDriver());
    (gameEngine::addUserUnit(30,15,0))->aplicarTextura(IrrDevice->getVideoDriver());
    (gameEngine::addUserUnit(40,20,0))->aplicarTextura(IrrDevice->getVideoDriver());
    (gameEngine::addUserUnit(34,17,0))->aplicarTextura(IrrDevice->getVideoDriver());*/
    (gameEngine::addBuildings(16,3,0))->aplicarTextura(IrrDevice->getVideoDriver());

    // aldeano demo, se pasa por el forro el x y el y que le pases
    (gameEngine::addIAUnit(10,10,4))->aplicarTextura(IrrDevice->getVideoDriver());

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

void graphicEngine::DrawMap(vector<shared_ptr<IDibujable>>* ia_units,vector<shared_ptr<IDibujable>>* user_units,vector<shared_ptr<IDibujable>>* buildings)
{
	if(mapa.get() == NULL){
		cout<<"creando mapa"<<endl;
		mapa = shared_ptr<mapa2D>(new mapa2D(IrrDevice,ia_units,user_units,buildings,false));
	}
	if(pantalla == NULL){
		pantalla= new PantallaBasica(IrrDevice,this, mapa,0);
	}
	pantalla->pintarPantalla(ia_units,user_units,buildings);
	pause = NULL;
	menu = NULL;
}

void graphicEngine::setPantalla(Pantalla* _pantalla){
	pantalla->dispose();
	pantalla = _pantalla;
}
