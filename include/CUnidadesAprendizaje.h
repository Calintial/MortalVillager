#ifndef CMINESWEEPER_H
#define CMINESWEEPER_H

//------------------------------------------------------------------------
//
//	Name: CMineSweeper.h
//
//  Author: Mat Buckland 2002
//
//  Desc: Class to create a minesweeper object 
//
//------------------------------------------------------------------------
#include <vector>
#include <math.h>
#include "CNeuralNet.h"
#include "utils.h"
#include "SVector2D.h"
#include "CParams.h"
#include "IDibujable.h"

using namespace std;

struct ObjetosCerca{
	//0:Aldeano, 1:Arquero,2:Espadachin,3:Lancero,4:Obstaculo
	int tipo;

	double vida;

	SVector2D posicion;
};
class CUnidadesAprendizaje :  public IDibujable
{

private:

  //the minesweeper's neural net
  CNeuralNet		m_ItsBrain;

	//its position in the world
	SVector2D		m_vPosition;

	//its rotation (surprise surprise)
	double 			m_life;

	//the sweeper's fitness score 
	double			m_dFitness;

	int 			m_move;

	int 			m_ataque;
	vector<ObjetosCerca> m_vObjetosCerca;

public:


	CUnidadesAprendizaje(IDibujable* Matriz[][MAPSIZE]);
	
	//updates the ANN with information from the sweepers enviroment
	bool			Update(vector<ObjetosCerca> m_vObjetosCerca);


	void			Reset();
  	vector<ObjetosCerca> getVectorObjetos(){return m_vObjetosCerca;};

	//-------------------accessor functions
	SVector2D	Position()const{return m_vPosition;}

	void			IncrementFitness(){++m_dFitness;}

	double		Fitness()const{return m_dFitness;}
  
  void      PutWeights(vector<double> &w){m_ItsBrain.PutWeights(w);}

  int       GetNumberOfWeights()const{return m_ItsBrain.GetNumberOfWeights();}
  void Pintar(IVideoDriver*,int,int){}
  void aplicarTextura(IVideoDriver* driver){}
  bool isTransitable(){}

};


#endif

	
	