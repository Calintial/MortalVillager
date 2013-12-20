#ifndef PANTALLA_H
#define PANTALLA_H

#include <string>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <string>
#include <irrlicht.h>
#include "mapa2D.h"
#include "DebugMenu.h"

using namespace irr;
using namespace video;
using namespace std;
using namespace core;

class mapa2D;
class Pantalla : public IEventReceiver
{
public:
		Pantalla(IrrlichtDevice * IrrDevice);
		~Pantalla();
		void pintarPantalla(vector<IDibujable*>*,vector<IDibujable*>*);
private:
	IrrlichtDevice * pantallaDevice;
	mapa2D * mapa;
	DebugMenu* debug;
};
#endif 