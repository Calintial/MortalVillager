#include "DebugMenu.h"

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

	/*Cargar texturas imagenes*/
	state_search = driver->getTexture("../media/Imagenes/Debug/MEF/Search.png");
	state_approach = driver->getTexture("../media/Imagenes/Debug/MEF/Approach.png");
	state_attack = driver->getTexture("../media/Imagenes/Debug/MEF/Attack.png");
	state_flee = driver->getTexture("../media/Imagenes/Debug/MEF/Flee.png");
	state_recovery = driver->getTexture("../media/Imagenes/Debug/MEF/Recovery.png");
}

void DebugMenu::Draw()
{
	int ia_state = ((battleIA*)vUnits[0])->getState();
	if (DebugDevice->run())
	{        
		if(DebugDevice->isWindowActive() && driver)
		{
			if(ia_state == SEARCHING)
			{
				state_search = driver->getTexture("../media/Imagenes/Debug/MEF/Search_selected.png");
				driver->draw2DImage(state_search, core::position2d<s32>(859,10),
                core::rect<s32>(0,0,75 ,75), 0,
                video::SColor(255,255,255,255), true);
			}
			else
			{
				state_search = driver->getTexture("../media/Imagenes/Debug/MEF/Search.png");
				driver->draw2DImage(state_search, core::position2d<s32>(859,10),
                core::rect<s32>(0,0,75 ,75), 0,
                video::SColor(255,255,255,255), true);
			}

			if(ia_state == APPROACH)
			{
				state_approach = driver->getTexture("../media/Imagenes/Debug/MEF/Approach_selected.png");
				driver->draw2DImage(state_approach, core::position2d<s32>(1046,10),
                core::rect<s32>(0,0,75 ,75), 0,
                video::SColor(255,255,255,255), true);
			}
			else
			{
				state_approach = driver->getTexture("../media/Imagenes/Debug/MEF/Approach.png");
				driver->draw2DImage(state_approach, core::position2d<s32>(1046,10),
                core::rect<s32>(0,0,75 ,75), 0,
                video::SColor(255,255,255,255), true);
			}

			if(ia_state == ATTACK)
			{
				state_attack = driver->getTexture("../media/Imagenes/Debug/MEF/Attack_selected.png");
				driver->draw2DImage(state_attack, core::position2d<s32>(1046,197),
                core::rect<s32>(0,0,75 ,75), 0,
                video::SColor(255,255,255,255), true);
			}
			else
			{
				state_attack = driver->getTexture("../media/Imagenes/Debug/MEF/Attack.png");
				driver->draw2DImage(state_attack, core::position2d<s32>(1046,197),
                core::rect<s32>(0,0,75 ,75), 0,
                video::SColor(255,255,255,255), true);				
			}

			if(ia_state == FLEE)
			{
				state_flee = driver->getTexture("../media/Imagenes/Debug/MEF/Flee_selected.png");
				driver->draw2DImage(state_flee, core::position2d<s32>(1046,384),
                core::rect<s32>(0,0,75 ,75), 0,
                video::SColor(255,255,255,255), true);
			}
			else
			{
				state_flee = driver->getTexture("../media/Imagenes/Debug/MEF/Flee.png");
				driver->draw2DImage(state_flee, core::position2d<s32>(1046,384),
                core::rect<s32>(0,0,75 ,75), 0,
                video::SColor(255,255,255,255), true);
			}

			if(ia_state == RECOVERY)
			{
				state_recovery = driver->getTexture("../media/Imagenes/Debug/MEF/Recovery_selected.png");
				driver->draw2DImage(state_recovery, core::position2d<s32>(859,384),
                core::rect<s32>(0,0,75 ,75), 0,
                video::SColor(255,255,255,255), true);
			}
			else
			{
				state_recovery = driver->getTexture("../media/Imagenes/Debug/MEF/Recovery.png");
				driver->draw2DImage(state_recovery, core::position2d<s32>(859,384),
                core::rect<s32>(0,0,75 ,75), 0,
                video::SColor(255,255,255,255), true);
			}



			env->drawAll();
		}
	}
}