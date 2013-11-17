// esto no está hecho para integrarlo directamente, está hecho así para poder hacer algo mientras no tenemos nada sobre lo que trabajar.

#include "Region.h"
#include "Enlace.h"
#include <iostream>
#include <vector>

using namespace std;

#define HEIGHT 20
#define WIDTH 20

class pathfinding
{
public:
	pathfinding();
	~pathfinding(); 
	void run();
	Region* getCorrespondingRegion(int x, int y);
	void createRegions();
	void analyzeRegions();
	void leftEdge(Region*);

private:
	int width,height; 
	int tamRegion;
	int mapa[HEIGHT][WIDTH];
	std::vector<Region*> regiones;
};