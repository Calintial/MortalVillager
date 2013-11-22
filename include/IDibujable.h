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
		void setTextura(ITexture* tex){textura=tex;}
		int getTipo(){return tipo;}
		void setTipo(int t){tipo=t;}
				
	private:
		ITexture* textura;
		int tipo;
};
#endif
