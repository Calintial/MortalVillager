#include "pantallaIABatalla.h"


PantallaIABatalla::PantallaIABatalla(IrrlichtDevice * IrrDevice,graphicEngine * _grEngine):Pantalla(IrrDevice,_grEngine){
	pantallaDevice= IrrDevice;
	mapa = NULL;
	debug = NULL;
}
PantallaIABatalla::~PantallaIABatalla(){

    delete mapa;
    delete debug;
}
void PantallaIABatalla::pintarPantalla(vector<IDibujable*>* ia_units,vector<IDibujable*>* user_units){

	if(mapa == NULL)
	{
		mapa = new mapa2D(pantallaDevice,ia_units,user_units,true);
	}


	if(debug == NULL)
		debug = new DebugMenu(pantallaDevice,ia_units,mapa);

	pantallaDevice->getVideoDriver()->beginScene(true, true, SColor(0,200,200,200));
	mapa->Pintar();
	
	debug->Draw();
	pantallaDevice->getVideoDriver()->endScene();  

}
