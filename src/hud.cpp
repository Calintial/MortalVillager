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
    driver->draw2DRectangle(video::SColor(255,154,147,129),core::rect<s32>(0,400,800 ,600),0);
	repaint(IrrDevice);
    env->drawAll();
    driver->endScene();

}
bool hud::OnEvent(const SEvent& event)
{
	printf("Estas clickando en el hud \n" );
	return true;
}
void hud::repaint(IrrlichtDevice * IrrDevice/*personaje que se ha clicado si se ha clicado*/){



    font->draw(L"Información del personaje:",
                    core::rect<s32>(200,450,200,450),
                    video::SColor(255,0,0,0));
    //env->drawAll();

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
