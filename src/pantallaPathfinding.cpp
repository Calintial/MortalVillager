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
	vision_texture = pantallaDevice->getVideoDriver()->getTexture("../media/Texturas/units/vision_distance.png");
}
Pantalla::~Pantalla(){

    delete mapa;
    delete interfazPathfinding;
}
void Pantalla::pintarPantalla(vector<IDibujable*>* ia_units,vector<IDibujable*>* user_units){

	if(mapa == NULL){
		
		mapa = new mapa2D(pantallaDevice,ia_units,user_units);
		
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

	if (event.EventType == EET_MOUSE_INPUT_EVENT)
	{
		if (event.MouseInput.X >= dimensionPantallaX || event.MouseInput.Y >= dimensionPantallaY)
		{

			return interfazPathfinding->OnEvent(event);
		}else{

			switch(event.MouseInput.Event)
			{
				case EMIE_LMOUSE_PRESSED_DOWN:
					{
						// Esto está copiapegado de mapa2D, cuidado por si cambia
						position2di pos_grid;
						pos_grid.X = (event.MouseInput.X) / TILE_WIDTH +1;
						pos_grid.Y = (event.MouseInput.Y) / TILE_HEIGHT +1;
						cout<<"Me has clicado en: "<< event.MouseInput.X << "," << event.MouseInput.Y << " - que corresponde a: "<< pos_grid.X<<","<<pos_grid.Y<<endl;
						Muro* muro = new Muro(1,pos_grid.X,pos_grid.Y);
						muro->aplicarTextura(pantallaDevice->getVideoDriver());
						mapa->setTile(pos_grid.X,pos_grid.Y,muro);
					}
					break;
				case EMIE_RMOUSE_PRESSED_DOWN:
					{
						// Esto está copiapegado de mapa2D, cuidado por si cambia
						position2di pos_grid;
						pos_grid.X = (event.MouseInput.X) / TILE_WIDTH+1;
						pos_grid.Y = (event.MouseInput.Y) / TILE_HEIGHT+1;
						cout<<"Me has clicado en: "<< event.MouseInput.X << "," << event.MouseInput.Y << " - que corresponde a: "<< pos_grid.X<<","<<pos_grid.Y<<endl;
						Suelo* suelo = new Suelo(0,pos_grid.X,pos_grid.Y);
						suelo->aplicarTextura(pantallaDevice->getVideoDriver());
						mapa->setTile(pos_grid.X,pos_grid.Y,suelo);
					}
					break;
			}
		}
	}
	else{
		
			return interfazPathfinding->OnEvent(event);
	}
	return false;
}