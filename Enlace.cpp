#include "Region.h"

Enlace::Enlace(int _origenX,int _origenY,int _destinoX,int _destinoY)
	:origenX(_origenX),origenY(_origenY),destinoX(_destinoX),destinoY(_destinoY)
{
	// hacer algo con los pesos, si hace falta y tal...
}

Enlace::Enlace(const Enlace& copia){
	origenX = copia.getOrigenX();
	destinoX = copia.getDestinoX();
	origenY = copia.getOrigenY();
	destinoY = copia.getDestinoY();
}

Enlace::~Enlace(){}