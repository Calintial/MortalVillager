#ifndef PANTALLA_H
#define PANTALLA_H

#include <irrlicht.h>
#include <string>
#include <vector>
#include <iostream>
#include <memory>
#include "mapa2D.h"
#include "IDibujable.h"

#define dpos 4

class graphicEngine;
class Pantalla : public IEventReceiver
{
public:

		Pantalla(IrrlichtDevice * IrrDevice,graphicEngine * _grEngine,shared_ptr<mapa2D> _mapa);
		virtual ~Pantalla() {};
		virtual void pintarPantalla(vector<shared_ptr<IDibujable>>*,vector<shared_ptr<IDibujable>>*,vector<shared_ptr<IDibujable>>*) = 0;

		virtual bool OnEvent(const SEvent& event);
		void dispose();
		bool pscroll [dpos];
		int getTipo() { return tipo;}
		void setTipo(int t){cout << "TIPONUEVO:" << t << endl; tipo=t;}
private:
	graphicEngine * grEngine;
	int tipo;
protected:
	IrrlichtDevice * pantallaDevice;
	shared_ptr<mapa2D> mapa;
	bool eliminar;



};
#endif 
