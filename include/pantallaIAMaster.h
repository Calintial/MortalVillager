#ifndef PANTALLA_IAMASTER_H
#define PANTALLA_IAMASTER_H

#include <string>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <string>
#include <irrlicht.h>
#include "pantalla.h"
#include "mapa2D.h"
#include "hud.h"
#include "DebugMaster.h"

using namespace irr;
using namespace video;
using namespace std;
using namespace core;

class mapa2D;
class PantallaIAMaster : public Pantalla
{
public:

		PantallaIAMaster(IrrlichtDevice * IrrDevice,graphicEngine * _grEngine,shared_ptr<mapa2D> _mapa, int tipo);
		~PantallaIAMaster();
		void pintarPantalla(vector<shared_ptr<IDibujable>>*,vector<shared_ptr<IDibujable>>*,vector<shared_ptr<IDibujable>>*);
		virtual bool OnEvent(const SEvent& event);
private:
	DebugMaster* debug;
	hud* hudmapa;
};
#endif 
