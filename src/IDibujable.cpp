#include "IDibujable.h"
IDibujable::~IDibujable() {
	delete textura;
	delete vinculado;
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
void IDibujable::setVinculado(IDibujable* _vinculado){
	vinculado = _vinculado;
}
IDibujable* IDibujable::getVinculado(){
	return vinculado;
}