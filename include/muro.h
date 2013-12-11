#ifndef MURO_H
#define MURO_H

//#include <irrlicht.h>
#include "IDibujable.h"

#include <string>
#include <vector>
#include <fstream>
#include <iostream>


class Muro : public IDibujable
{
public:
	Muro(int tipo, int posicionX,int posicionY);
	~Muro() override;
	/*ITexture* getTextura() const {
		return textura;
	}*/
	void Pintar(IVideoDriver* driver) override;
	//void setTextura(ITexture* tex){textura=tex;}
	bool isTransitable() override;
};

#endif
