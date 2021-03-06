#include "CUnidadesAprendizaje.h"

//-----------------------------------constructor-------------------------
//
//-----------------------------------------------------------------------
CUnidadesAprendizaje::CUnidadesAprendizaje(int x,int y):
                             m_dFitness(1),
                             m_moveX(0),
                             m_moveY(0),
                             m_ataqueX(0),
                             m_ataqueY(0),
                             move(0),
                             m_ataque(0)
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
	m_dFitness = 1;
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
bool CUnidadesAprendizaje::Update(std::shared_ptr<mapa2D> matriz)
{

	vector<double> inputs=m_ItsBrain.changeObjectstoInputs(m_vObjetosCerca,	getLife(),getPosicion().X,getPosicion().Y);

	output = m_ItsBrain.Update(inputs);
	if( output.size()<CParams::iNumOutputs){
		return false;
	}
	double x,y;
	int xint,yint;
	setMovimiento(0,0);
	setAtaque(0,0);
	x=output[0];
	y=output[1];
	m_ataque=0;
	move=0;
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

	if(xint<MAPSIZE && xint>0 && yint<MAPSIZE && yint>0 && output[2]>0.5 && matriz->getTile(yint,xint)->getVinculado()!=NULL && matriz->getTile(yint,xint)->getVinculado()->getTipo()==3){
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
void CUnidadesAprendizaje::calcular8Objetos(std::shared_ptr<mapa2D> matriz){
	m_vObjetosCerca.clear();
	int cant=0;
	for(int i= getPosicion().Y-1;i<=getPosicion().Y+1 && cant<8;i++){
		for(int j=getPosicion().X-1;j<=getPosicion().X+1 && cant<8;j++){

			if(i>=0 && i<=MAPSIZE-1 && j>=0 && j<=MAPSIZE-1){
				if(i==getPosicion().Y && j==getPosicion().X){
					continue;
				}

				if(matriz->getTile(i,j)->getTipo()!=0){
					m_vObjetosCerca.push_back(ObjetosCercanos(matriz->getTile(i,j)->getTipo(),0,j,i));
					cant++;
				}else{
					if(matriz->getTile(i,j)->getVinculado() != NULL){
						if(matriz->getTile(i,j)->getVinculado()->getTipo()==3){
							CUnidadesAprendizaje* unidad = (CUnidadesAprendizaje*)matriz->getTile(i,j)->getVinculado();
							ObjetosCercanos obj(3, unidad->getLife(),j,i);
							m_vObjetosCerca.push_back(obj);
							cant++;
						}	
					}
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
					m_vObjetosCerca.push_back(ObjetosCercanos(matriz->getTile(i,j)->getTipo(),0,j,i));
					cant++;
				}else{
					if(matriz->getTile(i,j)->getVinculado() != NULL){
						if(matriz->getTile(i,j)->getVinculado()->getTipo()==3){
							CUnidadesAprendizaje* unidad = (CUnidadesAprendizaje*)matriz->getTile(i,j)->getVinculado();
							ObjetosCercanos obj(3, unidad->getLife(),j,i);
							m_vObjetosCerca.push_back(obj);
							cant++;
						}	
					}
				}
			}
		
		}
	}
}
position2di CUnidadesAprendizaje::mayorMovimiento(double _izquierda, double _derecha, double _arriba, double _abajo,std::shared_ptr<mapa2D> matriz){
	
	int x=0,y=0;
	y=	getPosicion().Y;
	x=getPosicion().X-1;
	if(!( x>=0 && x<MAPSIZE &&  y>=0 &&  y<MAPSIZE) || matriz->getTile(y,x)->getTipo()!=0 || matriz->getTile(y,x)->getVinculado() != NULL){
		_izquierda=0;
	}
	y=	getPosicion().Y;
	x=getPosicion().X+1;
	if( !( x>=0 &&  x<MAPSIZE &&  y>=0 &&  y<MAPSIZE)|| matriz->getTile(y,x)->getTipo()!=0 || matriz->getTile(y,x)->getVinculado() != NULL){
		_derecha=0;
	}
	y=	getPosicion().Y-1;
	x=getPosicion().X;
	if(!( x>=0 &&  x<MAPSIZE &&  y>=0 &&  y<MAPSIZE)|| matriz->getTile(y,x)->getTipo()!=0 || matriz->getTile(y,x)->getVinculado() != NULL){
		_arriba=0;
	}
	y=	getPosicion().Y+1;
	x=getPosicion().X;
	if(!( x>=0 &&  x<MAPSIZE &&  y>=0 &&  y<MAPSIZE)|| matriz->getTile(y,x)->getTipo()!=0 || matriz->getTile(y,x)->getVinculado() != NULL){
		_abajo=0;
	}
	double mejor=max(max(max(_izquierda,_abajo),_arriba),_derecha);
	ofstream outfile;
	outfile.open("GeneticMovimientos.txt", ios::app);


	
	if(_izquierda==mejor){
		if (outfile.is_open())
		{
			outfile<<"Estoy en la posición("<<getPosicion().X<<","<<getPosicion().Y<<") y me muevo _izquierda  ("<<getPosicion().X-1<<","<<getPosicion().Y<<")"<<endl;
		}
		return position2di(getPosicion().X-1,getPosicion().Y);
	}
	else if(_derecha==mejor){
		if (outfile.is_open())
		{
			outfile<<"Estoy en la posición("<<getPosicion().X<<","<<getPosicion().Y<<") y me muevo _derecha("<<getPosicion().X+1<<","<<getPosicion().Y<<")"<<endl;
		}
		return position2di(getPosicion().X+1,getPosicion().Y);
	}
	else if(_arriba==mejor){
		if (outfile.is_open())
		{
			outfile<<"Estoy en la posición("<<getPosicion().X<<","<<getPosicion().Y<<") y me muevo  _arriba ("<<getPosicion().X<<","<<getPosicion().Y-1<<")"<<endl;
		}
		return  position2di(getPosicion().X,getPosicion().Y-1);
	}
	else if(_abajo==mejor){
		if (outfile.is_open())
		{
outfile<<"Estoy en la posición("<<getPosicion().X<<","<<getPosicion().Y<<") y me muevo  _abajo ("<<getPosicion().X<<","<<getPosicion().Y+1<<")"<<endl;
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
	setTextura(driver->getTexture("../media/Texturas/units/ia_swordman.png"));
}
void CUnidadesAprendizaje::PintarAtacar(IVideoDriver* driver,bool atacando)
{
	if(atacando)
		setTextura(driver->getTexture("../media/Texturas/units/user_swordman.png"));

	else
		setTextura(driver->getTexture("../media/Texturas/units/aprendizaje.png"));
}

void CUnidadesAprendizaje::TexturaSeleccionada(IVideoDriver* driver,bool seleccionada)
{
	if(seleccionada)
		setTextura(driver->getTexture("../media/Texturas/units/ia_unit_selected.png"));
	else
		setTextura(driver->getTexture("../media/Texturas/units/ia_swordman.png"));
}
//E Vida quitada x tipox fitness /max fitness) x vida/100
void CUnidadesAprendizaje::IncrementFitness(CUnidadesAprendizaje* atacado,int danyo){
	if(danyo>0 && atacado->getLife()==0){
		m_dFitness++;
	}
	
	m_dFitness+=danyo;
	if(m_dFitness>=290){
		cout<<"UNO DE 400!!!!!######################################################"<<endl;
		std::ofstream pesosActualesFile;
			vector<double> vecW=m_ItsBrain.GetWeights();
			pesosActualesFile.open("Mejor.txt",ios::app);
			if (pesosActualesFile.is_open())
			{
					pesosActualesFile<<"Fitness: "<<m_dFitness<<endl;
					pesosActualesFile<<vecW[0];
					for (int j = 1; j < vecW.size(); ++j)
					{
						pesosActualesFile<<","<<vecW[j]<<std::setprecision(20);
					}
					pesosActualesFile<<endl;
				
				pesosActualesFile.close();
			}

	}
}


	
bool CUnidadesAprendizaje::enemy_in_attack_range(position2di){
	// TODO: qu´e se supone que hace esto?...
	return false;
}
void CUnidadesAprendizaje::Recovery(){
	//cout<<"Me recupero <" << getPosition().X <<","<<getPosition().Y << ">"<<endl;
	if(getLife()<100){
		setLife(getLife()+1);	
	}
}
void CUnidadesAprendizaje::updateIA(std::shared_ptr<mapa2D> mapa){
//bool CController::tickRedNeuronalUnidad(shared_ptr<CUnidadesAprendizaje> unidad, const int i){
	if (this->getLife() > 0)
		{
			
			//Pintar();
				//update the NN and position
			/*outfile.open("GeneticMovimientos.txt", ios::app);
			if (outfile.is_open())
			{
				outfile << "La unidad ANTES : "<<i<<" tiene de Fitness :"<<this->Fitness()<<" y esta en la posición: ("<<this->getPosicion().X <<","<<this->getPosicion().Y<<")"<<endl;

			}

			outfile.close();*/
			if (!this->Update(mapa))
			{

					//error in processing the neural net
				cout<<"Wrong amount of NN inputs!"<<endl;
//				return false;
			}


			/*outfile.open("GeneticMovimientos.txt", ios::app);
			if (outfile.is_open())
			{
				outfile << "La unidad : "<<i<<" tiene de Fitness :"<<this->Fitness()<<" y esta en la posición: ("<<this->getPosicion().X <<","<<this->getPosicion().Y<<")"<<endl;

			}

			outfile.close();*/
			//PintarAtacar(m_driver,getAtaque());
			if(this->getAtaque()==1){
				position2di atacando=this->getAtaqueMovimiento();

				if(mapa->getTile(atacando.Y,atacando.X)->getVinculado()!=NULL && mapa->getTile(atacando.Y,atacando.X)->getVinculado()->getTipo()==3){

					CUnidadesAprendizaje* enemigo = (CUnidadesAprendizaje*)mapa->getTile(atacando.Y,atacando.X)->getVinculado();
					int dano = this->Attack(enemigo);
					this->IncrementFitness(enemigo,dano);
					
					outfile.open("GeneticMovimientos.txt", ios::app);
					if (outfile.is_open())
					{

						outfile << "Y esta atacando a: ("<<atacando.X<<","<<atacando.Y<<")"<<endl;
					}

					outfile.close();
					
				}

				m_ataque=0;
			}
			else{

				if(this->getMover()==1){
					//video::IVideoDriver* driver = device->getVideoDriver();
					/*mapa->setTile(this->getPosicion(),shared_ptr<Suelo>( new Suelo(this->getPosicion().X,this->getPosicion().Y)));
					std::dynamic_pointer_cast<Suelo>(mapa->getTile(this->getPosicion().Y,this->getPosicion().X))->setIsometric(false);*/
					//mapa->getTile(this->getPosicion())->aplicarTextura(driver);
					position2di moverse=this->getMovimiento();
					if(mapa->getTile(moverse.Y,moverse.X)->getTipo()==0 && mapa->getTile(moverse.Y,moverse.X)->getVinculado() ==NULL){
						//cout<<"Estoy en ("<<this->getPosition().X<<","<<this->getPosition().Y<<") Y me muevo a ("<<moverse.X<<","<<moverse.Y<<")"<<"y hay en el vector: "<<m_vecUnidades.size()<<endl;
						mapa->getTile(getPosition())->setVinculado(NULL);
						this->setPosition(this->getMovimiento());
						mapa->getTile(moverse)->setVinculado(this);
					}
					move=0;
					//mapa->setTile(this->getPosicion(),shared_ptr<IDibujable>(this));
				}else{
					this->Recovery();
				}
			}
		}else{
			position2di pos = this->getPosicion();
			if (pos.X >=0)
			{
				cout<<"##### HE MUERTO! POS: <"<<pos.X<<","<<pos.Y<<">"<<endl;
				//mapa->setTile(pos.Y,pos.X,shared_ptr<Suelo>( new Suelo(pos.X,pos.Y)));
				//std::dynamic_pointer_cast<Suelo>(mapa->getTile(pos.Y,pos.X))->setIsometric(false);
				//mapa->getTile(pos.Y,pos.X)->aplicarTextura(driver);
				mapa->getTile(pos)->setVinculado(NULL);
				//this->setPosition(-1,-1);
				setEliminar(true);

			}
			
			
		}
		this->calcular8Objetos(mapa);
		//return true;
}
