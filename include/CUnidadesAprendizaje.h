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
#include "C2DMatrix.h"
#include "SVector2D.h"
#include "CParams.h"

using namespace std;


class CUnidadesAprendizaje.h
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

public:


	CUnidadesAprendizaje();
	
	//updates the ANN with information from the sweepers enviroment
	bool			Update(vector<SVector2D> &mines);


	void			Reset();
  

	//-------------------accessor functions
	SVector2D	Position()const{return m_vPosition;}

	void			IncrementFitness(){++m_dFitness;}

	double		Fitness()const{return m_dFitness;}
  
  void      PutWeights(vector<double> &w){m_ItsBrain.PutWeights(w);}

  int       GetNumberOfWeights()const{return m_ItsBrain.GetNumberOfWeights();}
};


#endif

	
	