#ifndef IDIBUJABLE_H
#define IDIBUJABLE_H

#include <irrlicht.h>

using namespace irr;
using namespace video;
using namespace std;
using namespace core;

class IDibujable{
	public:
		virtual ~IDibujable() =0;
		ITexture* getTextura() const;
		virtual void Pintar(IVideoDriver* ) = 0;
		position2di getPosition();
		void setPosition(int x, int y);
		void setPosition(position2di p);
		void setTextura(ITexture* tex);
		int getTipo();
		void setTipo(int t);
		virtual bool isTransitable();
				
	private:
		ITexture* textura;
		int tipo;
		position2di position;
};
#endif
