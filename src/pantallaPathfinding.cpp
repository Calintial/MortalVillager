#include "pantalla.h"
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
	pantallaDevice->setEventReceiver(this); 
}
Pantalla::~Pantalla(){

    delete mapa;
}
int Pantalla::pintarPantalla(vector<IDibujable*>* ia_units,vector<IDibujable*>* user_units){

	if(mapa == NULL){
		
		mapa = new mapa2D(pantallaDevice,ia_units,user_units);
		
	}
	pantallaDevice->getVideoDriver()->beginScene(true, true, SColor(0,200,200,200));
	mapa->Pintar();
	pantallaDevice->getVideoDriver()->endScene(); 

}
bool Pantalla::OnEvent(const SEvent& event){

	if (event.EventType == EET_MOUSE_INPUT_EVENT)
	{
		switch(event.MouseInput.Event)
		{
			case EMIE_LMOUSE_PRESSED_DOWN:
							
				cout<<"Me has clicado!"<<endl;
				break;
		}
	}
	return false;
}