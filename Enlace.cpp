#include "Region.h"

Enlace::Enlace(Region *r1, Region* r2, int peso){
	reg1 = r1;
	r1->add(this);
	reg2 = r2;
	r2->add(this);
	intrapeso = peso;
}

Enlace::~Enlace(){
	reg1->remove(this);
	reg2->remove(this);
}

Region* Enlace::getConnected(Region *whocalls){
	if (reg1 == whocalls)
	{
		return reg2;
	}else if (reg2 == whocalls) 
	{
		return reg1;
	}else{
		std::string mensaje = "";
		mensaje += (long)whocalls;
		mensaje += "is not connected to this link";
		throw std::runtime_error(mensaje);
	}
}