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

std::vector<Nodo*> NodoRegional::getHijos(){
	cout<<"TODO"<<endl;
}