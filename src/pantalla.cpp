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

Pantalla::Pantalla(IrrlichtDevice * IrrDevice,graphicEngine * _grEngine){
	pantallaDevice= IrrDevice;
	pantallaDevice->setEventReceiver(this);
	grEngine = _grEngine;
}

bool Pantalla::OnEvent(const SEvent& event){
    if (event.EventType == irr::EET_KEY_INPUT_EVENT){
    	// TODO: mostrar la pantalla

    	if (event.KeyInput.Key == irr::KEY_F2 && event.KeyInput.PressedDown)
    	{
    		cout<<"F2 presionado -> pantallaBasica"<<endl;
    		grEngine->setPantalla(new PantallaBasica(pantallaDevice,grEngine));
    		return true;
    	}else if (event.KeyInput.Key == irr::KEY_F3 && event.KeyInput.PressedDown)
    	{
    		cout<<"F3 presionado -> pantallaPathfinding"<<endl;
    		grEngine->setPantalla(new PantallaPathfinding(pantallaDevice,grEngine));
    		return true;
    	}else if (event.KeyInput.Key == irr::KEY_F4 && event.KeyInput.PressedDown)
    	{
    		cout<<"F4 presionado -> pantallaIABatalla"<<endl;
    		grEngine->setPantalla(new PantallaIABatalla(pantallaDevice,grEngine));

    		return true;
    	}else{
    		cout<<"presionado "<<event.KeyInput.Key<<endl;
    	}
    }
    return false;
}

