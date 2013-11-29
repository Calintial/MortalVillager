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


}
bool hud::OnEvent(const SEvent& event)
{
	printf("Estas clickando en el hud \n" );
	return true;
}
void hud::paintInformation(){

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
