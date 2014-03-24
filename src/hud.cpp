		#include "hud.h"

hud::hud(IrrlichtDevice * IrrDevice,shared_ptr<mapa2D> _m):_mapa2D(_m){

	MenuDevice = IrrDevice;
	env = IrrDevice->getGUIEnvironment();
	env->clear();
		//Get the Scene Manager from the MenuDevice.
	smgr = IrrDevice->getSceneManager();
		//Get the Video Driver from the MenuDevice.
	driver = IrrDevice->getVideoDriver();

	font = env->getFont("../media/fonthaettenschweiler.bmp");
	skin = env->getSkin();
	if (font)
		skin->setFont(font);
	dimensionHUD1.X=600;
	dimensionHUD1.Y=400;
	dimensionHUD2.X=800;
	dimensionHUD2.Y=600;
	P1X=0;
	P1Y=403;
	P2X=800;
	P2Y=600;
	personajes= NULL;
	ensenyarInformacion=false;
	mapa="";

	hud_sprite = driver->getTexture("../media/Texturas/hud/HUD.png");
	hud_buttons = driver->getTexture("../media/Texturas/hud/botones.png");
	button_selected = -1;

}

bool hud::OnEvent(const SEvent& event)
{
	printf("Estas clickando en el hud \n" );
	return true;
}
void hud::paintInformation(vector<Unidades*>* pers){

	if(pers!=NULL)
		personajes=pers;
	cout << "Pinto hud" << endl;
	if(personajes!=NULL)
	{
		cout << "Algo en personajes, hay" << endl;
		if(personajes->size()>=1){
			cout << "Hay personajes, mostrar en hud a true" << endl;
			ensenyarInformacion=true;
		}
		else{
			ensenyarInformacion=false;
		}
	 }

}
//Suelo==0, Montaña=1, Bosque=2, CC=3, ALDEANO=4
void hud::pintarMiniMapa(){
	int x=595;
	int y=395;
	int xhud=0;
	int yhud=0;
	position2di dimPantalla=_mapa2D->GetCameraScroll();
	IDibujable *dib;
	for(int i=0;i<WIDTH;i++){
		for(int j=0;j<HEIGHT;j++){
			dib= _mapa2D->getTile(i,j);
			if(dib->getTipo()==0){

				driver->drawPixel(x+i,y+j,video::SColor(255,222,184,135));
			}
			else if(dib->getTipo()==1){

				driver->drawPixel(x+i,y+j,video::SColor(255,0,100,0));
			}
		}
	}
	vector<battleIA*>* idub= (vector<battleIA*>*)_mapa2D->getIa_units();

	for(unsigned int i=0;i<idub->size();i++){
		xhud=idub->at(i)->getPosition().X;
		yhud=idub->at(i)->getPosition().Y;
		if(ensenyarInformacion==true){
			if(idub->at(i)->getSelect()==true){
				driver->draw2DRectangle(video::SColor(255,255,255,0),core::rect<s32>(x+xhud,y+yhud,x+xhud+4 ,y+yhud+4),0);
			}
			else{
				driver->draw2DRectangle(video::SColor(255,0,0,255),core::rect<s32>(x+xhud,y+yhud,x+xhud+4 ,y+yhud+4),0);
			}
		}
		else{
				driver->draw2DRectangle(video::SColor(255,0,0,255),core::rect<s32>(x+xhud,y+yhud,x+xhud+4 ,y+yhud+4),0);
		}
		
	}
	vector<Unidades*>* udub= (vector<Unidades*>*)_mapa2D->getUser_units();
	for(unsigned int i=0;i<udub->size();i++){
		xhud=udub->at(i)->getPosition().X;
		yhud=udub->at(i)->getPosition().Y;
		if(ensenyarInformacion==true){
			if(udub->at(i)->getSelect()==true){
				driver->draw2DRectangle(video::SColor(255,0,255,0),core::rect<s32>(x+xhud,y+yhud,x+xhud+4 ,y+yhud+4),0);
			}
			else{
				driver->draw2DRectangle(video::SColor(255,255,0,0),core::rect<s32>(x+xhud,y+yhud,x+xhud+4 ,y+yhud+4),0);
			}
		}
		else{
			driver->draw2DRectangle(video::SColor(255,255,0,0),core::rect<s32>(x+xhud,y+yhud,x+xhud+4 ,y+yhud+4),0);
		}
	}

	vector<IDibujable*>* bdub=_mapa2D->getBuildings();
	for(unsigned int i=0;i<bdub->size();i++){
		xhud=bdub->at(i)->getPosition().X;
		yhud=bdub->at(i)->getPosition().Y;
		driver->draw2DRectangle(video::SColor(255,0,0,0),core::rect<s32>(x+xhud,y+yhud,x+xhud+8 ,y+yhud+8),0);
	}

	driver->draw2DRectangleOutline(core::rect<s32>(x+dimPantalla.X,y+dimPantalla.Y,x+dimPantalla.X+26,y+dimPantalla.Y+20),video::SColor(255,0,0,0));
}
void hud::paint(){

	if (MenuDevice->run())
	{        
		if(driver)
		{
			
			/*driver->draw2DRectangle(video::SColor(100,154,147,129),core::rect<s32>(0,400,800 ,600),0);
			driver->draw2DRectangle(video::SColor(255,154,147,129),core::rect<s32>(600,400,800 ,600),0);*/
			driver->draw2DImage(hud_sprite, position2di(0,392), rect<s32>(0, 0, hud_sprite->getSize().Width, hud_sprite->getSize().Height), 0, SColor((u32)((1.0f - 0.0f) * 255), 255, 255, 255), true);
			
			//Botones edificios HUD

			if(button_selected == 1)
				driver->draw2DImage(hud_buttons, position2di(396,468), rect<s32>(60, 0, 120, 55), 0, SColor((u32)((1.0f - 0.0f) * 255), 255, 255, 255), true);
			else
				driver->draw2DImage(hud_buttons, position2di(396,468), rect<s32>(0, 0, 60, 55), 0, SColor((u32)((1.0f - 0.0f) * 255), 255, 255, 255), true);

			if(button_selected == 2)
				driver->draw2DImage(hud_buttons, position2di(458,468), rect<s32>(180, 0, 240, 55), 0, SColor((u32)((1.0f - 0.0f) * 255), 255, 255, 255), true);
			else
				driver->draw2DImage(hud_buttons, position2di(458,468), rect<s32>(120, 0, 180, 55), 0, SColor((u32)((1.0f - 0.0f) * 255), 255, 255, 255), true);
			
			if(button_selected == 3)
				driver->draw2DImage(hud_buttons, position2di(521,468), rect<s32>(300, 0, 360, 55), 0, SColor((u32)((1.0f - 0.0f) * 255), 255, 255, 255), true);
			else
				driver->draw2DImage(hud_buttons, position2di(521,468), rect<s32>(240, 0, 300, 55), 0, SColor((u32)((1.0f - 0.0f) * 255), 255, 255, 255), true);
			
			if(button_selected == 4)
				driver->draw2DImage(hud_buttons, position2di(396,524), rect<s32>(420, 0, 480, 55), 0, SColor((u32)((1.0f - 0.0f) * 255), 255, 255, 255), true);
			else
				driver->draw2DImage(hud_buttons, position2di(396,524), rect<s32>(360, 0, 420, 55), 0, SColor((u32)((1.0f - 0.0f) * 255), 255, 255, 255), true);

			font->draw(L"Información del personaje:",
				core::rect<s32>(25,425,25,425),
				video::SColor(255,255,255,255));

			pintarMiniMapa();

			if(ensenyarInformacion==true){
				vector<battleIA*>* idub= (vector<battleIA*>*)_mapa2D->getIa_units();
				vector<Unidades*>* udub= (vector<Unidades*>*)_mapa2D->getUser_units();
				int numper = 0;
				
				for(int i=0; i<idub->size(); i++)
				{
					if(idub->at(i)->getSelect())
					{
						cout << "PONER IA " << i << " EN HUD" << endl;
						dibujaEnHUD(numper,idub->at(i));
						numper++;
					}
				}
				for(int i=0; i<udub->size(); i++)
				{
					if(udub->at(i)->getSelect())
					{
						cout << "PONER BICHO "<< i << " EN HUD" << endl;
						dibujaEnHUD(numper,udub->at(i));
						numper++;
					}
				}
			}
		}
	}

}

void hud::dibujaEnHUD(int numper,Unidades* posuni)
{
	/*core::stringw posx="";
	posx+=posuni->getPosition().X;
	core::stringw posy="";
	posy+= posuni->getPosition().Y;
					
	font->draw(posx,
	core::rect<s32>(200,470+(15*numper),200,470+(15*numper)),
	video::SColor(255,0,0,0));
						
	font->draw(posy,
	core::rect<s32>(300,470+(15*numper),300,470+(15*numper)),
	video::SColor(255,0,0,0));*/



	core::stringw Tipo = "Tipo: ";
	switch(posuni->getType())
	{
		case 0: Tipo += "Aldeano"; break;
		case 1: Tipo += "Arquero"; break;
		case 2: Tipo += "Espadachin"; break;
		case 3: Tipo += "Lancero"; break;
	}

	core::stringw Vida="Vida: ";
	Vida+=posuni->getLife();
	core::stringw Ataque="Ataque: ";
	Ataque+= posuni->getAttackValue();

	font->draw(Tipo,
		core::rect<s32>(25,445+(15*numper),25,445+(15*numper)),
		video::SColor(255,255,255,255));
	font->draw(Vida,
		core::rect<s32>(125,445+(15*numper),25,445+(15*numper)),
		video::SColor(255,255,255,255));
	font->draw(Ataque,
		core::rect<s32>(225,445+(15*numper),25,445+(15*numper)),
		video::SColor(255,255,255,255));
}

hud::~hud()
{
		//delete MenuDevice;
	/*delete driver;
	delete smgr;
	delete env;
	delete skin;
	delete font;*/
}

void hud::selectButton(int b)
{
	button_selected = b;
}

