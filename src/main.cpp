#include "graphicEngine.h"
#include "intelEngine.h"
#include <iostream>

using namespace std;

void menuPrincipal(){
    bool salir = false;
    while(!salir){
        // mostrar el menu, y gestionar lo que tenga que hacer
        salir = true;
    }
}

void actualizar_movimientos(){
    // Actualizo movimientos en el mapa, o algo
}

void gestionar_entrada_usuario(){
    // gestionar qué hace el usuario, etc
}

int main(int argc, char** argv)
{ 

    bool pausa = false;
    graphicEngine graphics;
    graphics.pintarMenu();
    intelEngine intel;
    //Run simulation
    while(graphics.updateOnce()){
        while(pausa){
            // mostrar el menú de pausa
            // congelar todo el juego
            // gestionar las cosas que se deban hacer mientras el juego está pausado
        }

        // dependiendo de cómo vaya de rápido, igual tendremos que poner esto en hilos, o algo así
        gestionar_entrada_usuario();
        intel.doSomething();
        // hasta aquí la posibilidad de hilos

        actualizar_movimientos();
    }
    cout<<"salida"<<endl;
    return 0;
}


































/*                          HERE BE DRAGONS


                                                 /===-_---~~~~~~~~~------____
                                                |===-~___                _,-'
                 -==\\                         `//~\\   ~~~~`---.___.-~~
             ______-==|                         | |  \\           _-~`
       __--~~~  ,-/-==\\                        | |   `\        ,'
    _-~       /'    |  \\                      / /      \      /
  .'        /       |   \\                   /' /        \   /'
 /  ____  /         |    \`\.__/-~~ ~ \ _ _/'  /          \/'
/-'~    ~~~~~---__  |     ~-/~         ( )   /'        _--~`
                  \_|      /        _)   ;  ),   __--~~
                    '~~--_/      _-~/-  / \   '-~ \
                   {\__--_/}    / \\_>- )<__\      \
                   /'   (_/  _-~  | |__>--<__|      | 
                  |0  0 _/) )-~     | |__>--<__|      |
                  / /~ ,_/       / /__>---<__/      |  
                 o o _//        /-~_>---<__-~      /
                 (^(~          /~_>---<__-      _-~              
                ,/|           /__>--<__/     _-~                 
             ,//('(          |__>--<__|     /                  .----_ 
            ( ( '))          |__>--<__|    |                 /' _---_~\
         `-)) )) (           |__>--<__|    |               /'  /     ~\`\
        ,/,'//( (             \__>--<__\    \            /'  //        ||
      ,( ( ((, ))              ~-__>--<_~-_  ~--____---~' _/'/        /'
    `~/  )` ) ,/|                 ~-_~>--<_/-__       __-~ _/ 
  ._-~//( )/ )) `                    ~~-'_/_/ /~~~~~~~__--~ 
   ;'( ')/ ,)(                              ~~~~~~~~~~ 
  ' ') '( (/
    '   '  `   
*/