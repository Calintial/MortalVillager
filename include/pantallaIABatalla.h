#ifndef PANTALLA_IABATALLA_H
#define PANTALLA_IABATALLA_H

#include <string>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <string>
#include <irrlicht.h>
#include "pantalla.h"
#include "mapa2D.h"
#include "DebugMenu.h"

using namespace irr;
using namespace video;
using namespace std;
using namespace core;

class mapa2D;
class PantallaIABatalla : public Pantalla
{
public:
		PantallaIABatalla(IrrlichtDevice * IrrDevice,graphicEngine * _grEngine);
		~PantallaIABatalla();
		void pintarPantalla(vector<IDibujable*>*,vector<IDibujable*>*);
private:
	IrrlichtDevice * pantallaDevice;
	mapa2D * mapa;
	DebugMenu* debug;
};
#endif 