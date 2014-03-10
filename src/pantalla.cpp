#include "pantalla.h"
// #include <string>
// #include <iostream>
// #include <vector>
// #include <cstdlib>
// #include <string>

// using namespace irr;
// using namespace video;
// using namespace std;
// using namespace core;
#include "pantallaBasica.h"
#include "pantallaPathfinding.h"
#include "pantallaIABatalla.h"
#include "gameEngine.h"

Pantalla::Pantalla(IrrlichtDevice * IrrDevice,graphicEngine * _grEngine,shared_ptr<mapa2D> _mapa):grEngine(_grEngine),mapa(_mapa){
	pantallaDevice= IrrDevice;
	pantallaDevice->setEventReceiver(this);

    eliminar = false;

}
void Pantalla::dispose(){
    eliminar = true;
}


bool Pantalla::OnEvent(const SEvent& event){
    if (event.EventType == irr::EET_KEY_INPUT_EVENT){
    	// TODO: mostrar la pantalla // constructor de copia con las distintas pantallas?

    	if (event.KeyInput.Key == irr::KEY_F2 && event.KeyInput.PressedDown)
    	{
    		cout<<"F2 presionado -> pantallaBasica"<<endl;
    		grEngine->setPantalla(new PantallaBasica(pantallaDevice,grEngine,mapa));
            return true;
    	}
    	else if (event.KeyInput.Key == irr::KEY_F3 && event.KeyInput.PressedDown)
    	{
    		cout<<"F3 presionado -> pantallaPathfinding"<<endl;
    		grEngine->setPantalla(new PantallaPathfinding(pantallaDevice,grEngine,mapa));
            return true;
    	}
    	else if (event.KeyInput.Key == irr::KEY_F4 && event.KeyInput.PressedDown)
    	{
    		cout<<"F4 presionado -> pantallaIABatalla"<<endl;
    		grEngine->setPantalla(new PantallaIABatalla(pantallaDevice,grEngine,mapa));
    		return true;
    	}
    	else if (event.KeyInput.Key == KEY_UP && event.KeyInput.PressedDown)
		{
			cout << "ARRIBA";
			position2di pos = mapa->GetCameraScroll();
			if(pos.Y>0)
				pos.Y = pos.Y-1;
			
			mapa->SetCameraScroll(pos);
			grEngine->setPantalla(new PantallaBasica(pantallaDevice,grEngine,mapa));
            return true;
		}
		else if (event.KeyInput.Key == KEY_DOWN && event.KeyInput.PressedDown)
		{
			cout << "ABAJO";
			position2di pos = mapa->GetCameraScroll();
			if(pos.Y<200)
				pos.Y = pos.Y+1;
			mapa->SetCameraScroll(pos);
			grEngine->setPantalla(new PantallaBasica(pantallaDevice,grEngine,mapa));
            return true;
		}
		else if (event.KeyInput.Key == KEY_RIGHT && event.KeyInput.PressedDown)
		{
			cout << "DERECHA";
			position2di pos = mapa->GetCameraScroll();
			if(pos.X<200)
				pos.X = pos.X+1;
			mapa->SetCameraScroll(pos);
			grEngine->setPantalla(new PantallaBasica(pantallaDevice,grEngine,mapa));
            return true;
		}
		else if (event.KeyInput.Key == KEY_LEFT && event.KeyInput.PressedDown)
		{
			cout << "IZQUIERDA";
			position2di pos = mapa->GetCameraScroll();
			if(pos.X>0)
				pos.X = pos.X-1;
			mapa->SetCameraScroll(pos);
			grEngine->setPantalla(new PantallaBasica(pantallaDevice,grEngine,mapa));
            return true;
		}
    	else
    	{
    		cout<<"presionado "<<event.KeyInput.Key<<endl;
    	}
    }	
    return false;
}

