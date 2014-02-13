#include "pantallaIABatalla.h"


PantallaIABatalla::PantallaIABatalla(IrrlichtDevice * IrrDevice,graphicEngine * _grEngine,shared_ptr<mapa2D> _mapa):Pantalla(IrrDevice,_grEngine,_mapa){
	pantallaDevice= IrrDevice;
	debug = NULL;
}
PantallaIABatalla::~PantallaIABatalla(){

    //delete mapa;
    //delete debug;
}
void PantallaIABatalla::pintarPantalla(vector<IDibujable*>* ia_units,vector<IDibujable*>* user_units){

	if(mapa == NULL)
	{
		cout<<"creando mapa"<<endl;
		mapa = shared_ptr<mapa2D>(new mapa2D(pantallaDevice,ia_units,user_units,true));
	}


	if(debug == NULL)
		debug = shared_ptr<DebugMenu>(new DebugMenu(pantallaDevice,ia_units,mapa));

	pantallaDevice->getVideoDriver()->beginScene(true, true, SColor(0,200,200,200));
	mapa->Pintar();
	
	debug->Draw();
	pantallaDevice->getVideoDriver()->endScene();  

}
