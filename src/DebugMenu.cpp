#include "DebugMenu.h"

int DebugMenu::unitSelected = 0;

DebugMenu::DebugMenu(IrrlichtDevice * IrrDevice, IDibujable** ia_units)
{
	DebugDevice = IrrDevice;
    env = IrrDevice->getGUIEnvironment();
    driver = IrrDevice->getVideoDriver();
    font = env->getFont("../media/fonthaettenschweiler.bmp");
    initDebugMenu();

    vUnits = ia_units;
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

			env->drawAll();
		}
	}
}

void DebugMenu::DrawMEF()
{
	int ia_state = ((battleIA*)vUnits[unitSelected])->getState();

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
	int ia_life = ((Unidades*)vUnits[unitSelected])->getLife();
	std::string string_life = "Vida:" + to_string(ia_life);
	std::string string_unit_selected = "Unidad seleccionada: " + to_string(unitSelected);

	font->draw(L"Parametros",
    core::rect<s32>(dimensionPantallaX + 59,509,dimensionPantallaX + 209,534),video::SColor(255,0,0,0));

	font->draw(stringw(string_unit_selected.c_str()),
    core::rect<s32>(dimensionPantallaX + 59,540,dimensionPantallaX + 209,565),video::SColor(255,0,0,0));

    font->draw(stringw(string_life.c_str()),
    core::rect<s32>(dimensionPantallaX + 59,571,dimensionPantallaX + 209,596),video::SColor(255,0,0,0));
}

void DebugMenu::setUnitSelected(int unit)
{
	unitSelected = unit;
}

int DebugMenu::getUnitSelected()
{
	return unitSelected;
}