#include "CUnidadesAprendizaje.h"

//-----------------------------------constructor-------------------------
//
//-----------------------------------------------------------------------
CUnidadesAprendizaje::CUnidadesAprendizaje(IDibujable* Matriz[][MAPSIZE]):
							 m_life(1),
                             m_dFitness(0),
                             m_moveX(0),
                             m_moveY(0),
                             m_ataqueX(0),
                             m_ataqueY(0)

			 
{
	setTipo(3);
	
	bool unidadNoPuesta=true;
	do{
		int RandFloatX=RandFloat() * MAPSIZE ;
		int RandFloatY=RandFloat() * MAPSIZE ;
		if(Matriz[RandFloatX][RandFloatY]!=NULL){
			if(Matriz[RandFloatX][RandFloatY]->getTipo()!=3){
				unidadNoPuesta=true;
				m_vPosition = SVector2D(RandFloatX, RandFloatX);  				
			}
		}
		else{
			m_vPosition = SVector2D(RandFloatX, RandFloatX); 
			unidadNoPuesta=true;
		}
		
	}
	while(unidadNoPuesta);
	
}

//-------------------------------------------Reset()--------------------
//
//	Resets the sweepers position, fitness and rotation
//
//----------------------------------------------------------------------
void CUnidadesAprendizaje::Reset()
{
	//reset the sweepers positions
	m_vPosition = SVector2D((RandFloat() * CParams::WindowWidth), 
					                (RandFloat() * CParams::WindowHeight));
	
	//and the fitness
	m_dFitness = 0;

	m_life = 1;
	m_moveX = 0;
	m_moveY = 0;
	m_ataqueX = 0;
	m_ataqueY = 0;
	m_vObjetosCerca.clear();
	return;
}

//-------------------------------Update()--------------------------------
//
//	First we take sensor readings and feed these into the sweepers brain.
//
//	The inputs are:
//	
//	A vector to the closest mine (x, y)
//	The sweepers 'look at' vector (x, y)
//
//	We receive two outputs from the brain.. lTrack & rTrack.
//	So given a force for each track we calculate the resultant rotation 
//	and acceleration and apply to current velocity vector.
//
//-----------------------------------------------------------------------
bool CUnidadesAprendizaje::Update()
{
	vector<double> inputs=m_ItsBrain.changeObjectstoInputs(m_vObjetosCerca,m_life,m_vPosition.x,m_vPosition.y);

	vector<double> output = m_ItsBrain.Update(inputs);
	if(output.size()<CParams::iNumOutputs){
		return false;
	}
	setAtaque(output[0],output[1]);
	m_ataque=output[2];
	if(m_ataque>0.5){
		m_ataque=1;
		setMovimiento(0,0);
	}
	else{
		SVector2D mov=mayorMovimiento(output[3],output[4],output[5],output[6]);
		setMovimiento(mov.x,mov.y);
		m_ataque=0;
	}
	return true;

}
void CUnidadesAprendizaje::calcular8Objetos(IDibujable* Matriz[][MAPSIZE]){
	int cant=0;
	for(int i= m_vPosition.x-1;i<=m_vPosition.x+1 && cant<8;i++){
		for(int j=m_vPosition.y-1;j<m_vPosition.y+1 && cant<8;j++){

			if(i>=0 && i<=MAPSIZE && j>=0 && j<=MAPSIZE){
				
				if(Matriz[j][i]!=NULL){
					if(Matriz[j][i]->getTipo()==3){
						m_vObjetosCerca.push_back(ObjetosCercanos(Matriz[j][i]->getTipo(),((CUnidadesAprendizaje*) Matriz[j][i])->getLife(),Matriz[j][i]->getPosicion().X,Matriz[j][i]->getPosicion().Y));

					}
					else{
						m_vObjetosCerca.push_back(ObjetosCercanos(Matriz[j][i]->getTipo(),0,Matriz[j][i]->getPosicion().X,Matriz[j][i]->getPosicion().Y));
					}
					cant++;
				}

			}
		}
		
	}
	for(int i= m_vPosition.x-2;i<=m_vPosition.x+2 && cant<8;i++){
		for(int j=m_vPosition.y-2;j<m_vPosition.y+2 && cant<8;j++){
			if(i>=0 && i<=MAPSIZE && j>=0 && j<=MAPSIZE){
					if(Matriz[j][i]->getTipo()==3){
						m_vObjetosCerca.push_back(ObjetosCercanos(Matriz[j][i]->getTipo(),((CUnidadesAprendizaje*) Matriz[j][i])->getLife(),Matriz[j][i]->getPosicion().X,Matriz[j][i]->getPosicion().Y));

					}
					else{
						m_vObjetosCerca.push_back(ObjetosCercanos(Matriz[j][i]->getTipo(),0,Matriz[j][i]->getPosicion().X,Matriz[j][i]->getPosicion().Y));
					}
					cant++;

			}
		}
		
	}
}
SVector2D CUnidadesAprendizaje::mayorMovimiento(int arriba, int abajo, int izquierda, int derecha){
	int mejor=max(max(max(arriba,abajo),izquierda),derecha);
	if(arriba==mejor){
		return SVector2D(m_vPosition.x-1,m_vPosition.y);
	}
	else if(abajo==mejor){
		return SVector2D(m_vPosition.x+1,m_vPosition.y);
	}
	else if(izquierda==mejor){
		return  SVector2D(m_vPosition.x,m_vPosition.y-1);
	}
	else{
		return  SVector2D(m_vPosition.x,m_vPosition.y+1);
	}
}