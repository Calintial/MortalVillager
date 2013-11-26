#ifndef ENLACE_H
#define ENLACE_H

#include <stdexcept> 
#include <iostream>

class Enlace
{
public:
	Enlace(int,int,int,int);
	Enlace(const Enlace&);
	~Enlace();

	int getOrigenX() const {return origenX;}
	int getOrigenY() const {return origenY;}
	int getDestinoX() const {return destinoX;}
	int getDestinoY() const {return destinoY;}

private:
	int origenX,origenY;
	int destinoX,destinoY;

	std::vector<int> pesos;

};
#endif