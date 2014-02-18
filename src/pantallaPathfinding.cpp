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
Pantalla::Pantalla(IrrlichtDevice * IrrDevice){
	pantallaDevice= IrrDevice;
	mapa = NULL;
	interfazPathfinding = NULL;
	pantallaDevice->setEventReceiver(this); 
}
Pantalla::~Pantalla(){

    delete mapa;
    delete interfazPathfinding;
}
void Pantalla::pintarPantalla(vector<IDibujable*>* ia_units,vector<IDibujable*>* user_units){

	if(mapa == NULL){
		
		mapa = new mapa2D(pantallaDevice,ia_units,user_units,false);
		
	}
	if(interfazPathfinding == NULL){
		
		interfazPathfinding = new InterfazPathfinding(pantallaDevice,mapa);
		
	}
	pantallaDevice->getVideoDriver()->beginScene(true, true, SColor(0,200,200,200));
	mapa->Pintar();
	interfazPathfinding->Draw();
	pantallaDevice->getVideoDriver()->endScene(); 

}
bool Pantalla::OnEvent(const SEvent& event){

	return interfazPathfinding->OnEvent(event);
	
	//return false;
}
