#ifndef CUNIDADESAPRENDIZAJE_H
#define CUNIDADESAPRENDIZAJE_H
#define MAPSIZE 200

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
#include "Unidades.h"
#include "ObjetosCercanos.h"
#include <fstream>
using namespace std;

class CUnidadesAprendizaje :  public Unidades
{

private:

  //the minesweeper's neural net
  CNeuralNet		m_ItsBrain;


	//the sweeper's fitness score 
	double			m_dFitness;
	int 			m_moveX;
	int 			m_moveY;
	int 			m_ataqueX;
	int 			m_ataqueY;
	//its position in the world
	int 			move;
	int 			m_ataque;


	vector<ObjetosCercanos> m_vObjetosCerca;


public:
	std::ofstream outfile;
	int getMover(){return move;};
	int getAtaque(){return m_ataque;}
	position2di getAtaqueMovimiento(){return  position2di(m_ataqueX,m_ataqueY);}
	position2di getMovimiento(){return  position2di(m_moveX,m_moveY);}
	void setAtaque(int x, int y){m_ataqueX=x;m_ataqueY=y;}
	void setMovimiento(int x, int y){m_moveX=x;m_moveY=y;}
	CUnidadesAprendizaje(int x, int y);
	
	//updates the ANN with information from the sweepers enviroment
	bool			Update(IDibujable* Matriz[][MAPSIZE]);


	void			Reset();
  	vector<ObjetosCercanos> getVectorObjetos(){return m_vObjetosCerca;};

	//-------------------accessor functions


	double		Fitness()const{return m_dFitness;}
  
  void      PutWeights(vector<double> &w){m_ItsBrain.PutWeights(w);}

  int       GetNumberOfWeights()const{return m_ItsBrain.GetNumberOfWeights();}
  void Pintar(IVideoDriver*,int,int);
  void aplicarTextura(IVideoDriver* driver);
  virtual void TexturaSeleccionada(IVideoDriver* driver,bool);
  void calcular8Objetos(IDibujable* [][MAPSIZE]);

	position2di mayorMovimiento(double arriba, double abajo, double izquierda, double derecha,IDibujable* Matriz[][MAPSIZE]);
 void IncrementFitness(CUnidadesAprendizaje *atacado,int danyo,double max_fitness);
void setFitness(double fitness){m_dFitness=fitness;};

	


};


#endif

	
	
