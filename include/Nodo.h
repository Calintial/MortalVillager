#ifndef NODO_H
#define NODO_H


#include <iostream>
#include <irrlicht.h>
using namespace irr::core;

class Nodo
{
public:
	Nodo(int _g,int _h,int _f,position2di _or,Nodo *_nodo);
	Nodo(const Nodo&);
	~Nodo();
	Nodo();
	bool operator<(const Nodo& nodo) const;
	position2di origen;
	int g;
    int h;
    int f;
    Nodo* p;	
};
#endif