#include "DebugMenu.h"


DebugMenu::DebugMenu(IrrlichtDevice * IrrDevice, vector<IDibujable*>* ia_units, mapa2D* map)
{
	DebugDevice = IrrDevice;
    env = IrrDevice->getGUIEnvironment();
    driver = IrrDevice->getVideoDriver();
    font = env->getFont("../media/fonthaettenschweiler.bmp");
    initDebugMenu();

    vUnits = ia_units;
    mapa = map;

	DebugDevice->setEventReceiver(this); 
	drawVision = false;
	drawAttackVision = false;
}

DebugMenu::~DebugMenu()
{

}

void DebugMenu::initDebugMenu()
{
	env->addCheckBox(false,rect<s32>(50,dimensionPantallaY+25,200,dimensionPantallaY+50), 0, CB_ATTACK_RANGE, 
							   L"Ver distancia ataque");
	env->addCheckBox(false,rect<s32>(50,dimensionPantallaY+50,200,dimensionPantallaY+75), 0, CB_VISION_RANGE, 
							   L"Ver distancia visión");

	IGUIScrollBar* speed_bar = env->addScrollBar(true,rect<s32>(300,dimensionPantallaY+50,500,dimensionPantallaY+75), 0, SCROLL_SPEED);

    speed_bar->setPos(gameEngine::getSpeed());

    /*Botones para añadir IA o unidades de usuario*/
	env->addButton(rect<s32>(550,dimensionPantallaY+35,750,dimensionPantallaY+60), 0, BUTTON_ADD_IA,
        L"Añadir IA", L"Añadir unidad controlada por la IA");

	env->addButton(rect<s32>(550,dimensionPantallaY+70,750,dimensionPantallaY+95), 0, BUTTON_ADD_UNIT,
        L"Añadir Unidad", L"Añadir unidad controlada por el usuario");

	/*Spin box para obtener las coordenadas para añadir las unidades*/
	IGUISpinBox* spbox_X = env->addSpinBox(L"0",rect<s32>(760,dimensionPantallaY+55,810,dimensionPantallaY+75),true,0,SPBOX_COORDX);
	IGUISpinBox* spbox_Y = env->addSpinBox(L"0",rect<s32>(830,dimensionPantallaY+55,880,dimensionPantallaY+75),true,0,SPBOX_COORDY);

	spbox_X->setDecimalPlaces(0);
	spbox_Y->setDecimalPlaces(0);

	spbox_X->setRange(0,26);
	spbox_Y->setRange(0,20);

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
		if(DebugDevice->isWindowActive() && driver)
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
	int ia_state = ((battleIA*)vUnits->at(mapa->getIASelected()))->getState();

	if(ia_state == SEARCHING)
	{
		state_search = driver->getTexture("../media/Imagenes/Debug/MEF/Search_selected.png");
		driver->draw2DImage(state_search, core::position2d<s32>(dimensionPantallaX + 59,10),
        core::rect<s32>(0,0,75 ,75), 0,
        video::SColor(255,255,255,255), true);
	}
	else
	{
		state_search = driver->getTexture("../media/Imagenes/Debug/MEF/Search.png");
		driver->draw2DImage(state_search, core::position2d<s32>(dimensionPantallaX + 59,10),
        core::rect<s32>(0,0,75 ,75), 0,
        video::SColor(255,255,255,255), true);
	}

	if(ia_state == APPROACH)
	{
		state_approach = driver->getTexture("../media/Imagenes/Debug/MEF/Approach_selected.png");
		driver->draw2DImage(state_approach, core::position2d<s32>(dimensionPantallaX + 246,10),
        core::rect<s32>(0,0,75 ,75), 0,
        video::SColor(255,255,255,255), true);
	}
	else
	{
		state_approach = driver->getTexture("../media/Imagenes/Debug/MEF/Approach.png");
		driver->draw2DImage(state_approach, core::position2d<s32>(dimensionPantallaX + 246,10),
        core::rect<s32>(0,0,75 ,75), 0,
        video::SColor(255,255,255,255), true);
	}

	if(ia_state == ATTACK)
	{
		state_attack = driver->getTexture("../media/Imagenes/Debug/MEF/Attack_selected.png");
		driver->draw2DImage(state_attack, core::position2d<s32>(dimensionPantallaX + 246,197),
        core::rect<s32>(0,0,75 ,75), 0,
        video::SColor(255,255,255,255), true);
	}
	else
	{
		state_attack = driver->getTexture("../media/Imagenes/Debug/MEF/Attack.png");
		driver->draw2DImage(state_attack, core::position2d<s32>(dimensionPantallaX + 246,197),
        core::rect<s32>(0,0,75 ,75), 0,
        video::SColor(255,255,255,255), true);				
	}

	if(ia_state == FLEE)
	{
		state_flee = driver->getTexture("../media/Imagenes/Debug/MEF/Flee_selected.png");
		driver->draw2DImage(state_flee, core::position2d<s32>(dimensionPantallaX + 246,384),
        core::rect<s32>(0,0,75 ,75), 0,
        video::SColor(255,255,255,255), true);
	}
	else
	{
		state_flee = driver->getTexture("../media/Imagenes/Debug/MEF/Flee.png");
		driver->draw2DImage(state_flee, core::position2d<s32>(dimensionPantallaX + 246,384),
        core::rect<s32>(0,0,75 ,75), 0,
        video::SColor(255,255,255,255), true);
	}

	if(ia_state == RECOVERY)
	{
		state_recovery = driver->getTexture("../media/Imagenes/Debug/MEF/Recovery_selected.png");
		driver->draw2DImage(state_recovery, core::position2d<s32>(dimensionPantallaX + 59,384),
        core::rect<s32>(0,0,75 ,75), 0,
        video::SColor(255,255,255,255), true);
	}
	else
	{
		state_recovery = driver->getTexture("../media/Imagenes/Debug/MEF/Recovery.png");
		driver->draw2DImage(state_recovery, core::position2d<s32>(dimensionPantallaX + 59,384),
        core::rect<s32>(0,0,75 ,75), 0,
        video::SColor(255,255,255,255), true);
	}

}

void DebugMenu::DrawParameters()
{
	int ia_life = ((Unidades*)vUnits->at(mapa->getIASelected()))->getLife();
	std::string string_life = "Vida:" + to_string(ia_life);
	std::string string_unit_selected = "Unidad IA seleccionada: " + to_string(mapa->getIASelected());

	font->draw(L"Parametros",
    core::rect<s32>(dimensionPantallaX + 59,509,dimensionPantallaX + 209,534),video::SColor(255,0,0,0));

	font->draw(stringw(string_unit_selected.c_str()),
    core::rect<s32>(dimensionPantallaX + 59,540,dimensionPantallaX + 209,565),video::SColor(255,0,0,0));

    font->draw(stringw(string_life.c_str()),
    core::rect<s32>(dimensionPantallaX + 59,571,dimensionPantallaX + 209,596),video::SColor(255,0,0,0));
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
		switch(event.MouseInput.Event)
		{
			case EMIE_LMOUSE_PRESSED_DOWN: mapa->OnEventMapa(event); break;
		}
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
			case BUTTON_ADD_IA: (gameEngine::addIAUnit((int)spbox_X->getValue(),(int)spbox_Y->getValue()))->Pintar(driver);
								break;
			case BUTTON_ADD_UNIT: (gameEngine::addUserUnit((int)spbox_X->getValue(),(int)spbox_Y->getValue()))->Pintar(driver);
								  break;
		}
	}
	return false;
}