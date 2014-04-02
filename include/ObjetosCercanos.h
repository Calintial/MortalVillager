#ifndef OBJETOSCERCANOS_H
#define OBJETOSCERCANOS_H
#include <vector>
#include "utils.h"
#include "SVector2D.h"
#include "CParams.h"
#include <irrlicht.h>
using namespace irr;
using namespace video;
using namespace std;
using namespace core;

class ObjetosCercanos{
	//0:Aldeano, 1:Arquero,2:Espadachin,3:Lancero,4:Obstaculo
	public:
	int tipo;

	double vida;

	position2di posicion;
	ObjetosCercanos(int _tipo,double _vida,int x, int y){tipo=_tipo;vida=_vida;posicion= position2di(x,y);};
	vector<double> getInputs(int x,int y);
};

#endif
