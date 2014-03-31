#include "EspadachinRedes.h"

EspadachinRedes::EspadachinRedes(int x,int y): CUnidadesAprendizaje(x,y){

	vision_range = 2;
	attack_range = 1;
	attack_value = 1;
	setTipo(3);
}
void EspadachinRedes::TexturaSeleccionada(IVideoDriver* driver,bool selected)
{
	if(selected)
		setTextura(driver->getTexture("../media/Texturas/units/ia_unit_selected.png"));
	else
		setTextura(driver->getTexture("../media/Texturas/units/ia_swordman.png"));
}