#ifndef PANTALLA_H
#define PANTALLA_H

#include <irrlicht.h>
#include <string>
#include <vector>
#include <iostream>
#include <memory>
#include "mapa2D.h"
#include "IDibujable.h"

class graphicEngine;
class Pantalla : public IEventReceiver
{
public:

		Pantalla(IrrlichtDevice * IrrDevice,graphicEngine * _grEngine,shared_ptr<mapa2D> _mapa);
		virtual ~Pantalla() {};
		virtual void pintarPantalla(vector<IDibujable*>*,vector<IDibujable*>*,vector<IDibujable*>*) = 0;

		virtual bool OnEvent(const SEvent& event);
		void dispose();
private:
	graphicEngine * grEngine;
protected:
	IrrlichtDevice * pantallaDevice;
	shared_ptr<mapa2D> mapa;
	bool eliminar;



};
#endif 