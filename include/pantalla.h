#ifndef PANTALLA_H
#define PANTALLA_H

#include <irrlicht.h>
#include <string>
#include <vector>
#include <iostream>
#include "IDibujable.h"
#include "gameEngine.h"


class Pantalla : public IEventReceiver
{
public:
		Pantalla(IrrlichtDevice * IrrDevice);
		virtual ~Pantalla() {};
		virtual void pintarPantalla(vector<IDibujable*>*,vector<IDibujable*>*) = 0;
		virtual bool OnEvent(const SEvent& event);
private:
	IrrlichtDevice * pantallaDevice;


};
#endif 