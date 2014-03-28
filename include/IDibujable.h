#ifndef IDIBUJABLE_H
#define IDIBUJABLE_H

#include <irrlicht.h>
#include "Pathfinding.h"

using namespace irr;
using namespace video;
using namespace std;
using namespace core;

class IDibujable{
	public:
		IDibujable();
		virtual ~IDibujable() =0;
		ITexture* getTextura() const;
		virtual void Pintar(IVideoDriver*,int,int) = 0;
		virtual void aplicarTextura(IVideoDriver* driver) = 0;
		position2di getPosition();
		void setPosition(int x, int y);
		void setPosition(position2di p);
		void setTextura(ITexture* tex);
		int getTipo();
		void setTipo(int t);
		virtual bool isTransitable();
		void setPathfinding(Pathfinding*);
		void setVinculado(IDibujable*);
		IDibujable* getVinculado();
				
	private:
		ITexture* textura;
		int tipo;
		position2di position;
	protected:
		Pathfinding* pathfinding;
		IDibujable* vinculado;
};
#endif
