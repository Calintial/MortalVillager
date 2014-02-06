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

Pantalla::Pantalla(IrrlichtDevice * IrrDevice){
	pantallaDevice= IrrDevice;
	pantallaDevice->setEventReceiver(this);
}

bool Pantalla::OnEvent(const SEvent& event){
    if (event.EventType == irr::EET_KEY_INPUT_EVENT){
    	if (event.KeyInput.Key == irr::KEY_F2 && event.KeyInput.PressedDown)
    	{
    		cout<<"F2 presionado -> pantallaBasica"<<endl;
    		return true;
    	}else if (event.KeyInput.Key == irr::KEY_F3 && event.KeyInput.PressedDown)
    	{
    		cout<<"F3 presionado -> pantallaPathfinding"<<endl;
    		return true;
    	}else if (event.KeyInput.Key == irr::KEY_F4 && event.KeyInput.PressedDown)
    	{
    		cout<<"F4 presionado -> pantallaIABatalla"<<endl;
    		return true;
    	}else{
    		cout<<"presionado "<<event.KeyInput.Key<<endl;
    	}
    }
    return false;
}

