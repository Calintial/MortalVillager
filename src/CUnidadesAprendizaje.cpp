#include "CUnidadesAprendizaje.h"

//-----------------------------------constructor-------------------------
//
//-----------------------------------------------------------------------
CUnidadesAprendizaje::CUnidadesAprendizaje(int x,int y):
							 m_life(100),
                             m_dFitness(0),
                             m_moveX(0),
                             m_moveY(0),
                             m_ataqueX(0),
                             m_ataqueY(0),
                             move(0)

			 
{
			m_vPosition = SVector2D(x, y); 
			
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
	m_life = 100;
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
bool CUnidadesAprendizaje::Update(IDibujable* Matriz[][MAPSIZE])
{
	vector<double> inputs=m_ItsBrain.changeObjectstoInputs(m_vObjetosCerca,m_life,m_vPosition.x,m_vPosition.y);

	vector<double> output = m_ItsBrain.Update(inputs);
	if( output.size()<CParams::iNumOutputs){
		return false;
	}
	double x,y;
	int xint,yint;
	x=output[0];
	y=output[1];
	if(0<x && x<=0.33){
		xint=m_vPosition.x-1;
	}
	else if(0.34<x && x<=0.66){
		xint=m_vPosition.x-1;
	}
	else{
		xint=m_vPosition.x+1;
	}
	if(0<y && y<=0.33){
		yint=m_vPosition.y-1;
	}
	else if(0.34<y && y<=0.66){
		yint=m_vPosition.y-1;
	}
	else{
		yint=m_vPosition.y+1;
	}
	if(xint<MAPSIZE && xint>0 && yint<MAPSIZE && yint>0 && output[2]>0.5 && Matriz[yint][xint]!=NULL && Matriz[yint][xint]->getTipo()==3){
		setAtaque(xint,yint);
		m_ataque=1;
		move=0;
		//setMovimiento(0,0);
	}
	else if(output[7]>0.5){
		SVector2D mov=mayorMovimiento(output[3],output[4],output[5],output[6],Matriz);
		if(mov.x>=0 && mov.x<MAPSIZE && mov.y>=0 && mov.y<MAPSIZE){
			setMovimiento(mov.x,mov.y);
			move=1;

		}

		m_ataque=0;
	}
	else{
		move=0;
		m_ataque=0;
	}

	/*for(double op:output){
		cout<<op<<",";
	}
	cout<<"M_ATAQUE: "<<m_ataque<<endl;*/
	/*ofstream outfile;
	#ifdef DEBUG
	outfile.open("GeneticMovimientos.txt", ios::app);
		if (outfile.is_open())
		{
							
			for(double op:output){
				outfile<<op<<",";
			}
		}

	outfile.close();
#endif*/
	return true;

}
void CUnidadesAprendizaje::calcular8Objetos(IDibujable* Matriz[][MAPSIZE]){
	int cant=0;
	for(int i= m_vPosition.y-1;i<=m_vPosition.y+1 && cant<8;i++){
		for(int j=m_vPosition.x-1;j<=m_vPosition.x+1 && cant<8;j++){

			if(i>=0 && i<=MAPSIZE-1 && j>=0 && j<=MAPSIZE-1){
				if(i==m_vPosition.y && j==m_vPosition.x){
					break;
				}

				if(Matriz[i][j]->getTipo()!=0){
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
		if(m_vPosition.y-1 <= i && i<= m_vPosition.y+1){
				break;
			}
		for(int j=m_vPosition.x-2;j<=m_vPosition.x+2 && cant<8;j++){
			if(m_vPosition.x-1 <= j && j<= m_vPosition.x+1){
				break;
			}
			if(i==m_vPosition.y && j==m_vPosition.x){
					break;
				}
			if(i>=0 && i<=MAPSIZE-1 && j>=0 && j<=MAPSIZE-1){
				if(Matriz[i][j]->getTipo()!=0){
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
SVector2D CUnidadesAprendizaje::mayorMovimiento(double arriba, double abajo, double izquierda, double derecha,IDibujable* Matriz[][MAPSIZE]){
	
	int x=0,y=0;
	x=	m_vPosition.y;
	y=m_vPosition.x-1;
	if(!( x>=0 && x<MAPSIZE &&  y>=0 &&  y<MAPSIZE) || Matriz[y][x]->getTipo()!=0){
		arriba=0;
	}
	x=	m_vPosition.y;
	y=m_vPosition.x+1;
	if( !( x>=0 &&  x<MAPSIZE &&  y>=0 &&  y<MAPSIZE)|| Matriz[y][x]->getTipo()!=0){
		abajo=0;
	}
	x=	m_vPosition.y-1;
	y=m_vPosition.x;
	if(!( x>=0 &&  x<MAPSIZE &&  y>=0 &&  y<MAPSIZE)|| Matriz[y][x]->getTipo()!=0){
		izquierda=0;
	}
	x=	m_vPosition.y+1;
	y=m_vPosition.x;
	if(!( x>=0 &&  x<MAPSIZE &&  y>=0 &&  y<MAPSIZE)|| Matriz[y][x]->getTipo()!=0){
		derecha=0;
	}
	double mejor=max(max(max(arriba,abajo),izquierda),derecha);
	ofstream outfile;
	outfile.open("GeneticMovimientos.txt", ios::app);


	
	if(arriba==mejor){
		if (outfile.is_open())
		{
			outfile<<"Arriba"<<endl;
		}
		return SVector2D(m_vPosition.x-1,m_vPosition.y);
	}
	else if(abajo==mejor){
		if (outfile.is_open())
		{
			outfile<<"Abajo"<<endl;
		}
		return SVector2D(m_vPosition.x+1,m_vPosition.y);
	}
	else if(izquierda==mejor){
		if (outfile.is_open())
		{
			outfile<<"Izquierda"<<endl;
		}
		return  SVector2D(m_vPosition.x,m_vPosition.y-1);
	}
	else if(derecha==mejor){
		if (outfile.is_open())
		{
			outfile<<"Derecha"<<endl;
		}
		return  SVector2D(m_vPosition.x,m_vPosition.y+1);
	}
	else{
		return SVector2D(m_vPosition.x,m_vPosition.y);
	}
	outfile.close();
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