#ifndef SUELO_H
#define SUELO_H

//#include <irrlicht.h>
#include "IDibujable.h"

#include <string>
#include <vector>
#include <fstream>
#include <iostream>


class Suelo : public IDibujable
{
public:
	Suelo(int t, int i, int j);
	~Suelo();
	/*ITexture* getTextura() const {
		return textura;
	}*/
	void Pintar(IVideoDriver* driver);
	//void setTextura(ITexture* tex){textura=tex;}
};

#endif
