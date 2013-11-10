#include "graphicEngine.h"

graphicEngine::graphicEngine()
{
    menu = new mainMenu();
}

graphicEngine::~graphicEngine()
{
    delete menu;
}

//Funcion encargada de pintar el menu principal
int graphicEngine::DrawMainMenu()
{
    int status = menu->run();
}