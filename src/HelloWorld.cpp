#include <irrlicht.h>
#include <iostream>

using namespace std;
using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;

int main(int argc, char** argv)
{
    //Create an Irrlicht Device.
    IrrlichtDevice * device = createDevice(EDT_OPENGL,dimension2d<u32>(800,600));

    //Get the Scene Manager from the device.
    ISceneManager * smgr = device->getSceneManager();

    //Get the Video Driver from the device.
    IVideoDriver * driver = device->getVideoDriver();

    //Add a Cube to the Scene.
    ISceneNode * node = smgr->addCubeSceneNode();

    //Needed to make the object's texture visible without a light source.
    node->setMaterialFlag(EMF_LIGHTING, false);

    //Add texture to the cube.
    node->setMaterialTexture(0,driver->getTexture("/usr/share/irrlicht/media/wall.jpg"));

    //Set cube 100 units further in forward direction (Z axis).
    node->setPosition(vector3df(0,0,100));

    //Add FPS Camera to allow movement using Keyboard and Mouse.
    smgr->addCameraSceneNodeFPS();

    //Run simulation
    while(device->run())
    {
        //Begin Scene with a gray backdrop #rgb(125,125,125)
        driver->beginScene(true,true,SColor(0,125,125,125));

        //Render the scene at this instant.
        smgr->drawAll();

        //End the scene
        driver->endScene();

        //Logic to update the scene will go here.
    }
    return 0;
}
