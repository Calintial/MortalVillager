#include "pantallaIABatalla.h"


Pantalla::Pantalla(IrrlichtDevice * IrrDevice){
	pantallaDevice= IrrDevice;
	mapa = NULL;
	debug = NULL;
	(gameEngine::addIAUnit(0,0,0))->aplicarTextura(pantallaDevice->getVideoDriver());
	(gameEngine::addIAUnit(10,10,0))->aplicarTextura(pantallaDevice->getVideoDriver());
	(gameEngine::addUserUnit(24,12,0))->aplicarTextura(pantallaDevice->getVideoDriver());
	(gameEngine::addBuildings(15,15,0))->aplicarTextura(pantallaDevice->getVideoDriver());
}
Pantalla::~Pantalla(){

    delete mapa;
    delete debug;
}
void Pantalla::pintarPantalla(vector<IDibujable*>* ia_units,vector<IDibujable*>* user_units, vector<IDibujable*>* buildings){

	if(mapa == NULL)
	{
		mapa = new mapa2D(pantallaDevice,ia_units,user_units,buildings,true);
	}


	if(debug == NULL)
		debug = new DebugMenu(pantallaDevice,ia_units,mapa);

	pantallaDevice->getVideoDriver()->beginScene(true, true, SColor(0,200,200,200));
	mapa->Pintar();
	
	debug->Draw();
	pantallaDevice->getVideoDriver()->endScene();  

}
