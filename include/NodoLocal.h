#ifndef NODO_LOCAL_H
#define NODO_LOCAL_H


#include <iostream>
#include "Nodo.h"

class NodoLocal: public Nodo
{
public:
	NodoLocal(position2di _pos,int _g,int _h,Nodo* _padre,Region* _region,std::shared_ptr<mapa2D> _mapa);
	NodoLocal();
	NodoLocal(const NodoLocal&);
	~NodoLocal();

	Region* getRegion() const;

	void init(position2di _pos);
	void update(int _g,int _h,Nodo* _padre);

	std::vector<Nodo*> getHijos();

private:
	Region* regionActual;
	std::shared_ptr<mapa2D> mapa;
};
#endif



