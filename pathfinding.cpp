#include "pathfinding_deverdad.h"
#include <boost/graph/graphviz.hpp>

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

pathfinding::~pathfinding(){}

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
			//regiones.push_back();
			vertex_t vertice = boost::add_vertex(grafoRegiones);
			grafoRegiones[vertice].inicioX = i;
			grafoRegiones[vertice].inicioY = j;
			grafoRegiones[vertice].finalX = finalX;
			grafoRegiones[vertice].finalY = finalY;
		}
	}
}

void pathfinding::run(){
	createRegions();
	
	std::pair<vertex_iter, vertex_iter> vp;
	for (vp = vertices(grafoRegiones); vp.first != vp.second; ++vp.first){
		std::cout << grafoRegiones[*vp.first].inicioX << ", " << grafoRegiones[*vp.first].inicioY << std::endl;
	}
	std::cout << std::endl;
}

int main(){
	pathfinding p;
	p.run();
	return 0;
}

