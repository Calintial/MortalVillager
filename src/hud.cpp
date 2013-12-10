		#include "hud.h"

hud::hud(IrrlichtDevice * IrrDevice,mapa2D * _m){

	MenuDevice = IrrDevice;
	env = IrrDevice->getGUIEnvironment();
	env->clear();
		//Get the Scene Manager from the MenuDevice.
	smgr = IrrDevice->getSceneManager();
		//Get the Video Driver from the MenuDevice.
	driver = IrrDevice->getVideoDriver();

	video::IVideoDriver* driver = IrrDevice->getVideoDriver();
	font = env->getFont("../media/fonthaettenschweiler.bmp");
	skin = env->getSkin();
	if (font)
		skin->setFont(font);
	P1X=0;
	P1Y=403;
	P2X=800;
	P2Y=600;
	personaje= new Unidades();
	personaje=NULL;
	ensenyarInformacion=false;
	mapa="";
	_mapa2D=_m;

}

bool hud::OnEvent(const SEvent& event)
{
	printf("Estas clickando en el hud \n" );
	return true;
}
void hud::paintInformation(Unidades * pers){

	personaje=pers;
	if(personaje!=NULL){
		ensenyarInformacion=true;
	}
	else{
		ensenyarInformacion=false;
	}

}
//Suelo==0, Montaña=1, Bosque=2, CC=3, ALDEANO=4
void hud::pintarMiniMapa(){
	for(int i=0;i<WIDTH;i++){
		for(int j=0;j<HEIGHT;j++){
			driver->draw2DRectangle(video::SColor(255,0,0,255),core::rect<s32>(600,400,604 ,404),0);
		}
	}
}
void hud::paint(){

	if (MenuDevice->run())
	{        
		if(MenuDevice->isWindowActive() && driver)
		{
			
			driver->draw2DRectangle(video::SColor(100,154,147,129),core::rect<s32>(0,400,800 ,600),0);
			driver->draw2DRectangle(video::SColor(255,154,147,129),core::rect<s32>(600,400,800 ,600),0);
			font->draw(L"Información del personaje:",
				core::rect<s32>(200,450,200,450),
				video::SColor(255,0,0,0));
			pintarMiniMapa();
			if(ensenyarInformacion==true){
				core::stringw posx="";
				posx+=personaje->getPosition().X;
				core::stringw posy="";
				posy+= personaje->getPosition().Y;
				font->draw(posx,
					core::rect<s32>(200,550,200,550),
					video::SColor(255,0,0,0));
				font->draw(posy,
					core::rect<s32>(300,550,300,550),
					video::SColor(255,0,0,0));
			
			}
		}
	}

}
hud::~hud()
{
		//delete MenuDevice;
	delete driver;
	delete smgr;
	delete env;
	delete skin;
	delete font;
}