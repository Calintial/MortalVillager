#include "pantalla.h"
// #include <string>
// #include <iostream>
// #include <vector>
// #include <cstdlib>
// #include <string>

// using namespace irr;
// using namespace video;
// using namespace std;
// using namespace core;

Pantalla::Pantalla(IrrlichtDevice * IrrDevice){
	pantallaDevice= IrrDevice;
	pantallaDevice->setEventReceiver(this);
}


