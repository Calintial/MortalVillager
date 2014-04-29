#ifndef SGENOME_H
#define SGENOME_H

#include <vector>
#include <algorithm>
#include <iostream>
#include <fstream>
#include "utils.h"
#include "CParams.h"

using namespace std;

//-----------------------------------------------------------------------
//
//	create a structure to hold each genome
//-----------------------------------------------------------------------
class SGenome
{
public:
	vector <double>	vecWeights;

	double          dFitness;

	SGenome():dFitness(0){}

	SGenome( vector <double> w, double f): vecWeights(w), dFitness(f){}

	//overload '<' used for sorting
	friend bool operator<(const SGenome& lhs, const SGenome& rhs)
	{
		return (lhs.dFitness < rhs.dFitness);
	}
	friend bool operator==(const SGenome &genomeahora,const SGenome &genome)
	{
		SGenome antiguo=genome;
		SGenome ahora=genomeahora;
		sort(ahora.vecWeights.begin(), ahora.vecWeights.end());
		sort(antiguo.vecWeights.begin(),antiguo.vecWeights.end());
		for(int i=0;i<ahora.vecWeights.size();i++){
			if(antiguo.vecWeights[i]!=ahora.vecWeights[i]){
				return false;
			}
		}
		return true;
	}

};
#endif