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
    
    for(int i=0; i<dpos; i++)
	{
		pscroll[i] = false;
	}
	
	tipo=0;
}

void Pantalla::dispose(){
    eliminar = true;
}


bool Pantalla::OnEvent(const SEvent& event){
    if (event.EventType == irr::EET_KEY_INPUT_EVENT){

    	if (event.KeyInput.Key == irr::KEY_F2 && event.KeyInput.PressedDown)
    	{
    		cout<<"F2 presionado -> pantallaBasica"<<endl;
    		setTipo(0);
    		grEngine->setPantalla(new PantallaBasica(pantallaDevice,grEngine,mapa,0));
            return true;
    	}
    	else if (event.KeyInput.Key == irr::KEY_F3 && event.KeyInput.PressedDown)
    	{
    		cout<<"F3 presionado -> pantallaPathfinding"<<endl;
    		setTipo(1);
    		grEngine->setPantalla(new PantallaPathfinding(pantallaDevice,grEngine,mapa,1));
            return true;
    	}
    	else if (event.KeyInput.Key == irr::KEY_F4 && event.KeyInput.PressedDown)
    	{
    		cout<<"F4 presionado -> pantallaIABatalla"<<endl;
    		setTipo(2);
    		grEngine->setPantalla(new PantallaIABatalla(pantallaDevice,grEngine,mapa,2));
    		return true;
    	}
    	
    	if (event.KeyInput.Key == KEY_UP && event.KeyInput.PressedDown)
		{
			cout << "ARRIBA pulsado";
			//arriba
			pscroll[0] = true;
		}
		if (event.KeyInput.Key == KEY_DOWN && event.KeyInput.PressedDown)
		{
			cout << "ABAJO pulsado";
			//abajo
			pscroll[1] = true;
		}
		if (event.KeyInput.Key == KEY_RIGHT && event.KeyInput.PressedDown)
		{
			cout << "DERECHA pulsado";
			//derecha
			pscroll[2] = true;
		}
		if (event.KeyInput.Key == KEY_LEFT && event.KeyInput.PressedDown)
		{
			cout << "IZQUIERDA pulsado";
			//izquierda
			pscroll[3] = true;
		}
		
		if (event.KeyInput.Key == KEY_UP && !event.KeyInput.PressedDown)
		{
			cout << "ARRIBA soltado";
			//arriba
			pscroll[0] = false;
		}
		if (event.KeyInput.Key == KEY_DOWN && !event.KeyInput.PressedDown)
		{
			cout << "ABAJO soltado";
			//abajo
			pscroll[1] = false;
		}
		if (event.KeyInput.Key == KEY_RIGHT && !event.KeyInput.PressedDown)
		{
			cout << "DERECHA soltado";
			//derecha
			pscroll[2] = false;
		}
		if (event.KeyInput.Key == KEY_LEFT && !event.KeyInput.PressedDown)
		{
			cout << "IZQUIERDA soltado";
			//izquierda
			pscroll[3] = false;
		}
		
		
		if (pscroll[0] == true || pscroll[1] == true || pscroll[2] == true || pscroll[3] == true)
		{
			position2di pos = mapa->GetCameraScroll();
			
			if(pscroll[0] == true)
			{
				if(pos.Y>0)
					pos.Y = pos.Y-1;
			}
			if(pscroll[1] == true)
			{
				if(pos.Y<200)
					pos.Y = pos.Y+1;
			}
			if(pscroll[2] == true)
			{
				if(pos.X<200)
					pos.X = pos.X+1;
			}
			if(pscroll[3] == true)
			{		
				if(pos.X>0)
					pos.X = pos.X-1;
			}
			
			mapa->SetCameraScroll(pos);
			cout << getTipo() << endl;
			if(getTipo()==0)
				grEngine->setPantalla(new PantallaBasica(pantallaDevice,grEngine,mapa,0));
			else if(getTipo()==1)
				grEngine->setPantalla(new PantallaPathfinding(pantallaDevice,grEngine,mapa,1));
			else if(getTipo()==2)
				grEngine->setPantalla(new PantallaIABatalla(pantallaDevice,grEngine,mapa,2));
				
			return true;
		}
    }	
    return false;
}

