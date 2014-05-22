#include "pantallaIAMaster.h"


PantallaIAMaster::PantallaIAMaster(IrrlichtDevice * IrrDevice,graphicEngine * _grEngine,shared_ptr<mapa2D> _mapa, int tipo):Pantalla(IrrDevice,_grEngine,_mapa){
	debug = NULL;
	hudmapa = NULL;
	eventosMapa = true;
	pantallaDevice->setEventReceiver(this);
	setTipo(tipo);
}
PantallaIAMaster::~PantallaIAMaster(){

    //delete mapa;
    delete debug;
    debug = NULL;
    delete hudmapa;
    hudmapa = NULL;
}

void PantallaIAMaster::pintarPantalla(vector<shared_ptr<IDibujable>>* ia_units,vector<shared_ptr<IDibujable>>* user_units, vector<shared_ptr<IDibujable>>* buildings){


	if(mapa.get() == NULL)
	{
		cout<<"creando mapa"<<endl;
		mapa = shared_ptr<mapa2D>(new mapa2D(pantallaDevice,ia_units,user_units,buildings,true));
	}

	if(hudmapa == NULL){
		hudmapa= new hud(pantallaDevice,mapa);
	}
	if(debug == NULL)
		debug = new DebugMaster(pantallaDevice,mapa);

	pantallaDevice->getVideoDriver()->beginScene(true, true, SColor(0,200,200,200));
	mapa->Pintar();
	
	hudmapa->paint();
	debug->Draw(gameEngine::getIntelEngine()->getDT()->caminoNodos);
	
	pantallaDevice->getVideoDriver()->endScene();
	if(eliminar){
		delete this;
	}

}

bool PantallaIAMaster::OnEvent(const SEvent& event){
	if (event.EventType == EET_MOUSE_INPUT_EVENT)
	{
		if(mapa->getSombra())
		{
			if(event.MouseInput.Event == EMIE_LMOUSE_PRESSED_DOWN)
			{
				position2di pos_colocar = mapa->getSombraCoords();
				pos_colocar = mapa->getTileCoordinates(pos_colocar.X,pos_colocar.Y) + mapa->GetCameraScroll();
				
				cout<<"Colocar edificio en:"<<pos_colocar.X << "," << pos_colocar.Y <<endl;

				if(mapa->puede_colocar(pos_colocar))
				{
					mapa->setSombra(false);
					
					cout<<"Colocar edificio en:"<<pos_colocar.X << "," << pos_colocar.Y <<endl;

					mapa->colocarEdificio(pos_colocar);

					hudmapa->selectButton(-1);
					cout<<"colocar"<<endl;					
				}
				else
				{
					cout<<"no se puede colocar"<<endl;	
				}

			}
			else if(event.MouseInput.Event == EMIE_RMOUSE_PRESSED_DOWN)
			{
				hudmapa->selectButton(-1);
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
								else if((event.MouseInput.X>=396 && event.MouseInput.X<=457 && event.MouseInput.Y >= 468 && event.MouseInput.Y<=523))
								{
									mapa->setSombra(true);
									mapa->setTipoEdificio(1);
									hudmapa->selectButton(1);
								}
								else if((event.MouseInput.X>=458 && event.MouseInput.X<=520 && event.MouseInput.Y >= 468 && event.MouseInput.Y<=523))
								{
									mapa->setSombra(true);
									mapa->setTipoEdificio(2);
									hudmapa->selectButton(2);
								}
								else if((event.MouseInput.X>=521 && event.MouseInput.X<=580 && event.MouseInput.Y >= 468 && event.MouseInput.Y<=523))
								{
									mapa->setSombra(true);
									mapa->setTipoEdificio(3);
									hudmapa->selectButton(3);
								}
								else if((event.MouseInput.X>=396 && event.MouseInput.X<=457 && event.MouseInput.Y >= 524 && event.MouseInput.Y<=579))
								{
									mapa->setSombra(true);
									mapa->setTipoEdificio(4);
									hudmapa->selectButton(4);
								}
								else if((event.MouseInput.X>=458 && event.MouseInput.X<=520 && event.MouseInput.Y >= 524 && event.MouseInput.Y<=579))
								{
									hudmapa->selectButton(5);
									//Implementar código de creación de aldeanos
									if(gameEngine::recursos_jugador >= 100)
									{
										shared_ptr<Aldeano>  u = std::dynamic_pointer_cast<Aldeano>(gameEngine::addUserUnit(5,3,0));
										u->aplicarTextura(pantallaDevice->getVideoDriver());
										u->setPathfinding(mapa->getPathfinding());
										u->Move(11,10);
										gameEngine::recursos_jugador = gameEngine::recursos_jugador - 100;
									}

									hudmapa->selectButton(-1);
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

	}else if(event.GUIEvent.EventType == EGET_SCROLL_BAR_CHANGED)
	{
		s32 id = event.GUIEvent.Caller->getID();

		switch(id)
		{
			case SCROLL_SPEED: s32 pos = ((IGUIScrollBar*)event.GUIEvent.Caller)->getPos();
                 			   gameEngine::setSpeed(pos);
							   break;
		}
	}else if(event.EventType == EET_KEY_INPUT_EVENT)
	{
		if(event.KeyInput.Key == irr::KEY_ESCAPE && event.KeyInput.PressedDown)
		{
			cout << "PAUSA LA PANTALLA" << endl;
			gameEngine::stado.pause();
			return true;
		}else{
			return Pantalla::OnEvent(event);
		}
	}else if(event.GUIEvent.EventType == EGET_BUTTON_CLICKED)
	{
		s32 id = event.GUIEvent.Caller->getID();

		if(id == BUTTON_ADD_BUILDING)
		{
			IGUIComboBox* combo_edificios = (IGUIComboBox*) pantallaDevice->getGUIEnvironment()->getRootGUIElement()->getElementFromId(COMBO_EDIFICIOS);
			int tipo_edificio = combo_edificios->getSelected();
			cout<<"sombra"<<endl;
			mapa->setSombra(true);
			mapa->setTipoEdificio(tipo_edificio);
		}else if(id == BUTTON_SEE_SUBARBOL)
		{
			IGUIComboBox* combo_subarbol = (IGUIComboBox*) pantallaDevice->getGUIEnvironment()->getRootGUIElement()->getElementFromId(COMBO_SUBARBOL);
			int tipo_subarbol = combo_subarbol->getSelected();
			debug->selectSubarbol(tipo_subarbol);
		}
	}
	return false;
}
