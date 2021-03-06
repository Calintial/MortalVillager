#include "NodoRegional.h"
#include "Region.h"
#include "mapa2D.h"
using namespace irr::core;

NodoRegional::NodoRegional(position2di _pos,int _g,int _h,Nodo*_padre,vertex_t _desciptor,Graph* _grafo):Nodo(_pos,_g,_h,_padre)
{
	descriptor = _desciptor;
	grafo = _grafo;
}

NodoRegional::NodoRegional():Nodo(){
	descriptor = (vertex_t)-1;
}

NodoRegional::NodoRegional(const NodoRegional& copia):Nodo(copia){
	this->descriptor = copia.descriptor;
	this->grafo = copia.grafo;
}

NodoRegional::~NodoRegional(){
	
}

void NodoRegional::init(position2di _pos,vertex_t _desc,Graph* _grafo){
	Nodo::init(_pos);
	descriptor = _desc;
	grafo = _grafo;
}

vertex_t NodoRegional::getVertexDescriptor(){
	return descriptor;
}

std::vector<Nodo*> NodoRegional::getHijos(position2di destino){
	std::vector<Nodo*> hijos;

	auto neighbours = boost::adjacent_vertices(descriptor,grafo->graph());
	for(auto i = neighbours.first; i != neighbours.second; ++i){
		Nodo* vecino = new NodoRegional(*(NodoRegional*)&grafo->graph()[*i]);
		Camino camino = (*grafo)[boost::edge(descriptor,*i,grafo->graph()).first];
		vecino->update(g + camino.getPeso(),vecino->distancia(destino),this);
		hijos.push_back(vecino);
	}
	return hijos;
}

Camino* NodoRegional::getCaminoDesdePadre(){
	if (padre != NULL)
	{
		auto edge = boost::edge(((NodoRegional*)padre)->getVertexDescriptor(),descriptor,*grafo);
		Camino* camino = &(*grafo)[edge.first];
		if (camino->getFinal() != getPosicion())
		{
			return camino->invertir();
		}else{
			return camino;
		}
	}else{
		return NULL;
	}
}

void NodoRegional::clear(){
	boost::clear_vertex_by_label(toString(),*grafo);
	boost::remove_vertex(toString(),*grafo);
}
