// esto no está hecho para integrarlo directamente, está hecho así para poder hacer algo mientras no tenemos nada sobre lo que trabajar.

#include "Region.h"
#include "Enlace.h"
#include <iostream>
#include <vector>

using namespace std;

#define HEIGHT 102
#define WIDTH 106

class pathfinding
{
public:
	pathfinding();
	~pathfinding();
	void run();
	Region* getCorrespondingRegion(int x, int y);
	void createRegions();

private:
	int width,height;
	int tamRegion;
	int mapa[HEIGHT][WIDTH];
	std::vector<Region*> regiones;
};