		#include "hud.h"

hud::hud(IrrlichtDevice * IrrDevice){

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

}

bool hud::OnEvent(const SEvent& event)
{
	printf("Estas clickando en el hud \n" );
	return true;
}
void hud::paintInformation(Unidades * pers,bool ensenyar){
	personaje=pers;
	ensenyarInformacion=ensenyar;
}
void hud::paint(){

	if (MenuDevice->run())
	{        
		if(MenuDevice->isWindowActive() && driver)
		{
			
			driver->draw2DRectangle(video::SColor(100,154,147,129),core::rect<s32>(0,403,800 ,600),0);
			font->draw(L"Información del personaje:",
				core::rect<s32>(200,450,200,450),
				video::SColor(255,0,0,0));
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
