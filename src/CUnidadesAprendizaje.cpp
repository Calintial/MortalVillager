#include "CUnidadesAprendizaje.h"

//-----------------------------------constructor-------------------------
//
//-----------------------------------------------------------------------
CUnidadesAprendizaje::CUnidadesAprendizaje(IDibujable* Matriz[][MAPSIZE],int posicion):
							 m_life(1),
                             m_dFitness(0),
                             m_moveX(0),
                             m_moveY(0),
                             m_ataqueX(0),
                             m_ataqueY(0)

			 
{
	setTipo(3);
	
	bool unidadNoPuesta=true;
	
		int RandFloatX=0;
		int RandFloatY=0;
		if(posicion<20){
		//int RandFloatX=RandFloat() * MAPSIZE ;
			RandFloatX=posicion;
		int RandFloatY=0;
		}
		else{
			RandFloatX=posicion-19;
			RandFloatY=1;
		}
		if(Matriz[RandFloatY][RandFloatX]!=NULL){
			if(Matriz[RandFloatY][RandFloatX]->getTipo()!=3){
				unidadNoPuesta=false;
				m_vPosition = SVector2D(RandFloatX, RandFloatY);  				
			}
		}
		else{
			m_vPosition = SVector2D(RandFloatX, RandFloatY); 
			unidadNoPuesta=false;
		}
		
	

	
}

//-------------------------------------------Reset()--------------------
//
//	Resets the sweepers position, fitness and rotation
//
//----------------------------------------------------------------------
void CUnidadesAprendizaje::Reset(IDibujable* Matriz[][MAPSIZE])
{
	Matriz[m_vPosition.y][m_vPosition.x]=NULL;
	bool unidadNoPuesta=true;
	do{

		int RandFloatX=RandFloat() * MAPSIZE ;
		int RandFloatY=RandFloat() * MAPSIZE ;
		if(Matriz[RandFloatY][RandFloatX]!=NULL){
			if(Matriz[RandFloatY][RandFloatX]->getTipo()!=3){
				unidadNoPuesta=false;
				m_vPosition = SVector2D(RandFloatX, RandFloatY);  				
			}
		}
		else{
			m_vPosition = SVector2D(RandFloatX, RandFloatY); 
			unidadNoPuesta=false;
		}
		
	}
	while(unidadNoPuesta);
	setTipo(3);
	//and the fitness
	m_dFitness = 0;
	m_ataque = 0;
	m_life = 100;
	m_moveX = 0;
	m_moveY = 0;
	m_ataqueX = 0;
	m_ataqueY = 0;
	m_vObjetosCerca.clear();
	calcular8Objetos(Matriz);
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
bool CUnidadesAprendizaje::Update(IDibujable* Matriz[][MAPSIZE])
{
	vector<double> inputs=m_ItsBrain.changeObjectstoInputs(m_vObjetosCerca,m_life,m_vPosition.x,m_vPosition.y);

	vector<double> output = m_ItsBrain.Update(inputs);
	if(output.size()<CParams::iNumOutputs){
		return false;
	}
	double x,y;
	int xint,yint;
	x=output[0];
	y=output[1];
	if(0<x<=0,33){
		xint=m_vPosition.x-1;
	}
	else if(0,34<x<=0,66){
		xint=m_vPosition.x-1;
	}
	else{
		xint=m_vPosition.x+1;
	}
	if(0<y<=0,33){
		yint=m_vPosition.y-1;
	}
	else if(0,34<y<=0,66){
		yint=m_vPosition.y-1;
	}
	else{
		yint=m_vPosition.y+1;
	}
	if(xint<MAPSIZE && xint>0 && yint<MAPSIZE && yint>0 && output[2]>0.5 && Matriz[yint][xint]!=NULL && Matriz[yint][xint]->getTipo()==3){
		setAtaque(xint,yint);
		m_ataque=1;
		setMovimiento(0,0);
	}
	else{
		SVector2D mov=mayorMovimiento(output[3],output[4],output[5],output[6]);
		if(mov.x>=0 && mov.x<MAPSIZE && mov.y>=0 && mov.y<MAPSIZE){
			setMovimiento(mov.x,mov.y);
			

		}
		setAtaque(0,0);
		m_ataque=0;
	}

	/*for(double op:output){
		cout<<op<<",";
	}
	cout<<"M_ATAQUE: "<<m_ataque<<endl;*/
	ofstream outfile;
	#ifdef DEBUG
	outfile.open("Genetic.txt", ios::app);
		if (outfile.is_open())
		{
							
			for(double op:output){
				outfile<<op<<",";
			}
		}

	outfile.close();
#endif
	return true;

}
void CUnidadesAprendizaje::calcular8Objetos(IDibujable* Matriz[][MAPSIZE]){
	int cant=0;
	for(int i= m_vPosition.y-1;i<=m_vPosition.y+1 && cant<8;i++){
		for(int j=m_vPosition.x-1;j<m_vPosition.x+1 && cant<8;j++){

			if(i>=0 && i<=MAPSIZE-1 && j>=0 && j<=MAPSIZE-1){
				
				if(Matriz[i][j]!=NULL){
					if(Matriz[i][j]->getTipo()==3){
						m_vObjetosCerca.push_back(ObjetosCercanos(3,((CUnidadesAprendizaje*) Matriz[i][j])->getLife(),Matriz[i][j]->getPosicion().X,Matriz[i][j]->getPosicion().Y));

					}
					else{
						m_vObjetosCerca.push_back(ObjetosCercanos(Matriz[i][j]->getTipo(),0,Matriz[i][j]->getPosicion().X,Matriz[i][j]->getPosicion().Y));
					}
					cant++;
				}

			}
		}
		
	}
	for(int i= m_vPosition.y-2;i<=m_vPosition.y+2 && cant<8;i++){
		for(int j=m_vPosition.x-2;j<m_vPosition.x+2 && cant<8;j++){
			if(i>=0 && i<=MAPSIZE-1 && j>=0 && j<=MAPSIZE-1){
				if(Matriz[i][j]!=NULL){
					if(Matriz[i][j]->getTipo()==3){
						m_vObjetosCerca.push_back(ObjetosCercanos(3,((CUnidadesAprendizaje*) Matriz[i][j])->getLife(),Matriz[i][j]->getPosicion().X,Matriz[i][j]->getPosicion().Y));

					}
					else{
						m_vObjetosCerca.push_back(ObjetosCercanos(Matriz[i][j]->getTipo(),0,Matriz[i][j]->getPosicion().X,Matriz[i][j]->getPosicion().Y));
					}
					cant++;

			}
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

void CUnidadesAprendizaje::Pintar(IVideoDriver* driver,int TPositionX,int TPositionY)
{
	ITexture *TTexture = getTextura();
	driver->draw2DImage(TTexture, position2di(TPositionX, TPositionY), rect<s32>(0,0,TTexture->getSize().Width, TTexture->getSize().Height), 0, SColor((u32)((1.0f - 0.0f) * 255), 255, 255, 255), true);

}

void CUnidadesAprendizaje::aplicarTextura(IVideoDriver* driver)
{
	setTextura(driver->getTexture("../media/Texturas/units/aprendizaje.png"));
}