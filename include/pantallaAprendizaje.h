#ifndef PANTALLA_APRENDIZAJE_H
#define PANTALLA_APRENDIZAJE_H

#include "pantalla.h"
#include "hud.h"
#include "CController.h"

enum{
	CB_PAUSE = 0,
	BUTTON_CONTINUAR = 1,
	BUTTON_CARGAR = 2
};

/*class mapa2D;
class hud;*/
class PantallaAprendizaje : public Pantalla
{
public:
		PantallaAprendizaje(IrrlichtDevice * IrrDevice,graphicEngine * _grEngine,shared_ptr<mapa2D> _mapa, int tipo);
		~PantallaAprendizaje();
		void pintarPantalla(vector<shared_ptr<IDibujable>>*,vector<shared_ptr<IDibujable>>*,vector<shared_ptr<IDibujable>>*);
		virtual bool OnEvent(const SEvent& event);
private:
	gui::IGUIEnvironment* env;
	CController* aprendizaje;
	CParams   g_Params;
	bool paused;
	bool continuar;
		int cantidadVecesCadaMapa;
	int cantidadIndice;
	int tipoMapa;
	int cantidadMapas;

};
#endif 
