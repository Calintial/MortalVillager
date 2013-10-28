// Facade pattern to separate graphic engine from the rest of the game
#include "graphicEngine.h"

graphicEngine::graphicEngine(){
	//Create an Irrlicht Device.
    device = createDevice(EDT_OPENGL,dimension2d<u32>(800,600));

    //Get the Scene Manager from the device.
    smgr = device->getSceneManager();

    //Get the Video Driver from the device.
    driver = device->getVideoDriver();

    //Add a Cube to the Scene.
    node = smgr->addCubeSceneNode();

    //Needed to make the object's texture visible without a light source.
    node->setMaterialFlag(EMF_LIGHTING, false);

    //Add texture to the cube.
    node->setMaterialTexture(0,driver->getTexture("/usr/share/irrlicht/media/wall.jpg"));

    //Set cube 100 units further in forward direction (Z axis).
    node->setPosition(vector3df(0,0,100));

    //Add FPS Camera to allow movement using Keyboard and Mouse.
    smgr->addCameraSceneNodeFPS();
}

/*
	Actualiza una vez la pantalla. 
	Devuelve si el device esta listo
*/
bool graphicEngine::updateOnce(){
	if(device->run()){
		//Begin Scene with a gray backdrop #rgb(125,125,125)
        driver->beginScene(true,true,SColor(0,125,125,125));

        //Render the scene at this instant.
        smgr->drawAll();

        //End the scene
        driver->endScene();

        //Logic to update the scene will go here.
        return true;
    }else{
    	return false;
    }
}