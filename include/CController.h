#ifndef CCONTROLLER_H
#define CCONTROLLER_H

//------------------------------------------------------------------------
//
//	Name: CController.h
//
//  Author: Mat Buckland 2002
//
//  Desc: Controller class for the 'Smart Sweeper' example 
//
//------------------------------------------------------------------------
#include <vector>
#include <sstream>
#include <string>
#include <fstream>
#include "CUnidadesAprendizaje.h"
#include "CGenAlg.h"
#include "utils.h"
#include "SVector2D.h"
#include "CParams.h"
#include "IDibujable.h"
#include "muro.h"
using namespace std;



class CController 
{

private:

	//storage for the population of genomes
	vector<SGenome>	     m_vecThePopulation;

	//and the minesweepers
  vector<CUnidadesAprendizaje*> m_vecUnidades;


	//pointer to the GA
	CGenAlg*		         m_pGA;

	int					         m_NumUnidades;

	int					         m_NumWeightsInNN;



	//stores the average fitness per generation for use 
	//in graphing.
	vector<double>		   m_vecAvFitness;

	//stores the best fitness per generation
	vector<double>		   m_vecBestFitness;

	//cycles per generation
	int					m_iTicks;

	//generation counter
	int					m_iGenerations;
	//0 transitable y 1 no transitable
	IDibujable* 				Matriz[MAPSIZE][MAPSIZE];

public:

	CController();

	~CController();
	CUnidadesAprendizaje* getUnidadPosicion(SVector2D pos);
	bool		Update();


};


#endif
	
