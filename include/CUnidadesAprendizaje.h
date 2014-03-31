#ifndef CMINESWEEPER_H
#define CMINESWEEPER_H
#define MAPSIZE 20
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
#include "ObjetosCercanos.h"
#include <fstream>
using namespace std;

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
	int 			m_ataque;
	int 			m_moveX;
	int 			m_moveY;
	int 			m_ataqueX;
	int 			m_ataqueY;
	vector<ObjetosCercanos> m_vObjetosCerca;


public:
	
	int getAtaque(){return m_ataque;}
	SVector2D getAtaqueMovimiento(){return  SVector2D(m_ataqueX,m_ataqueY);}
	SVector2D getMovimiento(){return  SVector2D(m_moveX,m_moveY);}
	void setAtaque(int x, int y){m_ataqueX=x;m_ataqueY=y;}
	void setMovimiento(int x, int y){m_moveX=x;m_moveY=y;}
	double getLife(){return m_life;}
	CUnidadesAprendizaje(IDibujable* Matriz[][MAPSIZE],int i);
	
	//updates the ANN with information from the sweepers enviroment
	bool			Update(IDibujable* Matriz[][MAPSIZE]);


	void			Reset(IDibujable* Matriz[][MAPSIZE]);
  	vector<ObjetosCercanos> getVectorObjetos(){return m_vObjetosCerca;};

	//-------------------accessor functions
	SVector2D	Position()const{return m_vPosition;}
	void setPosition(SVector2D pos){m_vPosition=pos;}
	void			IncrementFitness(){m_dFitness+=0.1;}

	double		Fitness()const{return m_dFitness;}
  
  void      PutWeights(vector<double> &w){m_ItsBrain.PutWeights(w);}

  int       GetNumberOfWeights()const{return m_ItsBrain.GetNumberOfWeights();}
  void Pintar(IVideoDriver*,int,int);
  void aplicarTextura(IVideoDriver* driver);
  bool isTransitable(){}
  void calcular8Objetos(IDibujable* [][MAPSIZE]);
	SVector2D mayorMovimiento(int arriba, int abajo, int izquierda, int derecha);
};


#endif

	
	