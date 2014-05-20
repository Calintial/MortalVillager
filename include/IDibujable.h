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
		void setDriver(IVideoDriver* _driver){m_driver = _driver;}
		position2di getPosition();
		void setPosition(int x, int y);
		void setPosition(position2di p);
		void setTextura(ITexture* tex);
		position2di getPosicion(){return position;};
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
		IVideoDriver* m_driver;
};
#endif
