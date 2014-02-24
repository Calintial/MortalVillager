#include "DebugMenu.h"


DebugMenu::DebugMenu(IrrlichtDevice * IrrDevice, vector<IDibujable*>* ia_units, shared_ptr<mapa2D> map)
{
	DebugDevice = IrrDevice;
    env = IrrDevice->getGUIEnvironment();
    driver = IrrDevice->getVideoDriver();
    font = env->getFont("../media/fonthaettenschweiler.bmp");
    env->clear();
    initDebugMenu();

    vUnits = ia_units;
    mapa = map;

	//DebugDevice->setEventReceiver(this); 
	drawVision = false;
	drawAttackVision = false;
}

DebugMenu::~DebugMenu()
{

}

void DebugMenu::initDebugMenu()
{
	env->addCheckBox(false,rect<s32>(50,dimensionPantallaY+45,200,dimensionPantallaY+60), 0, CB_ATTACK_RANGE, 
							   L"Ver distancia ataque");
	env->addCheckBox(false,rect<s32>(50,dimensionPantallaY+70,200,dimensionPantallaY+85), 0, CB_VISION_RANGE, 
							   L"Ver distancia visión");

	IGUIScrollBar* speed_bar = env->addScrollBar(true,rect<s32>(300,dimensionPantallaY+60,500,dimensionPantallaY+85), 0, SCROLL_SPEED);

    speed_bar->setPos(gameEngine::getSpeed());

    /*Botones para añadir IA o unidades de usuario*/
	env->addButton(rect<s32>(550,dimensionPantallaY+45,750,dimensionPantallaY+70), 0, BUTTON_ADD_IA,
        L"Añadir IA", L"Añadir unidad controlada por la IA");

	env->addButton(rect<s32>(550,dimensionPantallaY+80,750,dimensionPantallaY+105), 0, BUTTON_ADD_UNIT,
        L"Añadir Unidad", L"Añadir unidad controlada por el usuario");

	/*Spin box para obtener las coordenadas para añadir las unidades*/
	IGUISpinBox* spbox_X = env->addSpinBox(L"0",rect<s32>(760,dimensionPantallaY+65,810,dimensionPantallaY+85),true,0,SPBOX_COORDX);
	IGUISpinBox* spbox_Y = env->addSpinBox(L"0",rect<s32>(830,dimensionPantallaY+65,880,dimensionPantallaY+85),true,0,SPBOX_COORDY);

	spbox_X->setDecimalPlaces(0);
	spbox_Y->setDecimalPlaces(0);

	spbox_X->setRange(0,25);
	spbox_Y->setRange(0,19);

	/*Cargar texturas imagenes*/
	state_search = driver->getTexture("../media/Imagenes/Debug/MEF/Search.png");
	state_approach = driver->getTexture("../media/Imagenes/Debug/MEF/Approach.png");
	state_attack = driver->getTexture("../media/Imagenes/Debug/MEF/Attack.png");
	state_flee = driver->getTexture("../media/Imagenes/Debug/MEF/Flee.png");
	state_recovery = driver->getTexture("../media/Imagenes/Debug/MEF/Recovery.png");
}

void DebugMenu::Draw()
{
	if (DebugDevice->run())
	{        
		if(driver)
		{
			font->draw(L"Velocidad del juego",
            core::rect<s32>(350,dimensionPantallaY+25,500,dimensionPantallaY+50),video::SColor(255,0,0,0));
			
			DrawParameters();
			DrawMEF();
			DrawVisions();

			env->drawAll();
		}
	}
}

void DebugMenu::DrawMEF()
{
	int ia_selected = mapa->getIASelected();
	int ia_state = -1;

	if(ia_selected != -1)
		ia_state = ((battleIA*)vUnits->at(ia_selected))->getState();

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

	/*Ya recuperado*/
	driver->draw2DImage(driver->getTexture("../media/Imagenes/Debug/MEF/flechas/supLarge.png"), core::position2d<s32>(dimensionPantallaX + 105,90),
    core::rect<s32>(0,0,22 ,282), 0,
    video::SColor(255,255,255,255), true);

    /*Enemigo en rango*/
	driver->draw2DImage(driver->getTexture("../media/Imagenes/Debug/MEF/flechas/der.png"), core::position2d<s32>(dimensionPantallaX + 159,420),
    core::rect<s32>(0,0,100 ,22), 0,
    video::SColor(255,255,255,255), true);

}

void DebugMenu::DrawParameters()
{
	int ia_selected = mapa->getIASelected();
	if(ia_selected != -1)
	{
		int ia_life = ((Unidades*)vUnits->at(ia_selected))->getLife();
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

void DebugMenu::DrawVisions()
{
	position2di DrawPosition;

	int n_ia = vUnits->size();	
	for(int i=0; i<n_ia; i++)
	{
		position2di pos = vUnits->at(i)->getPosition();
		int v_range = ((Unidades*)vUnits->at(i))->getVisionRange();
		int a_range = ((Unidades*)vUnits->at(i))->getAttackRange();
		/*Pintar vision de la unidad*/
		if(drawVision)
		{
			for(int x = pos.X - v_range; x <= pos.X + v_range; x++)
			{
				for(int y = pos.Y - v_range; y <= pos.Y + v_range; y++)
				{
					if(x < mapa->ViewSize.Width && y < mapa->ViewSize.Height)
					{
						ITexture* vision_texture = driver->getTexture("../media/Texturas/units/vision_distance.png");
						DrawPosition = position2di(x*TILE_WIDTH,y*TILE_HEIGHT);
						mapa->PintarTile(vision_texture, DrawPosition.X, DrawPosition.Y);					
					}

				}
			}
		}

		/*Pintar rango de ataque de la unidad*/
		if(drawAttackVision)
		{
			for(int x = pos.X - a_range; x <= pos.X + a_range; x++)
			{
				for(int y = pos.Y - a_range; y <= pos.Y + a_range; y++)
				{
					if(x < mapa->ViewSize.Width && y < mapa->ViewSize.Height)
					{
						ITexture* vision_texture = driver->getTexture("../media/Texturas/units/vision_attack.png");
						DrawPosition = position2di(x*TILE_WIDTH,y*TILE_HEIGHT);
						mapa->PintarTile(vision_texture, DrawPosition.X, DrawPosition.Y);						
					}

				}
			}
		}
	}
}

bool DebugMenu::OnEvent(const SEvent& event)
{
	if (event.EventType == EET_MOUSE_INPUT_EVENT)
	{
		mapa->OnEventMapa(event);
	}
	else if(event.GUIEvent.EventType == EGET_CHECKBOX_CHANGED)
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
	else if(event.GUIEvent.EventType == EGET_SCROLL_BAR_CHANGED)
	{
		s32 id = event.GUIEvent.Caller->getID();

		switch(id)
		{
			case SCROLL_SPEED: s32 pos = ((IGUIScrollBar*)event.GUIEvent.Caller)->getPos();
                 			   gameEngine::setSpeed(pos);
							   break;
		}
	}

	else if(event.GUIEvent.EventType == EGET_BUTTON_CLICKED)
	{
		s32 id = event.GUIEvent.Caller->getID();

		IGUISpinBox* spbox_X = (IGUISpinBox*) env->getRootGUIElement()->getElementFromId(SPBOX_COORDX);
		IGUISpinBox* spbox_Y = (IGUISpinBox*) env->getRootGUIElement()->getElementFromId(SPBOX_COORDY);

		switch(id)
		{
			case BUTTON_ADD_IA: (gameEngine::addIAUnit((int)spbox_X->getValue(),(int)spbox_Y->getValue()))->aplicarTextura(driver);
								break;
			case BUTTON_ADD_UNIT: (gameEngine::addUserUnit((int)spbox_X->getValue(),(int)spbox_Y->getValue()))->aplicarTextura(driver);
								  break;
		}
	}
	return false;
}