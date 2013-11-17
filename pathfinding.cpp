#include "pathfinding.h"

pathfinding::pathfinding(){
	width = WIDTH;
	height = HEIGHT;
	tamRegion = 10;
	cout<<"MAPA:"<<endl;
	for (int i = 0; i < height; ++i)
	{
		for (int j = 0; j < width; ++j)
		{
			if((j+1)%(i+1) == 0){
				mapa[i][j] = -1;
				cout<<"▣";
			}else{
				mapa[i][j] = 0;
				cout<<"□";
			}
		}
		cout<<endl;
	}
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
	for (int i = 0; i < width; i+=tamRegion)
	{
		for (int j = 0; j < height; j+=tamRegion)
		{
			finalX = i+tamRegion-1;
			finalY = j+tamRegion-1;
			if (finalY > height)
			{
				finalY = height - 1;
			}

			if (finalX > width)
			{
				finalX = width -1;
			}
			regiones.push_back(new Region(i,j,finalX,finalY));
		}
	}
}

void pathfinding::leftEdge(Region* actual){
	if (actual->inicioX > 0)
	{
		Region* regionIzquierda = getCorrespondingRegion(actual->inicioX-1,actual->inicioY);
		int iterador = actual->inicioY;

		int tamHueco = 0;
		int posHueco = -1;
		while(iterador < actual->finalY && iterador < height)
		{
			if (mapa[iterador][actual->inicioX] == 0 && mapa[iterador][regionIzquierda->finalX] == 0)
			{
				if (posHueco == -1)
				{
					posHueco = iterador;
				}
				tamHueco++;
			}else{
				if (tamHueco > 0)
				{
					// la conexión es (actual->inicioX,posHueco + tamHueco/2)<===>(regionIzquierda->finalX,posHueco + tamHueco/2)
					new Enlace(actual,regionIzquierda,0); //TODO: cambiar el peso
					cout<<"Nuevo enlace"<<endl;
					tamHueco = 0;
					posHueco = -1;
				}
				
			}
			iterador++;
		}
		if (tamHueco > 0)
		{
			new Enlace(actual,regionIzquierda,0); //TODO: cambiar el peso
			cout<<"Nuevo enlace"<<endl;
		}
	}
}

void pathfinding::analyzeRegions(){
	for (int regIndex = 0; regIndex < regiones.size(); ++regIndex)
	{
		Region* actual = regiones[regIndex];
		// borde izquierdo de cada region
		leftEdge(actual);
	}
}

void pathfinding::run(){
	createRegions();

	cout<<"He creado "<<regiones.size()<<" regiones"<<endl;
	for (int i = 0; i < regiones.size(); ++i)
	{
		cout<<"Reg"<<i<<"("<<regiones[i]<<") {"<<regiones[i]->inicioX<<","<<regiones[i]->inicioY<<" - "<<regiones[i]->finalX<<","<<regiones[i]->finalY<<"}"<<endl;
	}
	analyzeRegions();
	for (int i = 0; i < regiones.size(); ++i)
	{
		cout<<"### Reg"<<i<<"("<<regiones[i]<<") conectada con:"<<endl;
		std::vector<Region*> lista = regiones[i]->getConnectedRegions();
		for (int j = 0; j < lista.size(); ++j)
		{
			cout<<"Reg "<<lista[j]<<endl;
		}
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

