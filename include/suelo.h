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
	~Suelo() override;
	/*ITexture* getTextura() const {
		return textura;
	}*/
	void Pintar(IVideoDriver*,int,int) override;
	void aplicarTextura(IVideoDriver* driver) override;
	//void setTextura(ITexture* tex){textura=tex;}
	bool isTransitable() override;
};

#endif
