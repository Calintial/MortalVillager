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
#include "EspadachinRedes.h"
#include "CGenAlg.h"
#include "utils.h"
#include "SVector2D.h"
#include "CParams.h"
#include "IDibujable.h"
#include "muro.h"
#include "gameEngine.h"
#include <fstream>
#define MAPSIZE 20
using namespace std;

const int TILE_W	= 32;
const int TILE_H = 32;

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

	IrrlichtDevice* device;
	video::IVideoDriver* driver;

	Unidades* unidad_seleccionada;

	IGUIFont* font;

public:
	std::ofstream outfile;
	CController(IrrlichtDevice* dev);

	~CController();
	CUnidadesAprendizaje* getUnidadPosicion(SVector2D pos);
	bool		Update();

	void Pintar();
	void generarMapa();
	void modificarUnidad(CUnidadesAprendizaje* unidad);
	bool OnEvent(const SEvent& event);
	void PintarInformacionUnidad();

};


#endif
	
