#ifndef PANTALLA_BASICA_H
#define PANTALLA_BASICA_H

#include "pantalla.h"
#include "hud.h"
#include "mapa2D.h"

/*class mapa2D;
class hud;*/
class PantallaBasica : public Pantalla
{
public:
		PantallaBasica(IrrlichtDevice * IrrDevice,graphicEngine * _grEngine,shared_ptr<mapa2D> _mapa, int tipo);
		~PantallaBasica();
		void pintarPantalla(vector<IDibujable*>*,vector<IDibujable*>*,vector<IDibujable*>*);
		virtual bool OnEvent(const SEvent& event);
private:
	hud* hudmapa;


};
#endif 
