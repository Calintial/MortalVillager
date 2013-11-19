#ifndef MAPA_H
#define MAPA_H

#include <iostream>

using namespace std;

class Unidades {
public:
	Mapa();
	~Mapa();
	void updateIA();


private:
	battleIA unit_ia;
	
};

#endif