#include "pantallaPathfinding.h"
#include <string>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <string>

using namespace irr;
using namespace video;
using namespace std;
using namespace core;
PantallaPathfinding::PantallaPathfinding(IrrlichtDevice * IrrDevice,graphicEngine * _grEngine,shared_ptr<mapa2D> _mapa, int tipo):Pantalla(IrrDevice,_grEngine,_mapa){
	interfazPathfinding = NULL;
	pantallaDevice->setEventReceiver(this);
	setTipo(tipo);
}
PantallaPathfinding::~PantallaPathfinding(){

    //delete mapa;
    delete interfazPathfinding;
}

void PantallaPathfinding::pintarPantalla(vector<shared_ptr<IDibujable>>* ia_units,vector<shared_ptr<IDibujable>>* user_units,vector<shared_ptr<IDibujable>>* buildings){

	if(mapa.get() == NULL){
		cout<<"creando mapa"<<endl;
		mapa = shared_ptr<mapa2D>(new mapa2D(pantallaDevice,ia_units,user_units,buildings,false));
		
	}
	if(interfazPathfinding == NULL){
		
		interfazPathfinding = new InterfazPathfinding(pantallaDevice,mapa);
		
	}
	pantallaDevice->getVideoDriver()->beginScene(true, true, SColor(0,200,200,200));
	mapa->Pintar();
	interfazPathfinding->Draw();
	pantallaDevice->getVideoDriver()->endScene();
	if(eliminar){
		delete this;
	}

}
bool PantallaPathfinding::OnEvent(const SEvent& event){

	if(event.EventType == EET_KEY_INPUT_EVENT)
	{
		return Pantalla::OnEvent(event);
	}else{
		if (interfazPathfinding != NULL)
		{
			return interfazPathfinding->OnEvent(event);
		}
		
	}
	
	return false;
}
