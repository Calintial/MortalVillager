#include "CGenAlg.h"




//-----------------------------------constructor-------------------------
//
//	sets up the population with random floats
//
//-----------------------------------------------------------------------
CGenAlg::CGenAlg(int	  popsize,
                 double	MutRat,
                 double	CrossRat,
                 int	  numweights,std::string nombreCarpeta) :	m_iPopSize(popsize),
                                      m_dMutationRate(MutRat),
										                  m_dCrossoverRate(CrossRat),
										                  m_iChromoLength(numweights),
										                  m_dTotalFitness(1),
										                  m_cGeneration(0),
										                  m_iFittestGenome(0),
										                  m_dBestFitness(1),
										                  m_dWorstFitness(99999999),
										                  m_dAverageFitness(1)
{
	carpeta=nombreCarpeta;
	//initialise population with chromosomes consisting of random
	//weights and all fitnesses set to zero
	for (int i=0; i<m_iPopSize; ++i)
	{
		m_vecPop.push_back(SGenome());

		for (int j=0; j<m_iChromoLength; ++j)
		{
			m_vecPop[i].vecWeights.push_back(RandomClamped());
		}
	}
}


//---------------------------------Mutate--------------------------------
//
//	mutates a chromosome by perturbing its weights by an amount not 
//	greater than CParams::dMaxPerturbation
//-----------------------------------------------------------------------
void CGenAlg::Mutate(vector<double> &chromo)
{
	//traverse the chromosome and mutate each weight dependent
	//on the mutation rate
/*#ifdef DEBUG
	outfile.open("Genetic.txt", ios::app);
			if (outfile.is_open()){
				outfile << "Ha empezado aqui"<<endl;
			}
#endif*/
	for (int i=0; i<chromo.size(); ++i)
	{
		//do we perturb this weight?
		double ran=RandFloat();
		if (ran < m_dMutationRate)
		{
			//add or subtract a small value to the weight
/*#ifdef DEBUG
			if (outfile.is_open())
			{
				outfile<< "Ran es: "<<ran<<endl;
				outfile << "Chromosoma mutado: " << chromo[i];
			}
#endif	*/	
			chromo[i] += (RandomClamped() * CParams::dMaxPerturbation);
/*#ifdef DEBUG
			if (outfile.is_open())
			{
				outfile << " ahora:  " << chromo[i]<<endl;
			}
#endif*/
		}
	}

	/*if (outfile.is_open()){
				outfile << "Ha terminado"<<endl;
				outfile.close();
	}*/
			
}

//----------------------------------GetChromoRoulette()------------------
//
//	returns a chromo based on roulette wheel sampling
//
//-----------------------------------------------------------------------
SGenome CGenAlg::GetChromoRoulette()
{
	//generate a random number between 0 & total fitness count
	double Slice = (double)(RandFloat() * m_dTotalFitness);

	//this will be set to the chosen chromosome
	SGenome TheChosenOne;
	
	//go through the chromosones adding up the fitness so far
	double FitnessSoFar = 1;
	
	for (int i=0; i<m_iPopSize; ++i)
	{
		FitnessSoFar += m_vecPop[i].dFitness;
		
		//if the fitness so far > random number return the chromo at 
		//this point
		if (FitnessSoFar >= Slice)
		{
			/*outfile.open("Genetic.txt", ios::app);
			if (outfile.is_open())
			{
				outfile << "Mejor fitness: " << m_vecPop[i].dFitness << endl;
			}
			outfile.close();*/
			TheChosenOne = m_vecPop[i];

      break;
		}
		
	}

	return TheChosenOne;
}
	
//-------------------------------------Crossover()-----------------------
//	
//  given parents and storage for the offspring this method performs
//	crossover according to the GAs crossover rate
//-----------------------------------------------------------------------
void CGenAlg::Crossover(const vector<double> &mum,
                        const vector<double> &dad,
                        vector<double>       &baby1,
                        vector<double>       &baby2)
{
	
/*#ifdef DEBUG
	outfile.open("Genetic.txt", ios::app);
#endif*/
	
		//just return parents as offspring dependent on the rate
		//or if parents are the same
		if ( (RandFloat() > m_dCrossoverRate) || (mum == dad)) 
		{
			baby1 = mum;
			baby2 = dad;
/*#ifdef DEBUG
			if (outfile.is_open())
			{
				outfile<< "no Crossover"<<endl;
			}
#endif*/
			return;
		}

		//determine a crossover point
		int cp = RandInt(0, m_iChromoLength - 1);
/*#ifdef DEBUG
		if (outfile.is_open())
			{
		
			outfile << "CP : "<<cp<<endl;
				outfile << "		MUM:" << endl;

				for (double d : mum){
					outfile << d << ",";
				}
				outfile << endl;
				outfile << "		DAD:" << endl;
				for (double d : dad){
					outfile << d << ",";
				}
				outfile << endl;
			}
#endif*/
		//create the offspring
		for (int i=0; i<cp; ++i)
		{
			baby1.push_back(mum[i]);
			baby2.push_back(dad[i]);
		}

		for (int i=cp; i<mum.size(); ++i)
		{
			baby1.push_back(dad[i]);
			baby2.push_back(mum[i]);
		}
/*#ifdef DEBUG
		if (outfile.is_open())
			{
				outfile << "		BABY1:" << endl;
				for (double d : baby1){
					outfile << d << ",";
				}
				outfile << endl;
				outfile << "		BABY2:" << endl;
				for (double d : baby2){
					outfile << d << ",";
				}
				outfile << endl;
			}
	outfile.close();
#endif
*/
	return;
}

//-----------------------------------Epoch()-----------------------------
//
//	takes a population of chromosones and runs the algorithm through one
//	 cycle.
//	Returns a new population of chromosones.
//
//-----------------------------------------------------------------------
vector<SGenome> CGenAlg::Epoch(vector<SGenome> &old_pop,int m_iGenerations)
{
	outfile.open("GeneticMovimientos.txt", ios::app);
	if (outfile.is_open())
	{
		outfile << "####################################################### CGenAlg::Epoch::219 " << m_iGenerations << "   ######################################################"<<endl
			;
	}

	outfile.close();

	//assign the given population to the classes population
  m_vecPop = old_pop;

  //reset the appropriate variables
  Reset();

  //sort the population (for scaling and elitism)
  sort(m_vecPop.begin(), m_vecPop.end());

  //calculate best, worst, average and total fitness
	CalculateBestWorstAvTot();
  
  //create a temporary vector to store new chromosones
	vector <SGenome> vecNewPop;

	//Now to add a little elitism we shall add in some copies of the
	//fittest genomes. Make sure we add an EVEN number or the roulette
  //wheel sampling will crash
	
	GrabNBest(CParams::iNumElite, CParams::iNumCopiesElite, vecNewPop);
	if(vecNewPop.size() == 0){
		cout<<"No hay elite!"<<endl;
		throw;
	}
	
	

	//now we enter the GA loop
	
	//repeat until a new population is generated
	while (vecNewPop.size() < m_iPopSize)
	{
		//grab two chromosones
		SGenome mum = GetChromoRoulette();
		SGenome dad = GetChromoRoulette();

		//create some offspring via crossover
		vector<double>		baby1, baby2;

		Crossover(mum.vecWeights, dad.vecWeights, baby1, baby2);

		//now we mutate
		Mutate(baby1);
		Mutate(baby2);

		//now copy into vecNewPop population
		if(vecNewPop.size() < m_iPopSize)
			vecNewPop.push_back(SGenome(baby1, 1));
		if(vecNewPop.size() < m_iPopSize)
			vecNewPop.push_back(SGenome(baby2, 1));
	}

	//finished so assign new pop back into m_vecPop
	m_vecPop = vecNewPop;
	outfile.open("GeneticMovimientos.txt", ios::app);
	if (outfile.is_open())
	{
		outfile << "#########################################################################FinalCGenAlg::Epoch####################################"<<endl;
	}

	outfile.close();
	return m_vecPop;
}


//-------------------------GrabNBest----------------------------------
//
//	This works like an advanced form of elitism by inserting NumCopies
//  copies of the NBest most fittest genomes into a population vector
//--------------------------------------------------------------------
void CGenAlg::GrabNBest(int	            NBest,
                        const int	      NumCopies,
                        vector<SGenome>	&Pop)
{
  //add the required amount of copies of the n most fittest 
	//to the supplied vector
	//while(NBest--)
	//{
	//	for (int i=0; i<NumCopies; ++i)
	//	{
	int mejorFitness = 0;
	int mejor = -1;
	for (int i = 0; i < m_iPopSize; ++i)
	{
		if(m_vecPop[i].dFitness > mejorFitness)
		{
			mejorFitness = m_vecPop[i].dFitness;
			mejor = i;
		}
	}

	if(mejorFitness > 0){
		Pop.push_back(m_vecPop[mejor]);
	  //}
	}else{
		cout<<"ESTO HA PETADO"<<endl;
	}
//	}
}

//-----------------------CalculateBestWorstAvTot-----------------------	
//
//	calculates the fittest and weakest genome and the average/total 
//	fitness scores
//---------------------------------------------------------------------
void CGenAlg::CalculateBestWorstAvTot()
{
	std::string excel=carpeta+"/Excel.txt";
	m_dTotalFitness = 1;
	
	double HighestSoFar = 1;
	double LowestSoFar  = 9999999;
	
	for (int i=0; i<m_iPopSize; ++i)
	{
		//update fittest if necessary
		if (m_vecPop[i].dFitness > HighestSoFar)
		{
			HighestSoFar	 = m_vecPop[i].dFitness;
			
			m_iFittestGenome = i;

			m_dBestFitness	 = HighestSoFar;
		}
		
		//update worst if necessary
		if (m_vecPop[i].dFitness < LowestSoFar)
		{
			LowestSoFar = m_vecPop[i].dFitness;
			
			m_dWorstFitness = LowestSoFar;
		}
		
		m_dTotalFitness	+= m_vecPop[i].dFitness;
	
		
	}//next chromo
	

	m_dAverageFitness = m_dTotalFitness / m_iPopSize;
	double mediana= m_vecPop[m_iPopSize/2].dFitness;
	outfile.open("Genetic.txt", ios::app);
			if (outfile.is_open())
			{
				outfile << "##################################################CGenAlg::CalculateBestWorstAvTot############################################"<<endl;
				outfile << "Mejor fitness: "<<m_dBestFitness<<endl;
				outfile << "Peor fitness: "<<m_dWorstFitness<<endl;
				outfile << "Average Fitness: "<<m_dAverageFitness<<endl;
			}
			outfile.close();

 	outfile.open(excel, ios::app);
 			if (outfile.is_open())
 			{
 				
 				outfile <<m_dBestFitness<<",";
 				outfile <<m_dWorstFitness<<",";
 				outfile<<m_dAverageFitness<<",";
 				outfile <<mediana<<endl;
 			}
 	outfile.close();
}

//-------------------------Reset()------------------------------
//
//	resets all the relevant variables ready for a new generation
//--------------------------------------------------------------
void CGenAlg::Reset()
{
	m_dTotalFitness		= 1;
	m_dBestFitness		= 1;
	m_dWorstFitness		= 9999999;
	m_dAverageFitness	= 1;
}

