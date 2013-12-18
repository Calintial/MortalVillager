#ifndef IDIBUJABLE_H
#define IDIBUJABLE_H

#include <irrlicht.h>

using namespace irr;
using namespace video;
using namespace std;
using namespace core;

class IDibujable{
	public:
		virtual ~IDibujable(){}
		ITexture* getTextura() const {
			return textura;
		}
		virtual void Pintar(IVideoDriver*,int,int) = 0;
		virtual void aplicarTextura(IVideoDriver* driver) = 0;
		position2di getPosition(){return position;};
		void setPosition(int x, int y){position.X = x; position.Y = y;};
		void setPosition(position2di p){position.X = p.X; position.Y = p.Y;}
		void setTextura(ITexture* tex){textura=tex;}
		int getTipo(){return tipo;}
		void setTipo(int t){tipo=t;}
		bool isTransitable();
				
	private:
		ITexture* textura;
		int tipo;
		position2di position;
};
#endif
