#include "pantallaIABatalla.h"


PantallaIABatalla::PantallaIABatalla(IrrlichtDevice * IrrDevice,graphicEngine * _grEngine,shared_ptr<mapa2D> _mapa):Pantalla(IrrDevice,_grEngine,_mapa){
	debug = NULL;
	pantallaDevice->setEventReceiver(this); 
}
PantallaIABatalla::~PantallaIABatalla(){

    //delete mapa;
    //delete debug;
}
void PantallaIABatalla::pintarPantalla(vector<IDibujable*>* ia_units,vector<IDibujable*>* user_units){

	if(mapa.get() == NULL)
	{
		cout<<"creando mapa"<<endl;
		mapa = shared_ptr<mapa2D>(new mapa2D(pantallaDevice,ia_units,user_units,true));
	}


	if(debug == NULL)
		debug = new DebugMenu(pantallaDevice,ia_units,mapa);

	pantallaDevice->getVideoDriver()->beginScene(true, true, SColor(0,200,200,200));
	mapa->Pintar();
	
	debug->Draw();
	pantallaDevice->getVideoDriver()->endScene();  

}

bool PantallaIABatalla::OnEvent(const SEvent& event){
	if(event.EventType == EET_KEY_INPUT_EVENT)
	{
		return Pantalla::OnEvent(event);
	}else{
		if(debug != NULL)
			return debug->OnEvent(event);
	}
	return false;
}