#ifndef PANTALLA_H
#define PANTALLA_H

#include "mapa2D.h"

class mapa2D;
class Pantalla : public IEventReceiver
{
public:
		Pantalla(IrrlichtDevice * IrrDevice);
		~Pantalla();
		int pintarPantalla(vector<IDibujable*>*,vector<IDibujable*>*);
		virtual bool OnEvent(const SEvent& event);
private:
	IrrlichtDevice * pantallaDevice;
	mapa2D * mapa;


};
#endif 