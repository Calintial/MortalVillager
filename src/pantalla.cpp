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
    delete hudmapa;
}
int Pantalla::pintarPantalla(vector<IDibujable*>* ia_units,vector<IDibujable*>* user_units){

	if(mapa == NULL){
		
		mapa = new mapa2D(pantallaDevice,ia_units,user_units);
		hudmapa= new hud(pantallaDevice,mapa);
		
	}
	pantallaDevice->getVideoDriver()->beginScene(true, true, SColor(0,200,200,200));
	mapa->Pintar();
	hudmapa->paint();
	pantallaDevice->getVideoDriver()->endScene(); 

}
bool Pantalla::OnEvent(const SEvent& event){

	if (event.EventType == EET_MOUSE_INPUT_EVENT)
	{
		switch(event.MouseInput.Event)
		{
			case EMIE_LMOUSE_PRESSED_DOWN:
							if(event.MouseInput.X>=hudmapa->dimensionHUD1.X && event.MouseInput.X<=hudmapa->dimensionHUD2.X && event.MouseInput.Y >=hudmapa->dimensionHUD1.Y && event.MouseInput.Y<=hudmapa->dimensionHUD2.Y){
								cout<<"Has clicado en el minimapa en la posición X:"<<event.MouseInput.X<<", Y"<<event.MouseInput.Y<<endl;
							}
							else{
								hudmapa->paintInformation(mapa->OnEventMapa(event));
							}
							
							break;
		}
	}
	return false;
}