#ifndef PANTALLA_APRENDIZAJE_H
#define PANTALLA_APRENDIZAJE_H

#include "pantalla.h"
#include "hud.h"
#include "CController.h"

/*class mapa2D;
class hud;*/
class PantallaAprendizaje : public Pantalla
{
public:
		PantallaAprendizaje(IrrlichtDevice * IrrDevice,graphicEngine * _grEngine,shared_ptr<mapa2D> _mapa, int tipo);
		~PantallaAprendizaje();
		void pintarPantalla(vector<IDibujable*>*,vector<IDibujable*>*,vector<IDibujable*>*);
		virtual bool OnEvent(const SEvent& event);
private:
	CController* aprendizaje;
	CParams   g_Params;

};
#endif 
