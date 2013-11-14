// esto no está hecho para integrarlo directamente, está hecho así para poder hacer algo mientras no tenemos nada sobre lo que trabajar.

#include "Region.h"
#include "Enlace.h"
#include <iostream>
#include <vector>

#define HEIGHT 10
#define WIDTH 10

class pathfinding
{
public:
	pathfinding();
	~pathfinding(){}
	void run();
	Region* getCorrespondingRegion(int x, int y);

//private:
	//int width,height;
	//int** mapa;
	std::vector<Region*> regiones;
};