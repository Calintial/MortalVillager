#include "pantallaBasica.h"

PantallaBasica::PantallaBasica(IrrlichtDevice * IrrDevice,graphicEngine * _grEngine,shared_ptr<mapa2D> _mapa):Pantalla(IrrDevice,_grEngine,_mapa){
	pantallaDevice->setEventReceiver(this);
	hudmapa = NULL;
}

PantallaBasica::~PantallaBasica()
{
    //delete mapa;
    delete hudmapa;
}

void PantallaBasica::pintarPantalla(vector<IDibujable*>* ia_units,vector<IDibujable*>* user_units)
{
	if(mapa.get() == NULL){
		cout<<"creando mapa"<<endl;
		mapa = shared_ptr<mapa2D>(new mapa2D(pantallaDevice,ia_units,user_units,false));
	}
	if(hudmapa == NULL){
		hudmapa= new hud(pantallaDevice,mapa);
	}
	pantallaDevice->getVideoDriver()->beginScene(true, true, SColor(0,200,200,200));
	pantallaDevice->setEventReceiver(this); 
	mapa->Pintar();
	hudmapa->paint();
	pantallaDevice->getVideoDriver()->endScene();
	if(eliminar){
		delete this;
	}

}

bool PantallaBasica::OnEvent(const SEvent& event){
	if (event.EventType == EET_MOUSE_INPUT_EVENT)
	{
		switch(event.MouseInput.Event)
		{
			case EMIE_LMOUSE_PRESSED_DOWN:
							if(event.MouseInput.X>=hudmapa->dimensionHUD1.X && event.MouseInput.X<=hudmapa->dimensionHUD2.X && event.MouseInput.Y >=hudmapa->dimensionHUD1.Y && event.MouseInput.Y<=hudmapa->dimensionHUD2.Y){
								cout<<"Has clicado en el minimapa en la posición X:"<<event.MouseInput.X<<", Y"<<event.MouseInput.Y<<endl;
							}
							else{
								if (mapa != NULL && hudmapa != NULL)
								{
									hudmapa->paintInformation(mapa->OnEventMapa(event));
								}
							}
							break;
			case EMIE_RMOUSE_PRESSED_DOWN: mapa->OnEventMapa(event);
			default:;
		}
	}
	if(event.EventType == EET_KEY_INPUT_EVENT)
	{
		if(event.KeyInput.Key == irr::KEY_ESCAPE && event.KeyInput.PressedDown)
		{
			cout << "PAUSA LA PANTALLA" << endl;
			gameEngine::stado.pause();
			return true;
		}else{
			return Pantalla::OnEvent(event);
		}
	}
	return false;
}
