#include "graphicEngine.h"

graphicEngine::graphicEngine()
{
    menu = new mainMenu();
    mapa = new mapa2D();
}

graphicEngine::~graphicEngine()
{
    delete menu;
    delete mapa;
}

//Funcion encargada de pintar el menu principal
int graphicEngine::DrawMainMenu()
{
    int status = menu->run();
}

int graphicEngine::DrawMap()
{
	
}
