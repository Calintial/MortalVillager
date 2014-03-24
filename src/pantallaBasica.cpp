#include "pantallaBasica.h"

PantallaBasica::PantallaBasica(IrrlichtDevice * IrrDevice,graphicEngine * _grEngine,shared_ptr<mapa2D> _mapa, int tipo):Pantalla(IrrDevice,_grEngine,_mapa){
	pantallaDevice->setEventReceiver(this);
	hudmapa = NULL;
	setTipo(tipo);
}

PantallaBasica::~PantallaBasica()
{
    //delete mapa;
    delete hudmapa;
}

void PantallaBasica::pintarPantalla(vector<IDibujable*>* ia_units,vector<IDibujable*>* user_units,vector<IDibujable*>* buildings)
{
	if(mapa.get() == NULL){
		cout<<"creando mapa"<<endl;
		mapa = shared_ptr<mapa2D>(new mapa2D(pantallaDevice,ia_units,user_units,buildings,false));
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
		if(mapa->getSombra())
		{
			if(event.MouseInput.Event == EMIE_LMOUSE_PRESSED_DOWN)
			{
				mapa->setSombra(false);
				position2di pos_colocar = mapa->getSombraCoords();
				pos_colocar = mapa->getTileCoordinates(pos_colocar.X,pos_colocar.Y);
				cout<<"Colocar edificio en:"<<pos_colocar.X << "," << pos_colocar.Y <<endl;

				switch(mapa->getTipoEdificio())
				{
					case 0: (gameEngine::addBuildings(pos_colocar.X,pos_colocar.Y,0)->aplicarTextura(pantallaDevice->getVideoDriver())); break;
					case 1: (gameEngine::addBuildings(pos_colocar.X,pos_colocar.Y,1)->aplicarTextura(pantallaDevice->getVideoDriver())); break;
					case 2: (gameEngine::addBuildings(pos_colocar.X,pos_colocar.Y,2)->aplicarTextura(pantallaDevice->getVideoDriver())); break;
					case 3: (gameEngine::addBuildings(pos_colocar.X,pos_colocar.Y,3)->aplicarTextura(pantallaDevice->getVideoDriver())); break;
					case 4: (gameEngine::addBuildings(pos_colocar.X,pos_colocar.Y,4)->aplicarTextura(pantallaDevice->getVideoDriver())); break;
				}
				
				cout<<"colocar"<<endl;
			}
			else if(event.MouseInput.Event == EMIE_RMOUSE_PRESSED_DOWN)
			{
				mapa->setSombra(false);
				cout<<"no colocar"<<endl;
			}
			else
			{
				position2di mouse_coords;
				mouse_coords.X = event.MouseInput.X;
				mouse_coords.Y = event.MouseInput.Y;
				mapa->setSombraCoords(mouse_coords);
			}
		}
		else
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
				case EMIE_LMOUSE_LEFT_UP:
					if(event.MouseInput.X>=hudmapa->dimensionHUD1.X && event.MouseInput.X<=hudmapa->dimensionHUD2.X && event.MouseInput.Y >=hudmapa->dimensionHUD1.Y && event.MouseInput.Y<=hudmapa->dimensionHUD2.Y){
									cout<<"Has clicado en el minimapa en la posición X:"<<event.MouseInput.X<<", Y"<<event.MouseInput.Y<<endl;
								}
								else{
									if (mapa != NULL && hudmapa != NULL)
									{
										hudmapa->paintInformation(mapa->OnEventMapa(event));
									}
								}
				case EMIE_RMOUSE_PRESSED_DOWN:
				case EMIE_MOUSE_MOVED: mapa->OnEventMapa(event);
										break;
				default:;
			}
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

	if(event.GUIEvent.EventType == EGET_BUTTON_CLICKED)
	{
		s32 id = event.GUIEvent.Caller->getID();

		if(id == BUTTON_ADD_BUILDING)
		{
			IGUIComboBox* combo_edificios = (IGUIComboBox*) pantallaDevice->getGUIEnvironment()->getRootGUIElement()->getElementFromId(COMBO_EDIFICIOS);
			int tipo_edificio = combo_edificios->getSelected();
			cout<<"sombra"<<endl;
			mapa->setSombra(true);
			mapa->setTipoEdificio(tipo_edificio);
		}
	}
	return false;
}
