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
	env->addButton(rect<s32>(1050,dimensionPantallaY+45,1250,dimensionPantallaY+70), 0, BUTTON_SEE_SUBARBOL,
        L"Ver Subarbol", L"Ver subarbol seleccionado");

	/*Desplegables para seleccionar unidad a insertar*/
	IGUIComboBox* combo_subarbol = env->addComboBox (rect<s32>(900,dimensionPantallaY+65,1000,dimensionPantallaY+85), 0,COMBO_SUBARBOL);
	combo_subarbol->addItem(L"Ninguno");
	combo_subarbol->addItem(L"Principal");
	combo_subarbol->addItem(L"Subarbol Defensa");
	combo_subarbol->addItem(L"Subarbol Construccion");
	combo_subarbol->addItem(L"Subarbol Espadachines");
	combo_subarbol->addItem(L"Subarbol Lanceros");
	combo_subarbol->addItem(L"Subarbol Arqueros");

	/*Cargar texturas imagenes*/
	node_1 = driver->getTexture("../media/Imagenes/Debug/DT/enemigo_cerca_no_selected.png");
	node_2 = driver->getTexture("../media/Imagenes/Debug/DT/vida_cc_no_selected.png");
	node_3 = driver->getTexture("../media/Imagenes/Debug/DT/soldados_no_selected.png");
	node_4 = driver->getTexture("../media/Imagenes/Debug/DT/nada_no_selected.png");
	node_5 = driver->getTexture("../media/Imagenes/Debug/DT/defender_no_selected.png");
	node_6 = driver->getTexture("../media/Imagenes/Debug/DT/superioridad_no_selected.png");
	node_7 = driver->getTexture("../media/Imagenes/Debug/DT/atacar_no_selected.png");
	node_8 = driver->getTexture("../media/Imagenes/Debug/DT/lanzas_mayor_no_selected");
	node_9 = driver->getTexture("../media/Imagenes/Debug/DT/cuartel_no_selected.png");
	node_10 = driver->getTexture("../media/Imagenes/Debug/DT/ald_esp_no_selected.png");
	node_11 = driver->getTexture("../media/Imagenes/Debug/DT/rec_espadachin_no_selected.png");
	node_12 = driver->getTexture("../media/Imagenes/Debug/DT/crear_espadachin_no_selected.png");
	node_13 = driver->getTexture("../media/Imagenes/Debug/DT/nada_no_selected.png");
	node_14 = driver->getTexture("../media/Imagenes/Debug/DT/rec_aldeano_no_selected.png");
	node_15 = driver->getTexture("../media/Imagenes/Debug/DT/crear_aldeano_no_selected.png");
	node_16 = driver->getTexture("../media/Imagenes/Debug/DT/nada_no_selected.png");
	node_17 = driver->getTexture("../media/Imagenes/Debug/DT/rec_cuartel_no_selected.png");
	node_18 = driver->getTexture("../media/Imagenes/Debug/DT/crear_cuartel_no_selected.png");
	node_19 = driver->getTexture("../media/Imagenes/Debug/DT/granja_no_selected.png");
	node_20 = driver->getTexture("../media/Imagenes/Debug/DT/nada_no_selected.png");
	node_21 = driver->getTexture("../media/Imagenes/Debug/DT/rec_granja_no_selected.png");	
	node_22 = driver->getTexture("../media/Imagenes/Debug/DT/crear_granja_no_selected.png");
	node_23 = driver->getTexture("../media/Imagenes/Debug/DT/nada_no_selected.png");
	node_24 = driver->getTexture("../media/Imagenes/Debug/DT/arquero_mayor_no_selected.png");
	node_25 = driver->getTexture("../media/Imagenes/Debug/DT/lanceria_no_selected.png");
	node_26 = driver->getTexture("../media/Imagenes/Debug/DT/aldeano_lancero_no_selected.png");
	node_27 = driver->getTexture("../media/Imagenes/Debug/DT/rec_lancero_no_selected.png");
	node_28 = driver->getTexture("../media/Imagenes/Debug/DT/crear_lancero_no_selected.png");
	node_29 = driver->getTexture("../media/Imagenes/Debug/DT/nada_no_selected.png");
	node_30 = driver->getTexture("../media/Imagenes/Debug/DT/rec_aldeano_no_selected.png");
	node_31 = driver->getTexture("../media/Imagenes/Debug/DT/crear_aldeano_no_selected.png");
	node_32 = driver->getTexture("../media/Imagenes/Debug/DT/nada_no_selected.png");
	node_33 = driver->getTexture("../media/Imagenes/Debug/DT/rec_lanceria_no_selected.png");
	node_34 = driver->getTexture("../media/Imagenes/Debug/DT/crear_lanceria_no_selected.png");
	node_35 = driver->getTexture("../media/Imagenes/Debug/DT/granja_no_selected.png");
	node_36 = driver->getTexture("../media/Imagenes/Debug/DT/nada_no_selected.png");
	node_37 = driver->getTexture("../media/Imagenes/Debug/DT/rec_granja_no_selected.png");	
	node_38 = driver->getTexture("../media/Imagenes/Debug/DT/crear_granja_no_selected.png");
	node_39 = driver->getTexture("../media/Imagenes/Debug/DT/nada_no_selected.png");
	node_40 = driver->getTexture("../media/Imagenes/Debug/DT/espadachin_arcos_no_selected.png");
	node_41 = driver->getTexture("../media/Imagenes/Debug/DT/arqueria_no_select.png");
	node_42 = driver->getTexture("../media/Imagenes/Debug/DT/aldeano_arquero_no_selected.png");
	node_43 = driver->getTexture("../media/Imagenes/Debug/DT/rec_arquero_no_selected.png");
	node_44 = driver->getTexture("../media/Imagenes/Debug/DT/crear_arquero_no_selected.png");
	node_45 = driver->getTexture("../media/Imagenes/Debug/DT/nada_no_selected.png");
	node_46 = driver->getTexture("../media/Imagenes/Debug/DT/rec_aldeano_no_selected.png");
	node_47 = driver->getTexture("../media/Imagenes/Debug/DT/crear_aldeano_no_selected.png");
	node_48 = driver->getTexture("../media/Imagenes/Debug/DT/nada_no_selected.png");
	node_49 = driver->getTexture("../media/Imagenes/Debug/DT/rec_arqueria_no_selected.png");
	node_50 = driver->getTexture("../media/Imagenes/Debug/DT/crear_arqueria_no_selected.png");
	node_51 = driver->getTexture("../media/Imagenes/Debug/DT/granja_no_selected.png");
	node_52 = driver->getTexture("../media/Imagenes/Debug/DT/nada_no_selected.png");
	node_53 = driver->getTexture("../media/Imagenes/Debug/DT/rec_granja_no_selected.png");	
	node_54 = driver->getTexture("../media/Imagenes/Debug/DT/crear_granja_no_selected.png");
	node_55 = driver->getTexture("../media/Imagenes/Debug/DT/nada_no_selected.png");
	node_56 = driver->getTexture("../media/Imagenes/Debug/DT/granja_no_selected.png");
	node_57 = driver->getTexture("../media/Imagenes/Debug/DT/atacar_no_selected.png");
	node_58 = driver->getTexture("../media/Imagenes/Debug/DT/nada_no_selected.png");
	node_59 = driver->getTexture("../media/Imagenes/Debug/DT/rec_granja_no_selected.png");
	node_60 = driver->getTexture("../media/Imagenes/Debug/DT/crear_granja_no_selected.png");
	node_61 = driver->getTexture("../media/Imagenes/Debug/DT/nada_no_selected.png");
}

void DebugMaster::Draw(vector<int> caminoNodos)
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
			DrawMEF(caminoNodos);

			env->drawAll();
		}
	}
}

void DebugMaster::DrawMEF(vector<int> caminoNodos)
{
	cout << "CAMINO:";
	switch(subarbolElegido)
	{
		case 0:
			break;
		case 1:
		//Principal
			//Lineas
			driver->draw2DLine(core::position2d<s32>(dimensionPantallaX + 260,20), core::position2d<s32>(dimensionPantallaX + 180, 120), video::SColor(255,0,0,0));
			driver->draw2DLine(core::position2d<s32>(dimensionPantallaX + 290,20), core::position2d<s32>(dimensionPantallaX + 380, 120), video::SColor(255,0,0,0));
				
			for(int i=0; i<caminoNodos.size(); i++)
			{
				cout << caminoNodos.at(i) << "-->";
				//NodoEnemigoCercaCC				
				if(caminoNodos.at(i) == 1)
				{
					node_1 = driver->getTexture("../media/Imagenes/Debug/DT/enemigo_cerca_selected.png");
				}
				
				//NodoVidaCC
				if(caminoNodos.at(i) == 2)
				{
					node_2 = driver->getTexture("../media/Imagenes/Debug/DT/vida_cc_selected.png");
				}

				//NodoLanzasMayorEspadas
				if(caminoNodos.at(i) == 8)
				{
					node_8 = driver->getTexture("../media/Imagenes/Debug/DT/lanzas_mayor_selected.png");
				}
			}	
			
			//Pinta
			driver->draw2DImage(node_1, core::position2d<s32>(dimensionPantallaX + 250,10),
			core::rect<s32>(0,0,75 ,75), 0, video::SColor(255,255,255,255), true);
			
			driver->draw2DImage(node_2, core::position2d<s32>(dimensionPantallaX + 150,120),
				core::rect<s32>(0,0,75 ,75), 0, video::SColor(255,255,255,255), true);
				
			driver->draw2DImage(node_8, core::position2d<s32>(dimensionPantallaX + 350,120),
				core::rect<s32>(0,0,75 ,75), 0, video::SColor(255,255,255,255), true);
			
			break;
		case 2:
		//Defensa
			//Lineas
			driver->draw2DLine(core::position2d<s32>(dimensionPantallaX + 260,20), core::position2d<s32>(dimensionPantallaX + 180, 120), video::SColor(255,0,0,0));
			driver->draw2DLine(core::position2d<s32>(dimensionPantallaX + 290,20), core::position2d<s32>(dimensionPantallaX + 380, 120), video::SColor(255,0,0,0));
			driver->draw2DLine(core::position2d<s32>(dimensionPantallaX + 160,180), core::position2d<s32>(dimensionPantallaX + 385, 50), video::SColor(255,0,0,0));
			driver->draw2DLine(core::position2d<s32>(dimensionPantallaX + 150,180), core::position2d<s32>(dimensionPantallaX + 100, 250), video::SColor(255,0,0,0));
			driver->draw2DLine(core::position2d<s32>(dimensionPantallaX + 400,80), core::position2d<s32>(dimensionPantallaX + 370, 250), video::SColor(255,0,0,0));
			for(int i=0; i<caminoNodos.size(); i++)
			{
				cout << caminoNodos.at(i) << "-->";
				//NodoVidaCC
				if(caminoNodos.at(i) == 2)
				{
					node_2 = driver->getTexture("../media/Imagenes/Debug/DT/vida_cc_selected.png");
				}
				
				//NodoTengoSoldados
				if(caminoNodos.at(i) == 3)
				{
					node_3 = driver->getTexture("../media/Imagenes/Debug/DT/soldados_selected.png");
				}
				
				//Nada
				if(caminoNodos.at(i) == 4)
				{
					node_4 = driver->getTexture("../media/Imagenes/Debug/DT/nada_selected.png");
				}
				
				//Defender
				if(caminoNodos.at(i) == 5)
				{
					node_5 = driver->getTexture("../media/Imagenes/Debug/DT/defender_selected.png");
				}
				
				//LanzasMayorEspadas
				if(caminoNodos.at(i) == 8)
				{
					node_8 = driver->getTexture("../media/Imagenes/Debug/DT/lanzas_mayor_selected.png");
				}
				
				//Superioridad
				if(caminoNodos.at(i) == 6)
				{
					node_6 = driver->getTexture("../media/Imagenes/Debug/DT/superioridad_selected.png");
				}
				
				//Atacar
				if(caminoNodos.at(i) == 7)
				{
					node_7 = driver->getTexture("../media/Imagenes/Debug/DT/atacar_selected.png");
				}
			}
			
			//Pinta
			driver->draw2DImage(node_2, core::position2d<s32>(dimensionPantallaX + 250,10),
				core::rect<s32>(0,0,75 ,75), 0, video::SColor(255,255,255,255), true);
			
			driver->draw2DImage(node_3, core::position2d<s32>(dimensionPantallaX + 150,120),
				core::rect<s32>(0,0,75 ,75), 0, video::SColor(255,255,255,255), true);
				
			driver->draw2DImage(node_4, core::position2d<s32>(dimensionPantallaX + 80,230),
				core::rect<s32>(0,0,75 ,75), 0, video::SColor(255,255,255,255), true);
				
			driver->draw2DImage(node_5, core::position2d<s32>(dimensionPantallaX + 150,180),
				core::rect<s32>(0,0,75 ,75), 0, video::SColor(255,255,255,255), true);
			
			driver->draw2DImage(node_8, core::position2d<s32>(dimensionPantallaX + 375,40),
				core::rect<s32>(0,0,75 ,75), 0, video::SColor(255,255,255,255), true);
			
			driver->draw2DImage(node_6, core::position2d<s32>(dimensionPantallaX + 350,120),
				core::rect<s32>(0,0,75 ,75), 0, video::SColor(255,255,255,255), true);
			
			driver->draw2DImage(node_7, core::position2d<s32>(dimensionPantallaX + 300,230),
				core::rect<s32>(0,0,75 ,75), 0, video::SColor(255,255,255,255), true);
			break;
		case 3:
		//Construcción
			for(int i=0; i<caminoNodos.size(); i++)
			{
				cout << caminoNodos.at(i) << "-->";
				//LanzasMayorEspadas
				if(caminoNodos.at(i) == 8)
				{
					node_8 = driver->getTexture("../media/Imagenes/Debug/DT/lanzas_mayor_selected.png");
				}
				
				//Cuartel
				if(caminoNodos.at(i) == 9)
				{
					node_9 = driver->getTexture("../media/Imagenes/Debug/DT/cuartel_selected.png");	
				}
				
				//ArquerosMayorLanzas
				if(caminoNodos.at(i) == 24)
				{
					node_24 = driver->getTexture("../media/Imagenes/Debug/DT/arquero_mayor_selected.png");
				}
				
				//Lanceria
				if(caminoNodos.at(i) == 25)
				{
					node_25 = driver->getTexture("../media/Imagenes/Debug/DT/lanceria_selected.png");
				}
				
				//EspadachinesMayorArcos
				if(caminoNodos.at(i) == 40)
				{
					node_40 = driver->getTexture("../media/Imagenes/Debug/DT/espadachin_arcos_selected.png");	
				}
				
				//Arqueria
				if(caminoNodos.at(i) == 41)
				{
					node_41 = driver->getTexture("../media/Imagenes/Debug/DT/arqueria_selected.png");	
				}
				
				//Atacar
				if(caminoNodos.at(i) == 57)
				{
					node_57 = driver->getTexture("../media/Imagenes/Debug/DT/atacar_selected.png");
				}
				
				//Granja
				if(caminoNodos.at(i) == 56)
				{
					node_56 = driver->getTexture("../media/Imagenes/Debug/DT/granja_selected.png");
				}
				
				//Nada
				if(caminoNodos.at(i) == 58)
				{
					node_58 = driver->getTexture("../media/Imagenes/Debug/DT/nada_selected.png");	
				}
				
				//RecGranja
				if(caminoNodos.at(i) == 59)
				{
					node_59 = driver->getTexture("../media/Imagenes/Debug/DT/rec_granja_selected.png");
				}
				
				//Crear Granjas
				if(caminoNodos.at(i) == 60)
				{
					node_60 = driver->getTexture("../media/Imagenes/Debug/DT/crear_granja_selected.png");	
				}
				
				//Nada
				if(caminoNodos.at(i) == 61)
				{
					node_61 = driver->getTexture("../media/Imagenes/Debug/DT/nada_selected.png");		
				}
			}
			
			//Pinta
			driver->draw2DImage(node_8, core::position2d<s32>(dimensionPantallaX + 80,10),
				core::rect<s32>(0,0,75 ,75), 0, video::SColor(255,255,255,255), true);
				
			driver->draw2DImage(node_9, core::position2d<s32>(dimensionPantallaX + 40,120),
				core::rect<s32>(0,0,75 ,75), 0, video::SColor(255,255,255,255), true);
				
			driver->draw2DImage(node_24, core::position2d<s32>(dimensionPantallaX + 120,120),
				core::rect<s32>(0,0,75 ,75), 0, video::SColor(255,255,255,255), true);
				
			driver->draw2DImage(node_25, core::position2d<s32>(dimensionPantallaX + 80,220),
				core::rect<s32>(0,0,75 ,75), 0, video::SColor(255,255,255,255), true);
				
			driver->draw2DImage(node_40, core::position2d<s32>(dimensionPantallaX + 160,220),
				core::rect<s32>(0,0,75 ,75), 0, video::SColor(255,255,255,255), true);
				
			driver->draw2DImage(node_41, core::position2d<s32>(dimensionPantallaX + 100,320),
				core::rect<s32>(0,0,75 ,75), 0, video::SColor(255,255,255,255), true);
				
			driver->draw2DImage(node_57, core::position2d<s32>(dimensionPantallaX + 200,375),
				core::rect<s32>(0,0,75 ,75), 0, video::SColor(255,255,255,255), true);
				
			driver->draw2DImage(node_56, core::position2d<s32>(dimensionPantallaX + 200,320),
				core::rect<s32>(0,0,75 ,75), 0, video::SColor(255,255,255,255), true);
				
			driver->draw2DImage(node_58, core::position2d<s32>(dimensionPantallaX + 160,420),
				core::rect<s32>(0,0,75 ,75), 0, video::SColor(255,255,255,255), true);
				
			driver->draw2DImage(node_59, core::position2d<s32>(dimensionPantallaX + 240,420),
				core::rect<s32>(0,0,75 ,75), 0, video::SColor(255,255,255,255), true);
				
			driver->draw2DImage(node_60, core::position2d<s32>(dimensionPantallaX + 200,520),
				core::rect<s32>(0,0,75 ,75), 0, video::SColor(255,255,255,255), true);
				
			driver->draw2DImage(node_61, core::position2d<s32>(dimensionPantallaX + 280,520),
				core::rect<s32>(0,0,75 ,75), 0, video::SColor(255,255,255,255), true);
			break;
			
		case 4:
		//Espadachines
			for(int i=0; i<caminoNodos.size(); i++)
			{
				cout << caminoNodos.at(i) << "-->";
				//Cuartel				
				if(caminoNodos.at(i) == 9)
				{
					node_9 = driver->getTexture("../media/Imagenes/Debug/DT/cuartel_selected.png");
				}
				//Aldeano espadachin
				if(caminoNodos.at(i) == 10)
				{
					node_10 = driver->getTexture("../media/Imagenes/Debug/DT/ald_esp_selected.png");
				}
				if(caminoNodos.at(i) == 11)
				{
					node_11 = driver->getTexture("../media/Imagenes/Debug/DT/rec_espadachin_no_selected.png");
				}
				if(caminoNodos.at(i) == 12)
				{
					node_12 = driver->getTexture("../media/Imagenes/Debug/DT/crear_espadachin_no_selected.png");
				}
				if(caminoNodos.at(i) == 13)
				{
					node_13 = driver->getTexture("../media/Imagenes/Debug/DT/nada_no_selected.png");
				}
				if(caminoNodos.at(i) == 14)
				{
					node_14 = driver->getTexture("../media/Imagenes/Debug/DT/rec_aldeano_no_selected.png");
				}
				if(caminoNodos.at(i) == 15)
				{
					node_15 = driver->getTexture("../media/Imagenes/Debug/DT/crear_aldeano_no_selected.png");
				}
				if(caminoNodos.at(i) == 16)
				{
					node_16 = driver->getTexture("../media/Imagenes/Debug/DT/nada_no_selected.png");
				}
				if(caminoNodos.at(i) == 17)
				{
					node_17 = driver->getTexture("../media/Imagenes/Debug/DT/rec_cuartel_no_selected.png");
				}
				if(caminoNodos.at(i) == 18)
				{
					node_18 = driver->getTexture("../media/Imagenes/Debug/DT/crear_cuartel_no_selected.png");
				}
				if(caminoNodos.at(i) == 19)
				{
					node_19 = driver->getTexture("../media/Imagenes/Debug/DT/granja_no_selected.png");
				}
				if(caminoNodos.at(i) == 20)	
				{
					node_20 = driver->getTexture("../media/Imagenes/Debug/DT/nada_no_selected.png");
				}
				if(caminoNodos.at(i) == 21)
				{
					node_21 = driver->getTexture("../media/Imagenes/Debug/DT/rec_granja_no_selected.png");
				}
				if(caminoNodos.at(i) == 22)
				{	
					node_22 = driver->getTexture("../media/Imagenes/Debug/DT/crear_granja_no_selected.png");
				}
				if(caminoNodos.at(i) == 23)
				{
					node_23 = driver->getTexture("../media/Imagenes/Debug/DT/nada_no_selected.png");
				}
			}
			
			//Pinta
			driver->draw2DImage(node_9, core::position2d<s32>(dimensionPantallaX + 250,10),
				core::rect<s32>(0,0,75 ,75), 0, video::SColor(255,255,255,255), true);
				
			driver->draw2DImage(node_10, core::position2d<s32>(dimensionPantallaX + 200,110),
				core::rect<s32>(0,0,75 ,75), 0, video::SColor(255,255,255,255), true);
				
			driver->draw2DImage(node_11, core::position2d<s32>(dimensionPantallaX + 140,210),
				core::rect<s32>(0,0,75 ,75), 0, video::SColor(255,255,255,255), true);
				
			driver->draw2DImage(node_12, core::position2d<s32>(dimensionPantallaX + 90,310),
				core::rect<s32>(0,0,75 ,75), 0, video::SColor(255,255,255,255), true);
				
			driver->draw2DImage(node_13, core::position2d<s32>(dimensionPantallaX + 180,310),
				core::rect<s32>(0,0,75 ,75), 0, video::SColor(255,255,255,255), true);
				
			driver->draw2DImage(node_14, core::position2d<s32>(dimensionPantallaX + 270,210),
				core::rect<s32>(0,0,75 ,75), 0, video::SColor(255,255,255,255), true);
				
			driver->draw2DImage(node_15, core::position2d<s32>(dimensionPantallaX + 230,310),
				core::rect<s32>(0,0,75 ,75), 0, video::SColor(255,255,255,255), true);
				
			driver->draw2DImage(node_16, core::position2d<s32>(dimensionPantallaX + 310,310),
				core::rect<s32>(0,0,75 ,75), 0, video::SColor(255,255,255,255), true);
				
			driver->draw2DImage(node_17, core::position2d<s32>(dimensionPantallaX + 360,110),
				core::rect<s32>(0,0,75 ,75), 0, video::SColor(255,255,255,255), true);
				
			driver->draw2DImage(node_18, core::position2d<s32>(dimensionPantallaX + 310,210),
				core::rect<s32>(0,0,75 ,75), 0, video::SColor(255,255,255,255), true);
				
			driver->draw2DImage(node_19, core::position2d<s32>(dimensionPantallaX + 400,210),
				core::rect<s32>(0,0,75 ,75), 0, video::SColor(255,255,255,255), true);
				
			driver->draw2DImage(node_20, core::position2d<s32>(dimensionPantallaX + 360,310),
				core::rect<s32>(0,0,75 ,75), 0, video::SColor(255,255,255,255), true);
				
			driver->draw2DImage(node_21, core::position2d<s32>(dimensionPantallaX + 430,310),
				core::rect<s32>(0,0,75 ,75), 0, video::SColor(255,255,255,255), true);
				
			driver->draw2DImage(node_22, core::position2d<s32>(dimensionPantallaX + 400,410),
				core::rect<s32>(0,0,75 ,75), 0, video::SColor(255,255,255,255), true);	
				
			driver->draw2DImage(node_23, core::position2d<s32>(dimensionPantallaX + 460,410),
				core::rect<s32>(0,0,75 ,75), 0, video::SColor(255,255,255,255), true);
			break;
		case 5:
		//Lanceros
			for(int i=0; i<caminoNodos.size(); i++)
			{
				cout << caminoNodos.at(i) << "-->";
				if(caminoNodos.at(i) == 25)
				{
					node_25 = driver->getTexture("../media/Imagenes/Debug/DT/lanceria_no_selected.png");
				}
				if(caminoNodos.at(i) == 26)
				{
					node_26 = driver->getTexture("../media/Imagenes/Debug/DT/aldeano_lancero_no_selected.png");
				}
				if(caminoNodos.at(i) == 27)
				{
					node_27 = driver->getTexture("../media/Imagenes/Debug/DT/rec_lancero_no_selected.png");
				}
				if(caminoNodos.at(i) == 28)
				{
					node_28 = driver->getTexture("../media/Imagenes/Debug/DT/crear_lancero_no_selected.png");
				}
				if(caminoNodos.at(i) == 29)
				{
					node_29 = driver->getTexture("../media/Imagenes/Debug/DT/nada_no_selected.png");
				}
				if(caminoNodos.at(i) == 30)
				{
					node_30 = driver->getTexture("../media/Imagenes/Debug/DT/rec_aldeano_no_selected.png");
				}
				if(caminoNodos.at(i) == 31)
				{
					node_31 = driver->getTexture("../media/Imagenes/Debug/DT/crear_aldeano_no_selected.png");
				}
				if(caminoNodos.at(i) == 32)
				{
					node_32 = driver->getTexture("../media/Imagenes/Debug/DT/nada_no_selected.png");
				}
				if(caminoNodos.at(i) == 33)
				{
					node_33 = driver->getTexture("../media/Imagenes/Debug/DT/rec_lanceria_no_selected.png");
				}
				if(caminoNodos.at(i) == 34)
				{
					node_34 = driver->getTexture("../media/Imagenes/Debug/DT/crear_lanceria_no_selected.png");
				}
				if(caminoNodos.at(i) == 35)
				{
					node_35 = driver->getTexture("../media/Imagenes/Debug/DT/granja_no_selected.png");
				}
				if(caminoNodos.at(i) == 36)
				{
					node_36 = driver->getTexture("../media/Imagenes/Debug/DT/nada_no_selected.png");
				}
				if(caminoNodos.at(i) == 37)
				{
					node_37 = driver->getTexture("../media/Imagenes/Debug/DT/rec_granja_no_selected.png");
				}
				if(caminoNodos.at(i) == 38)
				{
					node_38 = driver->getTexture("../media/Imagenes/Debug/DT/crear_granja_no_selected.png");
				}
				if(caminoNodos.at(i) == 39)
				{
					node_39 = driver->getTexture("../media/Imagenes/Debug/DT/nada_no_selected.png");
				}
			}
			
			//Pinta
			driver->draw2DImage(node_25, core::position2d<s32>(dimensionPantallaX + 250,10),
				core::rect<s32>(0,0,75 ,75), 0, video::SColor(255,255,255,255), true);
				
			driver->draw2DImage(node_26, core::position2d<s32>(dimensionPantallaX + 200,110),
				core::rect<s32>(0,0,75 ,75), 0, video::SColor(255,255,255,255), true);
				
			driver->draw2DImage(node_27, core::position2d<s32>(dimensionPantallaX + 140,210),
				core::rect<s32>(0,0,75 ,75), 0, video::SColor(255,255,255,255), true);
				
			driver->draw2DImage(node_28, core::position2d<s32>(dimensionPantallaX + 90,310),
				core::rect<s32>(0,0,75 ,75), 0, video::SColor(255,255,255,255), true);
				
			driver->draw2DImage(node_29, core::position2d<s32>(dimensionPantallaX + 180,310),
				core::rect<s32>(0,0,75 ,75), 0, video::SColor(255,255,255,255), true);
				
			driver->draw2DImage(node_30, core::position2d<s32>(dimensionPantallaX + 270,210),
				core::rect<s32>(0,0,75 ,75), 0, video::SColor(255,255,255,255), true);
				
			driver->draw2DImage(node_31, core::position2d<s32>(dimensionPantallaX + 230,310),
				core::rect<s32>(0,0,75 ,75), 0, video::SColor(255,255,255,255), true);
				
			driver->draw2DImage(node_32, core::position2d<s32>(dimensionPantallaX + 310,310),
				core::rect<s32>(0,0,75 ,75), 0, video::SColor(255,255,255,255), true);
				
			driver->draw2DImage(node_33, core::position2d<s32>(dimensionPantallaX + 360,110),
				core::rect<s32>(0,0,75 ,75), 0, video::SColor(255,255,255,255), true);
				
			driver->draw2DImage(node_34, core::position2d<s32>(dimensionPantallaX + 310,210),
				core::rect<s32>(0,0,75 ,75), 0, video::SColor(255,255,255,255), true);
				
			driver->draw2DImage(node_35, core::position2d<s32>(dimensionPantallaX + 400,210),
				core::rect<s32>(0,0,75 ,75), 0, video::SColor(255,255,255,255), true);
				
			driver->draw2DImage(node_36, core::position2d<s32>(dimensionPantallaX + 360,310),
				core::rect<s32>(0,0,75 ,75), 0, video::SColor(255,255,255,255), true);
				
			driver->draw2DImage(node_37, core::position2d<s32>(dimensionPantallaX + 430,310),
				core::rect<s32>(0,0,75 ,75), 0, video::SColor(255,255,255,255), true);
				
			driver->draw2DImage(node_38, core::position2d<s32>(dimensionPantallaX + 400,410),
				core::rect<s32>(0,0,75 ,75), 0, video::SColor(255,255,255,255), true);	
				
			driver->draw2DImage(node_39, core::position2d<s32>(dimensionPantallaX + 460,410),
				core::rect<s32>(0,0,75 ,75), 0, video::SColor(255,255,255,255), true);
			break;
		case 6:
		//Arqueros
			for(int i=0; i<caminoNodos.size(); i++)
			{
				cout << caminoNodos.at(i) << "-->";
				
				if(caminoNodos.at(i) == 41)
				{
					node_41 = driver->getTexture("../media/Imagenes/Debug/DT/arqueria_no_selected.png");
				}
				if(caminoNodos.at(i) == 42)
				{
					node_42 = driver->getTexture("../media/Imagenes/Debug/DT/aldeano_arquero_no_selected.png");
				}
				if(caminoNodos.at(i) == 43)
				{
					node_43 = driver->getTexture("../media/Imagenes/Debug/DT/rec_arquero_no_selected.png");
				}
				if(caminoNodos.at(i) == 44)
				{
					node_44 = driver->getTexture("../media/Imagenes/Debug/DT/crear_arquero_no_selected.png");
				}
				if(caminoNodos.at(i) == 45)
				{
					node_45 = driver->getTexture("../media/Imagenes/Debug/DT/nada_no_selected.png");
				}
				if(caminoNodos.at(i) == 46)
				{
					node_46 = driver->getTexture("../media/Imagenes/Debug/DT/rec_aldeano_no_selected.png");
				}
				if(caminoNodos.at(i) == 47)
				{
					node_47 = driver->getTexture("../media/Imagenes/Debug/DT/crear_aldeano_no_selected.png");
				}
				if(caminoNodos.at(i) == 48)
				{
					node_48 = driver->getTexture("../media/Imagenes/Debug/DT/nada_no_selected.png");
				}
				if(caminoNodos.at(i) == 49)
				{
					node_49 = driver->getTexture("../media/Imagenes/Debug/DT/rec_arqueria_no_selected.png");
				}
				if(caminoNodos.at(i) == 50)
				{
					node_50 = driver->getTexture("../media/Imagenes/Debug/DT/crear_arqueria_no_selected.png");
				}
				if(caminoNodos.at(i) == 51)
				{
					node_51 = driver->getTexture("../media/Imagenes/Debug/DT/granja_no_selected.png");
				}
				if(caminoNodos.at(i) == 52)
				{
					node_52 = driver->getTexture("../media/Imagenes/Debug/DT/nada_no_selected.png");
				}
				if(caminoNodos.at(i) == 53)
				{
					node_53 = driver->getTexture("../media/Imagenes/Debug/DT/rec_granja_no_selected.png");	
				}
				if(caminoNodos.at(i) == 54)
				{
					node_54 = driver->getTexture("../media/Imagenes/Debug/DT/crear_granja_no_selected.png");
				}
				if(caminoNodos.at(i) == 55)
				{
					node_55 = driver->getTexture("../media/Imagenes/Debug/DT/nada_no_selected.png");
				}
			}
			
			//Pinta
			driver->draw2DImage(node_41, core::position2d<s32>(dimensionPantallaX + 250,10),
				core::rect<s32>(0,0,75 ,75), 0, video::SColor(255,255,255,255), true);
				
			driver->draw2DImage(node_42, core::position2d<s32>(dimensionPantallaX + 200,110),
				core::rect<s32>(0,0,75 ,75), 0, video::SColor(255,255,255,255), true);
				
			driver->draw2DImage(node_43, core::position2d<s32>(dimensionPantallaX + 140,210),
				core::rect<s32>(0,0,75 ,75), 0, video::SColor(255,255,255,255), true);
				
			driver->draw2DImage(node_44, core::position2d<s32>(dimensionPantallaX + 90,310),
				core::rect<s32>(0,0,75 ,75), 0, video::SColor(255,255,255,255), true);
				
			driver->draw2DImage(node_45, core::position2d<s32>(dimensionPantallaX + 180,310),
				core::rect<s32>(0,0,75 ,75), 0, video::SColor(255,255,255,255), true);
				
			driver->draw2DImage(node_46, core::position2d<s32>(dimensionPantallaX + 270,210),
				core::rect<s32>(0,0,75 ,75), 0, video::SColor(255,255,255,255), true);
				
			driver->draw2DImage(node_47, core::position2d<s32>(dimensionPantallaX + 230,310),
				core::rect<s32>(0,0,75 ,75), 0, video::SColor(255,255,255,255), true);
				
			driver->draw2DImage(node_48, core::position2d<s32>(dimensionPantallaX + 310,310),
				core::rect<s32>(0,0,75 ,75), 0, video::SColor(255,255,255,255), true);
				
			driver->draw2DImage(node_49, core::position2d<s32>(dimensionPantallaX + 360,110),
				core::rect<s32>(0,0,75 ,75), 0, video::SColor(255,255,255,255), true);
				
			driver->draw2DImage(node_50, core::position2d<s32>(dimensionPantallaX + 310,210),
				core::rect<s32>(0,0,75 ,75), 0, video::SColor(255,255,255,255), true);
				
			driver->draw2DImage(node_51, core::position2d<s32>(dimensionPantallaX + 400,210),
				core::rect<s32>(0,0,75 ,75), 0, video::SColor(255,255,255,255), true);
				
			driver->draw2DImage(node_52, core::position2d<s32>(dimensionPantallaX + 360,310),
				core::rect<s32>(0,0,75 ,75), 0, video::SColor(255,255,255,255), true);
				
			driver->draw2DImage(node_53, core::position2d<s32>(dimensionPantallaX + 430,310),
				core::rect<s32>(0,0,75 ,75), 0, video::SColor(255,255,255,255), true);
				
			driver->draw2DImage(node_54, core::position2d<s32>(dimensionPantallaX + 400,410),
				core::rect<s32>(0,0,75 ,75), 0, video::SColor(255,255,255,255), true);	
				
			driver->draw2DImage(node_55, core::position2d<s32>(dimensionPantallaX + 460,410),
				core::rect<s32>(0,0,75 ,75), 0, video::SColor(255,255,255,255), true);
			break;
	}
}

bool DebugMaster::OnEvent(const SEvent& event)
{
	return false;
}
