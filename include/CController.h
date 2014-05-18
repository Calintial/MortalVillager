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
#include "MapaAprendizaje.h"
#include <ctime>
#include <boost/algorithm/string.hpp>
#include <iomanip>
using namespace std;

const int TILE_W	= 32;
const int TILE_H = 32;

class CController 
{

private:

	//storage for the population of genomes
	vector<SGenome>	     m_vecThePopulation;

	//and the minesweepers
  vector<shared_ptr<CUnidadesAprendizaje>> m_vecUnidades;

	int					         m_NumUnidades;
	//pointer to the GA
	CGenAlg*		         m_pGA;
	//cycles per generation
	int					m_iTicks;
		//generation counter
	int					m_iGenerations;


	int					         m_NumWeightsInNN;



	//stores the average fitness per generation for use 
	//in graphing.
	vector<double>		   m_vecAvFitness;

	//stores the best fitness per generation
	vector<double>		   m_vecBestFitness;




	//0 transitable y 1 no transitable
	MapaAprendizaje* 				matriz;

	IrrlichtDevice* device;
	video::IVideoDriver* driver;

	shared_ptr<Unidades> unidad_seleccionada;

	IGUIFont* font;
	void guardarPesos();

public:
	time_t t;
	std::string versionGit;
	std::ofstream outfile;
	std::string nombreCarpeta;
	std::string red;
	vector<double > prueba;
	CController(IrrlichtDevice* dev);

	~CController();
	shared_ptr<CUnidadesAprendizaje>  getUnidadPosicion(position2di pos);
	//bool		Update();
	bool tickRedNeuronalUnidad(shared_ptr<CUnidadesAprendizaje> unidad, int i);
	bool		tickRedNeuronal();
	bool		redNeuronal();
	bool		genetico();

	void Pintar();
	
	void generarMapa(int tipoMapa);
	bool OnEvent(const SEvent& event);
	void PintarInformacionUnidad();
void ponerWeightFichero(std::string fichero);
};


#endif
	
