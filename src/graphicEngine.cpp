// Facade pattern to separate graphic engine from the rest of the game
#include "graphicEngine.h"

graphicEngine::graphicEngine(){
    game = NULL;
}

graphicEngine::~graphicEngine(){
    delete game;
}

bool graphicEngine::pintarMenu(){
    bool menuSalida = menu.run();
    std::cout<<"menu devuelve "<<menuSalida<<std::endl;
    return menuSalida;
}
/*
	Actualiza una vez la pantalla. 
	Devuelve si el device esta listo
*/
bool graphicEngine::updateOnce(){
    if(game == NULL){
        std::cout<<"creando gameScreen"<<std::endl;
        game = new gameScreen();
    }
    std::cout<<"Aquí debería mostrar la pantalla de juego"<<std::endl;
    game->run();
    return true;
}