#ifndef ALDEANODEMO_H
#define ALDEANODEMO_H

#include <iostream>
#include "AldeanoIA.h"

class AldeanoDemo : public AldeanoIA{

public:
	AldeanoDemo(position2di posInicial, position2di posDestino);
	~AldeanoDemo();

	void updateIA(vector<IDibujable*>*);

private:
	Camino* caminoDemo;
	position2di posInicial;
	position2di posDestino;
};

#endif