#include "IDibujable.h"
IDibujable::IDibujable(){
	pathfinding = NULL;
	vinculado = NULL;
}
IDibujable::~IDibujable() {

}
ITexture* IDibujable::getTextura() const {
	return textura;
}
void Pintar(IVideoDriver* ){

}
position2di IDibujable::getPosition(){
	return position;
}

void IDibujable::setPosition(int x, int y){
	position.X = x; position.Y = y;
	
}
void IDibujable::setPosition(position2di p){
	position.X = p.X; position.Y = p.Y;
	
}
void IDibujable::setTextura(ITexture* tex){
	textura=tex;
}
int IDibujable::getTipo(){
	return tipo;
}
void IDibujable::setTipo(int t){
	tipo=t;
}
bool IDibujable::isTransitable(){
	return true;
}
void IDibujable::setPathfinding(Pathfinding* _pathfinding){
	pathfinding = _pathfinding;
}

void IDibujable::setVinculado(IDibujable* _vinculado){
	vinculado = _vinculado;
}
IDibujable* IDibujable::getVinculado(){
	return vinculado;
}

/*void IDibujable::setSeleccionado(IVideoDriver* driver){
	setTextura(driver->getTexture("../media/Texturas/suelo/dirt.png"));
}*/

