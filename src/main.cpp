#include "graphicEngine.h"
#include <iostream>

using namespace std;


int main(int argc, char** argv)
{
    graphicEngine graphics;
    //Run simulation
    while(graphics.updateOnce()){
        cout<<"bucle"<<endl;
    }
    cout<<"salida"<<endl;
    return 0;
}
