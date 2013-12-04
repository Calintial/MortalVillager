#ifndef IDIBUJABLE_H
#define IDIBUJABLE_H

#include <irrlicht.h>

using namespace irr;
using namespace video;
using namespace std;
using namespace core;

class IDibujable{
	public:
		ITexture* getTextura() const {
			return textura;
		}
		virtual void Pintar(IVideoDriver* ) = 0;
		position2di getPosition(){return position;};
		void setPosition(int x, int y){position.X = x; position.Y = y;};
		void setPosition(position2di p){position.X = p.X; position.Y = p.Y;}
		void setTextura(ITexture* tex){textura=tex;}
		int getTipo(){return tipo;}
		void setTipo(int t){tipo=t;}
				
	private:
		ITexture* textura;
		int tipo;
		position2di position;
};
#endif
