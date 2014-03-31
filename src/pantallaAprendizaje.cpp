#include "pantallaAprendizaje.h"

PantallaAprendizaje::PantallaAprendizaje(IrrlichtDevice * IrrDevice,graphicEngine * _grEngine,shared_ptr<mapa2D> _mapa, int tipo):Pantalla(IrrDevice,_grEngine,_mapa){
	
	pantallaDevice->setEventReceiver(this);
	setTipo(tipo);
	srand (3);
	aprendizaje = new CController(pantallaDevice);

}

PantallaAprendizaje::~PantallaAprendizaje()
{
}

void PantallaAprendizaje::pintarPantalla(vector<IDibujable*>* ia_units,vector<IDibujable*>* user_units,vector<IDibujable*>* buildings)
{
	/*if(aprendizaje == NULL){
		aprendizaje= new CController();
	}*/

	pantallaDevice->getVideoDriver()->beginScene(true, true, SColor(0,200,200,200));
	pantallaDevice->setEventReceiver(this);

	aprendizaje->Update();
	//hudmapa->paint();

	pantallaDevice->getVideoDriver()->draw2DRectangle(video::SColor(255,200,200,200),core::rect<s32>(32*20,0,pantallaDevice->getVideoDriver()->getScreenSize().Width,pantallaDevice->getVideoDriver()->getScreenSize().Height));
	pantallaDevice->getVideoDriver()->draw2DRectangle(video::SColor(255,200,200,200),core::rect<s32>(0,32*20,pantallaDevice->getVideoDriver()->getScreenSize().Width,pantallaDevice->getVideoDriver()->getScreenSize().Height));
	pantallaDevice->getVideoDriver()->endScene();
	if(eliminar){
		delete this;
	}

}

bool PantallaAprendizaje::OnEvent(const SEvent& event){
	/*if (event.EventType == EET_MOUSE_INPUT_EVENT)
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
					pos_colocar.X = pos_colocar.X -1;
					mapa->setSombra(false);
					
					cout<<"Colocar edificio en:"<<pos_colocar.X << "," << pos_colocar.Y <<endl;

					switch(mapa->getTipoEdificio())
					{
						case 0: (gameEngine::addBuildings(pos_colocar.X,pos_colocar.Y,0)->aplicarTextura(pantallaDevice->getVideoDriver())); break;
						case 1: (gameEngine::addBuildings(pos_colocar.X,pos_colocar.Y,1)->aplicarTextura(pantallaDevice->getVideoDriver())); break;
						case 2: (gameEngine::addBuildings(pos_colocar.X,pos_colocar.Y,2)->aplicarTextura(pantallaDevice->getVideoDriver())); break;
						case 3: (gameEngine::addBuildings(pos_colocar.X,pos_colocar.Y,3)->aplicarTextura(pantallaDevice->getVideoDriver())); break;
						case 4: (gameEngine::addBuildings(pos_colocar.X,pos_colocar.Y,4)->aplicarTextura(pantallaDevice->getVideoDriver())); break;
					}
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

	}*/

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
	else if (event.EventType == EET_MOUSE_INPUT_EVENT)
	{
		aprendizaje->OnEvent(event);
	}

	/*if(event.GUIEvent.EventType == EGET_BUTTON_CLICKED)
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
	return false;*/
}

