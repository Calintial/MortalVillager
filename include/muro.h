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
	Muro(int posicionX,int posicionY);
	~Muro() override;
	/*ITexture* getTextura() const {
		return textura;
	}*/
	void Pintar(IVideoDriver*,int,int) override;
	//void setTextura(ITexture* tex){textura=tex;}
	bool isTransitable() override;
	void aplicarTextura(IVideoDriver* driver);

private:
	ITexture *TTexture_Suelo;
};

#endif
