#include "CUnidadesAprendizaje.h"

//-----------------------------------constructor-------------------------
//
//-----------------------------------------------------------------------
CUnidadesAprendizaje::CUnidadesAprendizaje(int x,int y):
                             m_dFitness(0),
                             m_moveX(0),
                             m_moveY(0),
                             m_ataqueX(0),
                             m_ataqueY(0),
                             move(0)
{			
	setPosition(x,y);
	setLife(100);
}

//-------------------------------------------Reset()--------------------
//
//	Resets the sweepers position, fitness and rotation
//
//----------------------------------------------------------------------
void CUnidadesAprendizaje::Reset()
{
	
	move=0;
	m_dFitness = 0;
	m_ataque = 0;
	setLife(100);
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
bool CUnidadesAprendizaje::Update(MapaAprendizaje* matriz)
{

	vector<double> inputs=m_ItsBrain.changeObjectstoInputs(m_vObjetosCerca,	getLife(),getPosicion().X,getPosicion().Y);

	vector<double> output = m_ItsBrain.Update(inputs);
	if( output.size()<CParams::iNumOutputs){
		return false;
	}
	double x,y;
	int xint,yint;
	x=output[0];
	y=output[1];

	if(0<x && x<=0.33){
		xint=getPosicion().X-1;
	}
	else if(0.34<x && x<=0.66){
		xint=getPosicion().X-1;
	}
	else{
		xint=getPosicion().X+1;
	}
	if(0<y && y<=0.33){
		yint=getPosicion().Y-1;
	}
	else if(0.34<y && y<=0.66){
		yint=getPosicion().Y-1;
	}
	else{
		yint=getPosicion().Y+1;
	}

	if(xint<MAPSIZE && xint>0 && yint<MAPSIZE && yint>0 && output[2]>0.5 && matriz->getTile(yint,xint)!=NULL && matriz->getTile(yint,xint)->getTipo()==3){
		setAtaque(xint,yint);
		m_ataque=1;
		move=0;
		//setMovimiento(0,0);
	}
	else if(output[7]>0.5){
		position2di mov=mayorMovimiento(output[3],output[4],output[5],output[6],matriz);
		if(mov.X>=0 && mov.X<MAPSIZE && mov.Y>=0 && mov.Y<MAPSIZE){
			setMovimiento(mov.X,mov.Y);
			move=1;

		}
		else{
			move=0;
			m_ataque=0;
		}
	
	}
	else{
			outfile.open("GeneticMovimientos.txt", ios::app);
		if (outfile.is_open())
		{
							
				outfile<<"No hago nada porque ninguno es mayor a 0,5"<<endl;
			
		}

		outfile.close();
		move=0;
		m_ataque=0;
	}


	outfile.open("GeneticMovimientos.txt", ios::app);
		if (outfile.is_open())
		{
							
			for(double op:output){
				outfile<<op<<",";
			}
		}

	outfile.close();

	return true;

}
void CUnidadesAprendizaje::calcular8Objetos(MapaAprendizaje* matriz){
	m_vObjetosCerca.clear();
	int cant=0;
	for(int i= getPosicion().Y-1;i<=getPosicion().Y+1 && cant<8;i++){
		for(int j=getPosicion().X-1;j<=getPosicion().X+1 && cant<8;j++){

			if(i>=0 && i<=MAPSIZE-1 && j>=0 && j<=MAPSIZE-1){
				if(i==getPosicion().Y && j==getPosicion().X){
					continue;
				}

				if(matriz->getTile(i,j)->getTipo()!=0){
					if(matriz->getTile(i,j)->getTipo()==3){
						outfile.open("GeneticMovimientos.txt", ios::app);
							if (outfile.is_open())
							{
												
									outfile<<"He visto un enemigo ("<<j<<","<<i<<")"<<endl;
								
							}

							outfile.close();
							ObjetosCercanos obj(3,((CUnidadesAprendizaje*) matriz->getTile(i,j))->getLife(),j,i);
							m_vObjetosCerca.push_back(obj);
						
					}
					else{
						outfile.open("GeneticMovimientos.txt", ios::app);
							if (outfile.is_open())
							{
												
									outfile<<"He visto un muro ("<<j<<","<<i<<")"<<endl;
								
							}

							outfile.close();
						m_vObjetosCerca.push_back(ObjetosCercanos(matriz->getTile(i,j)->getTipo(),0,j,i));
					}
					cant++;
				}

			}
		}
		
	}
	for(int i= getPosicion().Y-2;i<=getPosicion().Y+2 && cant<8;i++){
		for(int j=getPosicion().X-2;j<=getPosicion().X+2 && cant<8;j++){
			if(getPosicion().Y-1 <= i && i<= getPosicion().Y+1 && getPosicion().X-1 <= j && j<= getPosicion().X+1){
				continue;
			}
			if(i>=0 && i<=MAPSIZE-1 && j>=0 && j<=MAPSIZE-1){
				if(matriz->getTile(i,j)->getTipo()!=0){
					if(matriz->getTile(i,j)->getTipo()==3){
						outfile.open("GeneticMovimientos.txt", ios::app);
							if (outfile.is_open())
							{
												
									outfile<<"He visto un enemigo ("<<i<<","<<j<<")"<<endl;
								
							}

							outfile.close();
						m_vObjetosCerca.push_back(ObjetosCercanos(3,((CUnidadesAprendizaje*) matriz->getTile(i,j))->getLife(),matriz->getTile(i,j)->getPosicion().X,matriz->getTile(i,j)->getPosicion().Y));
						
					}
					else{
							outfile.open("GeneticMovimientos.txt", ios::app);
							if (outfile.is_open())
							{
												
									outfile<<"He visto un muro ("<<i<<","<<j<<")"<<endl;
								
							}

							outfile.close();
						m_vObjetosCerca.push_back(ObjetosCercanos(matriz->getTile(i,j)->getTipo(),0,matriz->getTile(i,j)->getPosicion().X,matriz->getTile(i,j)->getPosicion().Y));
					}
					cant++;

			}
		}
		
	}
}
}
position2di CUnidadesAprendizaje::mayorMovimiento(double arriba, double abajo, double izquierda, double derecha,MapaAprendizaje* matriz){
	
	int x=0,y=0;
	x=	getPosicion().Y;
	y=getPosicion().X-1;
	if(!( x>=0 && x<MAPSIZE &&  y>=0 &&  y<MAPSIZE) || matriz->getTile(y,x)->getTipo()!=0){
		arriba=0;
	}
	x=	getPosicion().Y;
	y=getPosicion().X+1;
	if( !( x>=0 &&  x<MAPSIZE &&  y>=0 &&  y<MAPSIZE)|| matriz->getTile(y,x)->getTipo()!=0){
		abajo=0;
	}
	x=	getPosicion().Y-1;
	y=getPosicion().X;
	if(!( x>=0 &&  x<MAPSIZE &&  y>=0 &&  y<MAPSIZE)|| matriz->getTile(y,x)->getTipo()!=0){
		izquierda=0;
	}
	x=	getPosicion().Y+1;
	y=getPosicion().X;
	if(!( x>=0 &&  x<MAPSIZE &&  y>=0 &&  y<MAPSIZE)|| matriz->getTile(y,x)->getTipo()!=0){
		derecha=0;
	}
	double mejor=max(max(max(arriba,abajo),izquierda),derecha);
	ofstream outfile;
	outfile.open("GeneticMovimientos.txt", ios::app);


	
	if(arriba==mejor){
		if (outfile.is_open())
		{
			outfile<<"Estoy en la posición("<<getPosicion().X<<","<<getPosicion().Y<<") y me muevo arriba Arriba ("<<getPosicion().X-1<<","<<getPosicion().Y<<")"<<endl;
		}
		return position2di(getPosicion().X-1,getPosicion().Y);
	}
	else if(abajo==mejor){
		if (outfile.is_open())
		{
			outfile<<"Estoy en la posición("<<getPosicion().X<<","<<getPosicion().Y<<") y me muevo arriba Abajo ("<<getPosicion().X+1<<","<<getPosicion().Y<<")"<<endl;
		}
		return position2di(getPosicion().X+1,getPosicion().Y);
	}
	else if(izquierda==mejor){
		if (outfile.is_open())
		{
			outfile<<"Estoy en la posición("<<getPosicion().X<<","<<getPosicion().Y<<") y me muevo arriba Izquierda ("<<getPosicion().X<<","<<getPosicion().Y-1<<")"<<endl;
		}
		return  position2di(getPosicion().X,getPosicion().Y-1);
	}
	else if(derecha==mejor){
		if (outfile.is_open())
		{
outfile<<"Estoy en la posición("<<getPosicion().X<<","<<getPosicion().Y<<") y me muevo arriba derecha ("<<getPosicion().X<<","<<getPosicion().Y+1<<")"<<endl;
		}
		return  position2di(getPosicion().X,getPosicion().Y+1);
	}
	else{
		if (outfile.is_open())
		{
			outfile<<"No se mueve"<<endl;
		}
		return position2di(getPosicion().X,getPosicion().Y);
	}
	outfile.close();
	return position2di(0,0);
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

void CUnidadesAprendizaje::TexturaSeleccionada(IVideoDriver* driver,bool seleccionada)
{
	if(seleccionada)
		setTextura(driver->getTexture("../media/Texturas/units/aprendizaje_seleccionado.png"));
	else
		setTextura(driver->getTexture("../media/Texturas/units/aprendizaje.png"));
}
//E Vida quitada x tipox fitness /max fitness) x vida/100
void CUnidadesAprendizaje::IncrementFitness(CUnidadesAprendizaje *atacado,int danyo,double max_fitness){
	float tipo=0.5;
	double fitnessAtacado=atacado->Fitness();
	if(danyo>=3){
		tipo=2;
	}
	else if(danyo==2){
		tipo=1;
	}
	m_dFitness+=(danyo*tipo*fitnessAtacado/max_fitness)+1;
}
