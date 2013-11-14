#include "pathfinding.h"

pathfinding::pathfinding(){
	/*width = WIDTH;
	height = HEIGHT;
	mapa = new int[HEIGHT][WIDTH];*/
}

void pathfinding::run(){
	Region *r0 = new Region(0,0,2,2);
	Region *r1 = new Region(0,3,2,5);
	Region *r2 = new Region(3,0,5,2);
	Region *r3 = new Region(3,3,5,5);
	regiones.push_back(r0);
	regiones.push_back(r1);
	regiones.push_back(r2);
	regiones.push_back(r3);

	Enlace *link;
	link = new Enlace(r0,r1,10);
	link = new Enlace(r0,r2,10);
	link = new Enlace(r2,r3,10);
	link = new Enlace(r1,r3,10);
	std::cout<<"R0: "<<r0<<" - R1: "<<r1<<" - R2 "<<r2<<" - R3: "<<r3<<std::endl;
	std::cout<<"Voy a mostrar las regiones conectadas con r1"<<std::endl;
	std::vector<Region*> regionesConectadas = r1->getConnectedRegions();
	for (int i = 0; i < regionesConectadas.size(); ++i)
	{
		std::cout<<regionesConectadas[i]<<" ";
	}
	std::cout<<std::endl;

	std::cout<<"La región de 0,0 es: "<<getCorrespondingRegion(0,0)<<std::endl;
	std::cout<<"La región de 1,4 es: "<<getCorrespondingRegion(1,4)<<std::endl;
	std::cout<<"La región de 4,1 es: "<<getCorrespondingRegion(4,1)<<std::endl;
	std::cout<<"La región de 5,5 es: "<<getCorrespondingRegion(5,5)<<std::endl;

	delete r0;
	delete r1;
	delete r2;
	delete r3;
}

Region* pathfinding::getCorrespondingRegion(int x, int y){
	for (int i = 0; i < regiones.size(); ++i)
	{
		if(regiones[i]->isInside(x,y)){
			return regiones[i];
		}
	}
	return NULL;
}

int main(){
	pathfinding p;
	p.run();
	return 0;
}

