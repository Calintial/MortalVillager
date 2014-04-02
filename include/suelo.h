#ifndef SUELO_H
#define SUELO_H

//#include <irrlicht.h>
#include "IDibujable.h"
#include "mapa2D.h"

#include <string>
#include <vector>
#include <fstream>
#include <iostream>


class Suelo : public IDibujable
{
public:
	Suelo(int i, int j);
	~Suelo() override;
	/*ITexture* getTextura() const {
		return textura;
	}*/
	void Pintar(IVideoDriver*,int,int) override;
	void aplicarTextura(IVideoDriver* driver) override;
	//void setTextura(ITexture* tex){textura=tex;}
	bool isTransitable() override;
	void setIsometric(bool iso);

private:
	bool isometric;
};

#endif
