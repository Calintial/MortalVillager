#include "InterfazPathfinding.h"

InterfazPathfinding::InterfazPathfinding(IrrlichtDevice * IrrDevice,mapa2D* map){
	device = IrrDevice;
    env = IrrDevice->getGUIEnvironment();
    driver = IrrDevice->getVideoDriver();
    font = env->getFont("../media/fonthaettenschweiler.bmp");
    init();

    mapa = map;
	
	drawRegiones = false;
	drawEnlaces = false;
	drawCaminosInternos = false;
	drawCaminoFinal = false;
}

InterfazPathfinding::~InterfazPathfinding(){}

void InterfazPathfinding::init(){
	env->addCheckBox(false,rect<s32>(dimensionPantallaX+10,0,dimensionPantallaX+160,25), 0, CB_REGIONES, 
							   L"Ver regiones");
	env->addCheckBox(false,rect<s32>(dimensionPantallaX+10,25,dimensionPantallaX+160,50), 0, CB_ENLACES, 
							   L"Ver enlaces");
	env->addCheckBox(false,rect<s32>(dimensionPantallaX+10,50,dimensionPantallaX+160,75), 0, CB_CAMINOS_INTERNOS, 
							   L"Ver caminos internos");
	env->addCheckBox(false,rect<s32>(dimensionPantallaX+10,75,dimensionPantallaX+160,100), 0, CB_CAMINO_FINAL, 
							   L"Ver camino final");
	env->addButton(rect<s32>(dimensionPantallaX + 10,dimensionPantallaY+35,dimensionPantallaX + 210,dimensionPantallaY+60), 0, BUTTON_NEXT,
        L"Procesar", L"Iniciar análisis del mapa, generación de regiones y cálculo de caminos internos");

}

void InterfazPathfinding::Draw()
{
	if (device->run())
	{        
		if(driver)
		{
			//font->draw(L"Velocidad del juego",
            //core::rect<s32>(350,dimensionPantallaY+25,500,dimensionPantallaY+50),video::SColor(255,0,0,0));
			
			//DrawParameters();
			//DrawMEF();
			//DrawVisions();

			env->drawAll();
		}
	}
}


bool InterfazPathfinding::OnEvent(const SEvent& event)
{
	
	
	if(event.GUIEvent.EventType == EGET_CHECKBOX_CHANGED)
	{
		s32 id = event.GUIEvent.Caller->getID();
		switch(id)
		{
			case CB_REGIONES: drawRegiones = ((IGUICheckBox*)event.GUIEvent.Caller)->isChecked();
								  break;
			case CB_ENLACES: drawEnlaces = ((IGUICheckBox*)event.GUIEvent.Caller)->isChecked();
								  break;
			case CB_CAMINOS_INTERNOS: drawCaminosInternos = ((IGUICheckBox*)event.GUIEvent.Caller)->isChecked();
								  break;
			case CB_CAMINO_FINAL: drawCaminoFinal = ((IGUICheckBox*)event.GUIEvent.Caller)->isChecked();
								  break;
		}
		
	}
	else if (event.GUIEvent.EventType == EGET_BUTTON_CLICKED)
	{
		s32 id = event.GUIEvent.Caller->getID();
		switch(id)
		{
			case BUTTON_NEXT: mapa->getPathfinding()->createRegions();
								break;
		}					
	}
	/*
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
	}*/
	return false;
}