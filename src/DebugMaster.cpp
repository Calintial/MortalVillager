#include "DebugMaster.h"


DebugMaster::DebugMaster(IrrlichtDevice * IrrDevice, shared_ptr<mapa2D> map)
{
	DebugDevice = IrrDevice;
    env = IrrDevice->getGUIEnvironment();
    driver = IrrDevice->getVideoDriver();
    font = env->getFont("../media/fonthaettenschweiler.bmp");
    //env->clear();
    initDebugMenu();

    mapa = map;

	//DebugDevice->setEventReceiver(this); 
	drawVision = false;
	drawAttackVision = false;
	subarbolElegido = 0;
}

DebugMaster::~DebugMaster()
{

}

void DebugMaster::initDebugMenu()
{
	IGUIScrollBar* speed_bar = env->addScrollBar(true,rect<s32>(300,dimensionPantallaY+60,500,dimensionPantallaY+85), 0, SCROLL_SPEED);

    speed_bar->setPos(gameEngine::getSpeed());

    /*Botones para añadir IA o unidades de usuario*/
	env->addButton(rect<s32>(550,dimensionPantallaY+45,750,dimensionPantallaY+70), 0, BUTTON_SEE_SUBARBOL,
        L"Ver Subarbol", L"Ver subarbol seleccionado");

	/*Desplegables para seleccionar unidad a insertar*/
	IGUIComboBox* combo_subarbol = env->addComboBox (rect<s32>(900,dimensionPantallaY+65,1000,dimensionPantallaY+85), 0,COMBO_SUBARBOL);
	combo_subarbol->addItem(L"Subarbol BLA");
	combo_subarbol->addItem(L"Subarbol BLA");
	combo_subarbol->addItem(L"Subarbol BLA");
	combo_subarbol->addItem(L"Subarbol BLA");

	/*Cargar texturas imagenes*/
	state_search = driver->getTexture("../media/Imagenes/Debug/MEF/Search.png");
	state_approach = driver->getTexture("../media/Imagenes/Debug/MEF/Approach.png");
	state_attack = driver->getTexture("../media/Imagenes/Debug/MEF/Attack.png");
	state_flee = driver->getTexture("../media/Imagenes/Debug/MEF/Flee.png");
	state_recovery = driver->getTexture("../media/Imagenes/Debug/MEF/Recovery.png");
}

void DebugMaster::Draw()
{
	if (DebugDevice->run())
	{        
		if(driver)
		{
			font->draw(L"Velocidad del juego",
            core::rect<s32>(350,dimensionPantallaY+25,500,dimensionPantallaY+50),video::SColor(255,0,0,0));
			
			//DrawVisions();

			driver->draw2DRectangle(video::SColor(255,200,200,200),core::rect<s32>(dimensionPantallaX,0,driver->getScreenSize().Width,driver->getScreenSize().Height));
			driver->draw2DRectangle(video::SColor(255,200,200,200),core::rect<s32>(0,dimensionPantallaY,driver->getScreenSize().Width,driver->getScreenSize().Height));

			//DrawParameters();
			//DrawMEF();

			env->drawAll();
		}
	}
}

void DebugMaster::DrawMEF(vector<int> caminoNodos)
{
	int ia_selected = mapa->getIASelected();
	int ia_state = -1;

	if(ia_selected != -1){
		battleIA* batiA = (battleIA*)vUnits->at(ia_selected).get();
		ia_state = batiA->getState();
	}

	if(ia_state == SEARCHING)
	{
		state_search = driver->getTexture("../media/Imagenes/Debug/MEF/Search_selected.png");
		driver->draw2DImage(state_search, core::position2d<s32>(dimensionPantallaX + 79,10),
        core::rect<s32>(0,0,75 ,75), 0,
        video::SColor(255,255,255,255), true);
	}
	else
	{
		state_search = driver->getTexture("../media/Imagenes/Debug/MEF/Search.png");
		driver->draw2DImage(state_search, core::position2d<s32>(dimensionPantallaX + 79,10),
        core::rect<s32>(0,0,75 ,75), 0,
        video::SColor(255,255,255,255), true);
	}

	//No hay enemigo en rango de vision
	driver->draw2DImage(driver->getTexture("../media/Imagenes/Debug/MEF/flechas/bucleRej.png"), core::position2d<s32>(dimensionPantallaX + 30,10),
    core::rect<s32>(0,0,59 ,56), 0,
    video::SColor(255,255,255,255), true);

	//Enemigo en rango
	driver->draw2DImage(driver->getTexture("../media/Imagenes/Debug/MEF/flechas/der.png"), core::position2d<s32>(dimensionPantallaX + 159,20),
    core::rect<s32>(0,0,100 ,22), 0,
    video::SColor(255,255,255,255), true);

	//Fuera de rango
	driver->draw2DImage(driver->getTexture("../media/Imagenes/Debug/MEF/flechas/izq.png"), core::position2d<s32>(dimensionPantallaX + 159,50),
    core::rect<s32>(0,0,100 ,22), 0,
    video::SColor(255,255,255,255), true);

	if(ia_state == APPROACH)
	{
		state_approach = driver->getTexture("../media/Imagenes/Debug/MEF/Approach_selected.png");
		driver->draw2DImage(state_approach, core::position2d<s32>(dimensionPantallaX + 266,10),
        core::rect<s32>(0,0,75 ,75), 0,
        video::SColor(255,255,255,255), true);
	}
	else
	{
		state_approach = driver->getTexture("../media/Imagenes/Debug/MEF/Approach.png");
		driver->draw2DImage(state_approach, core::position2d<s32>(dimensionPantallaX + 266,10),
        core::rect<s32>(0,0,75 ,75), 0,
        video::SColor(255,255,255,255), true);
	}

	//Fuera de rango de ataque. Dentro de rango visión
	driver->draw2DImage(driver->getTexture("../media/Imagenes/Debug/MEF/flechas/bucleNoRej.png"), core::position2d<s32>(dimensionPantallaX + 331,10),
    core::rect<s32>(0,0,59 ,56), 0,
    video::SColor(255,255,255,255), true);

	//En rango de ataque
	driver->draw2DImage(driver->getTexture("../media/Imagenes/Debug/MEF/flechas/inf.png"), core::position2d<s32>(dimensionPantallaX + 310,90),
    core::rect<s32>(0,0,22 ,100), 0,
    video::SColor(255,255,255,255), true);

	//Fuera de rango de ataque
	driver->draw2DImage(driver->getTexture("../media/Imagenes/Debug/MEF/flechas/sup.png"), core::position2d<s32>(dimensionPantallaX + 290,90),
    core::rect<s32>(0,0,22 ,100), 0,
    video::SColor(255,255,255,255), true);

    //Fuera de rango
	driver->draw2DImage(driver->getTexture("../media/Imagenes/Debug/MEF/flechas/supIzq2.png"), core::position2d<s32>(dimensionPantallaX + 170,90),
    core::rect<s32>(0,0,97 ,118), 0,
    video::SColor(255,255,255,255), true);


	if(ia_state == ATTACK)
	{
		state_attack = driver->getTexture("../media/Imagenes/Debug/MEF/Attack_selected.png");
		driver->draw2DImage(state_attack, core::position2d<s32>(dimensionPantallaX + 266,197),
        core::rect<s32>(0,0,75 ,75), 0,
        video::SColor(255,255,255,255), true);
	}
	else
	{
		state_attack = driver->getTexture("../media/Imagenes/Debug/MEF/Attack.png");
		driver->draw2DImage(state_attack, core::position2d<s32>(dimensionPantallaX + 266,197),
        core::rect<s32>(0,0,75 ,75), 0,
        video::SColor(255,255,255,255), true);				
	}

	//Enemigo en rango de ataque y vida suficiente
	driver->draw2DImage(driver->getTexture("../media/Imagenes/Debug/MEF/flechas/bucleNoRej.png"), core::position2d<s32>(dimensionPantallaX + 331,197),
    core::rect<s32>(0,0,59 ,56), 0,
    video::SColor(255,255,255,255), true);

	//Vida insuficiente
	driver->draw2DImage(driver->getTexture("../media/Imagenes/Debug/MEF/flechas/inf.png"), core::position2d<s32>(dimensionPantallaX + 292.5,282),
    core::rect<s32>(0,0,22 ,100), 0,
    video::SColor(255,255,255,255), true);




	if(ia_state == FLEE)
	{
		state_flee = driver->getTexture("../media/Imagenes/Debug/MEF/Flee_selected.png");
		driver->draw2DImage(state_flee, core::position2d<s32>(dimensionPantallaX + 266,384),
        core::rect<s32>(0,0,75 ,75), 0,
        video::SColor(255,255,255,255), true);
	}
	else
	{
		state_flee = driver->getTexture("../media/Imagenes/Debug/MEF/Flee.png");
		driver->draw2DImage(state_flee, core::position2d<s32>(dimensionPantallaX + 266,384),
        core::rect<s32>(0,0,75 ,75), 0,
        video::SColor(255,255,255,255), true);
	}

	driver->draw2DImage(driver->getTexture("../media/Imagenes/Debug/MEF/flechas/izq.png"), core::position2d<s32>(dimensionPantallaX + 159,390),
    core::rect<s32>(0,0,100 ,22), 0,
    video::SColor(255,255,255,255), true);

    //Enemigo fuera de rango
	driver->draw2DImage(driver->getTexture("../media/Imagenes/Debug/MEF/flechas/bucleNoRej.png"), core::position2d<s32>(dimensionPantallaX + 331,384),
    core::rect<s32>(0,0,59 ,56), 0,
    video::SColor(255,255,255,255), true);

	if(ia_state == RECOVERY)
	{
		state_recovery = driver->getTexture("../media/Imagenes/Debug/MEF/Recovery_selected.png");
		driver->draw2DImage(state_recovery, core::position2d<s32>(dimensionPantallaX + 79,384),
        core::rect<s32>(0,0,75 ,75), 0,
        video::SColor(255,255,255,255), true);
	}
	else
	{
		state_recovery = driver->getTexture("../media/Imagenes/Debug/MEF/Recovery.png");
		driver->draw2DImage(state_recovery, core::position2d<s32>(dimensionPantallaX + 79,384),
        core::rect<s32>(0,0,75 ,75), 0,
        video::SColor(255,255,255,255), true);
	}

	//No recuperado
	driver->draw2DImage(driver->getTexture("../media/Imagenes/Debug/MEF/flechas/bucleRej.png"), core::position2d<s32>(dimensionPantallaX + 30,384),
    core::rect<s32>(0,0,59 ,56), 0,
    video::SColor(255,255,255,255), true);

	//Ya recuperado
	driver->draw2DImage(driver->getTexture("../media/Imagenes/Debug/MEF/flechas/supLarge.png"), core::position2d<s32>(dimensionPantallaX + 105,90),
    core::rect<s32>(0,0,22 ,282), 0,
    video::SColor(255,255,255,255), true);

    //Enemigo en rango
	driver->draw2DImage(driver->getTexture("../media/Imagenes/Debug/MEF/flechas/der.png"), core::position2d<s32>(dimensionPantallaX + 159,420),
    core::rect<s32>(0,0,100 ,22), 0,
    video::SColor(255,255,255,255), true);

}
/*
void DebugMaster::DrawParameters()
{
	int ia_selected = mapa->getIASelected();
	if(ia_selected != -1)
	{

		Unidades* unidad = (Unidades*)vUnits->at(ia_selected).get();
		int ia_life = unidad->getLife();
		std::string string_life = "Vida:" + to_string(ia_life);
		std::string string_unit_selected = "Unidad IA seleccionada: " + to_string(ia_selected);

		font->draw(L"Parametros",
	    core::rect<s32>(dimensionPantallaX + 59,509,dimensionPantallaX + 209,534),video::SColor(255,0,0,0));

		font->draw(stringw(string_unit_selected.c_str()),
	    core::rect<s32>(dimensionPantallaX + 59,540,dimensionPantallaX + 209,565),video::SColor(255,0,0,0));

	    font->draw(stringw(string_life.c_str()),
	    core::rect<s32>(dimensionPantallaX + 59,571,dimensionPantallaX + 209,596),video::SColor(255,0,0,0));		
	}

}

void DebugMaster::DrawVisions()
{
	position2di DrawPosition;

	int n_ia = vUnits->size();	
	for(int i=0; i<n_ia; i++)
	{
		position2di pos = vUnits->at(i)->getPosition() - mapa->GetCameraScroll();
		Unidades* uni_ptr = (Unidades*)(vUnits->at(i).get());
		int v_range = uni_ptr->getVisionRange();
		int a_range = uni_ptr->getAttackRange();

		position2di limits;
		limits.X = WIDTH;
		limits.Y = HEIGHT;
		limits = limits - mapa->GetCameraScroll();

		//Pintar vision de la unidad
		if(drawVision)
		{
			for(int x = pos.X - v_range; x <= pos.X + v_range; x++)
			{
				for(int y = pos.Y - v_range; y <= pos.Y + v_range; y++)
				{
					if((x>= 0 && x < limits.X) && (y>= 0 && y < limits.Y))
					{
						ITexture* vision_texture = driver->getTexture("../media/Texturas/units/vision_distance.png");
						DrawPosition = mapa2D::getIsoFromTile(x,y);
						mapa->PintarTile(vision_texture, DrawPosition.X, DrawPosition.Y);					
					}

				}
			}
		}

		//Pintar rango de ataque de la unidad
		if(drawAttackVision)
		{
			for(int x = pos.X - a_range; x <= pos.X + a_range; x++)
			{
				for(int y = pos.Y - a_range; y <= pos.Y + a_range; y++)
				{
					if((x>= 0 && x < limits.X) && (y>= 0 && y < limits.Y))
					{
						ITexture* vision_texture = driver->getTexture("../media/Texturas/units/vision_attack.png");
						DrawPosition = mapa2D::getIsoFromTile(x,y);
						mapa->PintarTile(vision_texture, DrawPosition.X, DrawPosition.Y);						
					}

				}
			}
		}
	}
}

bool DebugMaster::OnEvent(const SEvent& event)
{

	/*if(event.GUIEvent.EventType == EGET_CHECKBOX_CHANGED)
	{
		s32 id = event.GUIEvent.Caller->getID();
		switch(id)
		{
			case CB_VISION_RANGE: drawVision = ((IGUICheckBox*)event.GUIEvent.Caller)->isChecked();
								  break;
			case CB_ATTACK_RANGE: drawAttackVision = ((IGUICheckBox*)event.GUIEvent.Caller)->isChecked();
								  break;
		}
		
	}
	

	else if(event.GUIEvent.EventType == EGET_BUTTON_CLICKED)
	{
		s32 id = event.GUIEvent.Caller->getID();

		if(id == BUTTON_SEE_SUBARBOL)
		{

			IGUIComboBox* combo_subarbol = (IGUIComboBox*) env->getRootGUIElement()->getElementFromId(combo_subarbol);
			int tipo_subarbol = combo_subarbol->getSelected();

		}
		
	}
	else if (event.EventType == EET_MOUSE_INPUT_EVENT)
	{
		if(mapa->getSombra())
		{
			if(event.MouseInput.Event == EMIE_LMOUSE_PRESSED_DOWN)
			{
				mapa->setSombra(false);
				position2di pos_colocar = mapa->getSombraCoords();
				pos_colocar = mapa->getTileCoordinates(pos_colocar.X,pos_colocar.Y);
				cout<<"Colocar edificio en:"<<pos_colocar.X << "," << pos_colocar.Y <<endl;

				(gameEngine::addBuildings(pos_colocar.X,pos_colocar.Y,0,true)->aplicarTextura(driver));
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
			mapa->OnEventMapa(event);			
		}
	}*/
	return false;
}
