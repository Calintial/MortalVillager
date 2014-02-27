#include "InterfazPathfinding.h"

InterfazPathfinding::InterfazPathfinding(IrrlichtDevice * IrrDevice,shared_ptr<mapa2D> map){
	device = IrrDevice;
    env = IrrDevice->getGUIEnvironment();
    driver = IrrDevice->getVideoDriver();
    font = env->getFont("../media/fonthaettenschweiler.bmp");
    env->clear();
    init();

    mapa = map;
    caminoFinal = NULL;
	
	drawRegiones = false;
	drawEnlaces = false;
	drawCaminosInternos = false;
	drawCaminoFinal = false;
	estado = ESTADO_PINTAR;
	origen = destino = position2di(-1,-1);
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
	env->addButton(rect<s32>(dimensionPantallaX + 220,dimensionPantallaY+35,dimensionPantallaX + 430,dimensionPantallaY+60), 0, BUTTON_CLEAR,
        L"Vaciar", L"");
	env->addButton(rect<s32>(dimensionPantallaX + 220,75,dimensionPantallaX + 430,100), 0, BUTTON_SAVE,
        L"Guardar", L"");
}

void InterfazPathfinding::Draw()
{
	if (device->run())
	{        
		if(driver)
		{
			//font->draw(L"Velocidad del juego",
            //core::rect<s32>(350,dimensionPantallaY+25,500,dimensionPantallaY+50),video::SColor(255,0,0,0));
			
			DrawRegiones();
			DrawEnlacesYCaminos();
			DrawCaminoFinal();
			driver->draw2DRectangle(video::SColor(255,200,200,200),core::rect<s32>(dimensionPantallaX,0,driver->getScreenSize().Width,driver->getScreenSize().Height));
			driver->draw2DRectangle(video::SColor(255,200,200,200),core::rect<s32>(0,dimensionPantallaY,driver->getScreenSize().Width,driver->getScreenSize().Height));

			env->drawAll();
		}
	}
}

void InterfazPathfinding::DrawRegiones(){
	if (drawRegiones)
	{
		std::vector<Region*> regiones = mapa->getPathfinding()->getRegiones();
		for (int i = 0; i < regiones.size(); ++i)
		{
			position2di inicio = regiones[i]->getInicio();
			position2di final = regiones[i]->getFinal();
			final.X ++;
			final.Y ++;
			auto thick_old = driver->getMaterial2D().Thickness;
			driver->getMaterial2D().Thickness=12.f;
			driver->enableMaterial2D();
			driver->draw2DRectangleOutline(core::rect<s32>(mapa->getDrawPosition(inicio),mapa->getDrawPosition(final)),video::SColor(255,0,255,0));
			driver->getMaterial2D().Thickness=thick_old;
		}
	}
	
}

void InterfazPathfinding::DrawEnlacesYCaminos(){
	if (drawEnlaces || drawCaminosInternos)
	{
		std::vector<Enlace*> enlaces = mapa->getPathfinding()->getEnlaces();
		for (int i = 0; i < enlaces.size(); ++i)
		{
			
			if (drawEnlaces)
			{
				position2di inicio = enlaces[i]->getDestino();
				position2di final = enlaces[i]->getOrigen();
				final.X ++;
				final.Y ++;
				driver->draw2DRectangle(video::SColor(128,0,255,128),core::rect<s32>(mapa->getDrawPosition(inicio),mapa->getDrawPosition(final)));
			}
			
			if(drawCaminosInternos){
				std::vector<Camino> caminos = enlaces[i]->getIntraCaminosDestino();
				for (int j = 0; j < caminos.size(); ++j)
				{
					for (position2di paso: caminos[j].getCamino())
					{
						position2di pasoFinal = paso;
						pasoFinal.X++;
						pasoFinal.Y++;
						driver->draw2DRectangle(video::SColor(128,128,0,128),core::rect<s32>(mapa->getDrawPosition(paso),mapa->getDrawPosition(pasoFinal)));
					}
				}
			}
		}
	}	
}

void InterfazPathfinding::DrawCaminoFinal(){
	if (drawCaminoFinal && caminoFinal != NULL)
	{
		for(position2di paso: caminoFinal->getCamino()){
			position2di pasoFinal = paso;
			pasoFinal.X++;
			pasoFinal.Y++;
			driver->draw2DRectangle(video::SColor(255,255,0,0),core::rect<s32>(mapa->getDrawPosition(paso),mapa->getDrawPosition(pasoFinal)));
		}
	}
}

bool InterfazPathfinding::OnEvent(const SEvent& event)
{
	if (event.EventType == EET_MOUSE_INPUT_EVENT)
	{
		if (event.MouseInput.X < dimensionPantallaX || event.MouseInput.Y < dimensionPantallaY)
		{
			switch(event.MouseInput.Event)
			{
				case EMIE_LMOUSE_PRESSED_DOWN:
					{
						// Esto está copiapegado de mapa2D, cuidado por si cambia
						position2di pos_grid;
						pos_grid.X = (event.MouseInput.X) / TILE_WIDTH;
						pos_grid.Y = (event.MouseInput.Y) / TILE_HEIGHT;
						cout<<"Me has clicado en: "<< event.MouseInput.X << "," << event.MouseInput.Y << " - que corresponde a: "<< pos_grid.X<<","<<pos_grid.Y<<endl;
						if (estado == ESTADO_PINTAR)
						{
							Muro* muro = new Muro(1,pos_grid.X,pos_grid.Y);
							muro->aplicarTextura(device->getVideoDriver());
							mapa->setTile(pos_grid.X,pos_grid.Y,muro);
						}else{
							origen = pos_grid;
						}
						
					}
					break;
				case EMIE_RMOUSE_PRESSED_DOWN:
					{
						// Esto está copiapegado de mapa2D, cuidado por si cambia
						position2di pos_grid;
						pos_grid.X = (event.MouseInput.X) / TILE_WIDTH;
						pos_grid.Y = (event.MouseInput.Y) / TILE_HEIGHT;
						cout<<"Me has clicado en: "<< event.MouseInput.X << "," << event.MouseInput.Y << " - que corresponde a: "<< pos_grid.X<<","<<pos_grid.Y<<endl;
						if (estado == ESTADO_PINTAR)
						{
							Suelo* suelo = new Suelo(0,pos_grid.X,pos_grid.Y);
							suelo->aplicarTextura(device->getVideoDriver());
							mapa->setTile(pos_grid.X,pos_grid.Y,suelo);
						}else{
							destino = pos_grid;
						}
						
					}
					break;
			}
		}
	}else if (event.GUIEvent.EventType == EGET_BUTTON_CLICKED)
	{
		s32 id = event.GUIEvent.Caller->getID();
		switch(id)
		{

			case BUTTON_NEXT:{ 
					cout<<"Soy un boton!"<<endl;
					if (estado == ESTADO_PINTAR){
						mapa->getPathfinding()->run();
						estado = ESTADO_CAMINO;
					}else{
						if (origen.X != -1 && origen.Y != -1 && destino.X != -1 && destino.Y != -1)
						{
							caminoFinal = mapa->getPathfinding()->calcularCamino(origen,destino);
						}else{
							cerr<<"Debes poner origen y destino"<<endl;
						}
					}
				}
				break;
			case BUTTON_CLEAR:{
				estado = ESTADO_PINTAR;
				origen = destino = position2di(-1,-1);
				caminoFinal = NULL;
				mapa->getPathfinding()->clear();
			}
			case BUTTON_SAVE:{
				mapa->GuardarMapa();
			}
		}					
	}
	else if(event.GUIEvent.EventType == EGET_CHECKBOX_CHANGED)
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
	return false;
}