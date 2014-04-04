#ifndef ALDEANODEMO_H
#define ALDEANODEMO_H

#include <iostream>
#include "AldeanoIA.h"

class AldeanoDemo : public AldeanoIA{

public:
	AldeanoDemo(position2di posInicial, position2di posDestino);
	~AldeanoDemo();

	void updateIA(std::shared_ptr<mapa2D> mapa);

private:
	Camino* caminoDemo;
	position2di posInicial;
	position2di posDestino;
};

#endif