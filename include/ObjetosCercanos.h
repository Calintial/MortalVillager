#ifndef OBJETOSCERCANOS_H
#define OBJETOSCERCANOS_H
#include <vector>
#include "utils.h"
#include "SVector2D.h"
#include "CParams.h"
class ObjetosCercanos{
	//0:Aldeano, 1:Arquero,2:Espadachin,3:Lancero,4:Obstaculo
	public:
	int tipo;

	double vida;

	SVector2D posicion;
	ObjetosCercanos(int _tipo,double _vida,int x, int y){tipo=_tipo;vida=_vida;posicion= SVector2D(x,y);};
	vector<double> getInputs(int x,int y);
};

#endif
