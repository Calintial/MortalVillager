#ifndef ENLACE_H
#define ENLACE_H

#include <stdexcept> 
//#include "Region.h"
#include <iostream>

class Region;
class Enlace
{
public:
	Enlace(Region *r1, Region* r2, int peso);
	~Enlace();
	Region* getConnected(Region *whocalls);

//private:
	Region* reg1;
	Region* reg2;
	int intrapeso;

};
#endif