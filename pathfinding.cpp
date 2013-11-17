#include "pathfinding.h"

pathfinding::pathfinding(){
	width = WIDTH;
	height = HEIGHT;
	tamRegion = 10;
}

pathfinding::~pathfinding(){
	for (int i = 0; i < regiones.size(); ++i)
	{
		delete regiones[i];
	}
	regiones.clear();
}

void pathfinding::createRegions(){
	int finalX,finalY;
	for (int i = 0; i < height; i+=tamRegion)
	{
		for (int j = 0; j < width; j+=tamRegion)
		{
			finalX = i+tamRegion-1;
			finalY = j+tamRegion-1;
			if (finalX > height)
			{
				finalX = height - 1;
			}

			if (finalY > width)
			{
				finalY = width -1;
			}
			regiones.push_back(new Region(i,j,finalX,finalY));
		}
	}
}

void pathfinding::run(){
	createRegions();

	cout<<"He creado "<<regiones.size()<<" regiones"<<endl;
	for (int i = 0; i < regiones.size(); ++i)
	{
		cout<<"Reg"<<i<<" {"<<regiones[i]->inicioX<<","<<regiones[i]->inicioY<<" - "<<regiones[i]->finalX<<","<<regiones[i]->finalY<<"}"<<endl;
	}
	/*Enlace *link;
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
	delete r3;*/
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

