#include "gameScreen.h"


gameScreen::gameScreen(){
	dimensionPantallaX=800;
    dimensionPantallaY=600;

	//Create an Irrlicht Device.
    GameDevice = createDevice(EDT_OPENGL,dimension2d<u32>(dimensionPantallaX,dimensionPantallaY),16,true,false,false,0);

    env = GameDevice->getGUIEnvironment();
    GameDevice->setWindowCaption(L"Demo de Mortal Villager");
    GameDevice->setResizable(true);

    //Get the Scene Manager from the GameDevice.
    smgr = GameDevice->getSceneManager();

    //Get the Video Driver from the GameDevice.
    driver = GameDevice->getVideoDriver();

    video::IVideoDriver* driver = GameDevice->getVideoDriver();
    env = GameDevice->getGUIEnvironment();
    //Add a Cube to the Scene.
    node = smgr->addCubeSceneNode();

    //Needed to make the object's texture visible without a light source.
    node->setMaterialFlag(EMF_LIGHTING, false);

    //Add texture to the cube.
    node->setMaterialTexture(0,driver->getTexture("/usr/share/irrlicht/media/wall.jpg"));

    //Set cube 100 units further in forward direction (Z axis).
    node->setPosition(vector3df(0,0,100));

    //Add FPS Camera to allow movement using Keyboard and Mouse.
    //smgr->addCameraSceneNodeFPS();

    GameDevice->setEventReceiver(this); 
}

gameScreen::~gameScreen(){
	delete GameDevice;
	delete driver;
	delete smgr;
	delete env;
	delete skin;
	delete font;
}


bool gameScreen::OnEvent(const SEvent& event)
{
    if (event.GUIEvent.EventType == EGET_BUTTON_CLICKED)
    {
        std::cout<<"closeDevice"<<std::endl;
        GameDevice->closeDevice();
    }
	// eventos para el juego
	return false;
}


bool gameScreen::run(){
    
    while(GameDevice->run() && driver)
    {
        if (GameDevice->isWindowActive())
        {
            //Begin Scene with a gray backdrop #rgb(125,125,125)
	        driver->beginScene(true,true,SColor(0,125,125,125));

	        //Render the scene at this instant.
	        smgr->drawAll();
	        
	        //env->drawAll();
	        //End the scene
	        driver->endScene();

	        //Logic to update the scene will go here.
        }
    }

    GameDevice->drop();
    return true;
}