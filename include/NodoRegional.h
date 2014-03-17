#ifndef NODO_REGIONAL_H
#define NODO_REGIONAL_H


#include <iostream>
#include "Nodo.h"

typedef boost::graph_traits<Graph>::vertex_descriptor vertex_t;

class NodoRegional: public Nodo
{
public:
	NodoRegional(position2di _pos,int _g,int _h,Nodo* _padre,vertex_t _desciptor,Graph* _grafo);
	NodoRegional();
	NodoRegional(const NodoRegional&);
	virtual ~NodoRegional();

	void init(position2di _pos,vertex_t _desc,Graph* _grafo);
	//void update(int _g,int _h,Nodo* _padre);
	vertex_t getVertexDescriptor();
	std::vector<Nodo*> getHijos();
	Camino* getCaminoDesdePadre();

private:
    vertex_t descriptor;
    Graph* grafo;
};
#endif



