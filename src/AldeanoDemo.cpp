#include "AldeanoDemo.h"

AldeanoDemo::AldeanoDemo(position2di _posInicial, position2di _posDestino):AldeanoIA(_posInicial.X,_posInicial.Y)
{
	cout << "ConstruirAldeanoDemo" << endl;
	posInicial = _posInicial;
	posDestino = _posDestino;
	caminoDemo = NULL;
}


AldeanoDemo::~AldeanoDemo()
{
	cout << "DestruirAldeanoDemo" << endl;
}

void AldeanoDemo::updateIA(std::shared_ptr<mapa2D> mapa){

	if(pathfinding){
		if (!caminoDemo || !camino)
		{
			caminoDemo = pathfinding->calcularCamino(posInicial,posDestino);
			position2di final = caminoDemo->getFinal();
			for (int i = 0; i < 30; ++i)
			{
				caminoDemo->addNodo(final);
			}
			
			camino = new Camino(*caminoDemo);
		}

		state = MOVE;

		if (camino->getPeso() <= 1)
		{
			// actualizamos el camino a recorrer

			// si está en destino
			if (getPosition().X > (posDestino.X - posInicial.X)/2)
			{
				delete camino;
				camino = caminoDemo->invertir();
			}else{// si está en inicio
				delete camino;
				camino = new Camino(*caminoDemo);
			}
		}
		
		Move(camino);
	}
}