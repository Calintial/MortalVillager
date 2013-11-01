// Facade pattern to separate graphic engine from the rest of the game
#include "graphicEngine.h"

graphicEngine::graphicEngine(){
    dimensionPantallaX=800;
    dimensionPantallaY=600;

	//Create an Irrlicht Device.
    device = createDevice(EDT_OPENGL,dimension2d<u32>(dimensionPantallaX,dimensionPantallaY));

    env = device->getGUIEnvironment();
    device->setWindowCaption(L"Demo de Mortal Village");
    device->setResizable(true);

    //Get the Scene Manager from the device.
    smgr = device->getSceneManager();

    //Get the Video Driver from the device.
    driver = device->getVideoDriver();

    video::IVideoDriver* driver = device->getVideoDriver();
    env = device->getGUIEnvironment();
    pintarMenu();
   
    //pintar un cubo
    /*
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
*/}
void graphicEngine::pintarCubo(){

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
void graphicEngine::pintarMenu(){
    skin = env->getSkin();
    font = env->getFont("../media/fonthaettenschweiler.bmp");
    if (font)
        skin->setFont(font);

    skin->setFont(env->getBuiltInFont(), EGDF_TOOLTIP);
        
    env->addButton(rect<s32>((dimensionPantallaX/2-100),dimensionPantallaY/2,(dimensionPantallaX/2+100),dimensionPantallaY/2 + 32), 0, GUI_BOTON_JUGAR,
        L"Jugar", L"Empezar partida");
    env->addButton(rect<s32>((dimensionPantallaX/2-100),dimensionPantallaY/2+40,(dimensionPantallaX/2+100),dimensionPantallaY/2 + 72), 0,GUI_BOTON_OPCIONES,
        L"Opciones", L"Opciones de juego");       
    env->addButton(rect<s32>((dimensionPantallaX/2-100),dimensionPantallaY/2+80,(dimensionPantallaX/2+100),dimensionPantallaY/2 + 112), 0, GUI_BOTON_CREDITOS,
        L"Creditos", L"Información del juego"); 
     env->addButton(rect<s32>((dimensionPantallaX/2-100),dimensionPantallaY/2+120,(dimensionPantallaX/2+100),dimensionPantallaY/2 + 152), 0, GUI_BOTON_SALIR,
        L"Salir", L"Salir del juego"); 
    /*SAppContext context;
    context.device = device;
    // Then create the event receiver, giving it that context structure.
    MyEventReceiver receiver(context);
    // And tell the device to use our custom event receiver.

    device->setEventReceiver(&receiver);
    */
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
       // smgr->drawAll();
        
        env->drawAll();
        //End the scene
        driver->endScene();

        //Logic to update the scene will go here.
        return true;
    }else{
    	return false;
    }
}