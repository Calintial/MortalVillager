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

	/*Botón para añadir edificios*/
	env->addButton(rect<s32>(200,500,300,550), 0, BUTTON_ADD_BUILDING,
			 L"Añadir Edificio", L"Añadir un edificio");

	/*Desplegables para seleccionar unidad a insertar*/
	IGUIComboBox* combo_edificios = env->addComboBox (rect<s32>(350,500,450,550), 0,COMBO_EDIFICIOS);
	combo_edificios->addItem(L"Centro ciudad");
	combo_edificios->addItem(L"Granja");
	combo_edificios->addItem(L"Cuartel");
	combo_edificios->addItem(L"Arqueria");
	combo_edificios->addItem(L"Lanceria");
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
		/*if(personajes->size()>1){
			cout << "Hay personajes, mostrar en hud a true" << endl;
			ensenyarInformacion=true;
		}
		else{
			ensenyarInformacion=false;
		}*/
	 }

}
//Suelo==0, Montaña=1, Bosque=2, CC=3, ALDEANO=4
void hud::pintarMiniMapa(){
	int x=600;
	int y=400;
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
	vector<IDibujable*>* idub= _mapa2D->getIa_units();

	for(unsigned int i=0;i<idub->size();i++){
		xhud=idub->at(i)->getPosition().X;
		yhud=idub->at(i)->getPosition().Y;
		if(ensenyarInformacion==true){
			if(xhud==personajes->at(i)->getPosition().X && yhud==personajes->at(i)->getPosition().Y){
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
	idub=_mapa2D->getUser_units();
	for(unsigned int i=0;i<idub->size();i++){
		xhud=idub->at(i)->getPosition().X;
		yhud=idub->at(i)->getPosition().Y;
		if(ensenyarInformacion==true){
			if(xhud==personajes->at(i)->getPosition().X && yhud==personajes->at(i)->getPosition().Y){
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

	driver->draw2DRectangleOutline(core::rect<s32>(x+dimPantalla.X,y+dimPantalla.Y,x+dimPantalla.X+26,y+dimPantalla.Y+20),video::SColor(255,0,0,0));
}
void hud::paint(){

	if (MenuDevice->run())
	{        
		if(driver)
		{
			
			driver->draw2DRectangle(video::SColor(100,154,147,129),core::rect<s32>(0,400,800 ,600),0);
			driver->draw2DRectangle(video::SColor(255,154,147,129),core::rect<s32>(600,400,800 ,600),0);
			font->draw(L"Información del personaje:",
				core::rect<s32>(200,450,200,450),
				video::SColor(255,0,0,0));

			pintarMiniMapa();
			if(ensenyarInformacion==true){
				for(int i=0; i<personajes->size(); i++)
				{
					core::stringw posx="";
					posx+=personajes->at(i)->getPosition().X;
					core::stringw posy="";
					posy+= personajes->at(i)->getPosition().Y;
				
					font->draw(posx,
					core::rect<s32>(200,550+(50*i),200,550+(50*i)),
					video::SColor(255,0,0,0));
					
					font->draw(posy,
					core::rect<s32>(300,550+(50*i),300,550+(50*i)),
					video::SColor(255,0,0,0));
				}
				
			}
		}
	}

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
