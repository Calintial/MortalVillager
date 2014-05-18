#include "pantallaIABatalla.h"


PantallaIABatalla::PantallaIABatalla(IrrlichtDevice * IrrDevice,graphicEngine * _grEngine,shared_ptr<mapa2D> _mapa, int tipo):Pantalla(IrrDevice,_grEngine,_mapa){
	debug = NULL;
	pantallaDevice->setEventReceiver(this);
	setTipo(tipo);
}
PantallaIABatalla::~PantallaIABatalla(){

    //delete mapa;
    delete debug;
}

void PantallaIABatalla::pintarPantalla(vector<shared_ptr<IDibujable>>* ia_units,vector<shared_ptr<IDibujable>>* user_units, vector<shared_ptr<IDibujable>>* buildings){


	if(mapa.get() == NULL)
	{
		cout<<"creando mapa"<<endl;
		mapa = shared_ptr<mapa2D>(new mapa2D(pantallaDevice,ia_units,user_units,buildings,true));
	}


	if(debug == NULL)
		debug = new DebugMenu(pantallaDevice,ia_units,mapa);

	pantallaDevice->getVideoDriver()->beginScene(true, true, SColor(0,200,200,200));
	mapa->Pintar();
	
	debug->Draw();
	pantallaDevice->getVideoDriver()->endScene();
	if(eliminar){
		delete this;
	}

}

bool PantallaIABatalla::OnEvent(const SEvent& event){
	if(event.EventType == EET_KEY_INPUT_EVENT)
	{
		cout<<"ok"<<endl;
		return Pantalla::OnEvent(event);
	}else{
		if(debug != NULL)
			return debug->OnEvent(event);
	}
	return false;
}
