#include "ObjetosCercanos.h"
vector<double> ObjetosCercanos::getInputs(int x,int y){
	
	vector<double> inputs;
		switch(tipo){
			case 0:
					inputs.push_back(1);
					inputs.push_back(0);
					inputs.push_back(0);
					inputs.push_back(0);
					inputs.push_back(0);
					break;
			case 1:	inputs.push_back(0);
					inputs.push_back(1);
					inputs.push_back(0);
					inputs.push_back(0);
					inputs.push_back(0);	
					break;
			case 2: inputs.push_back(0);
					inputs.push_back(0);
					inputs.push_back(1);
					inputs.push_back(0);
					inputs.push_back(0);
					break;
			case 3:
					inputs.push_back(0);
					inputs.push_back(0);
					inputs.push_back(0);
					inputs.push_back(1);
					inputs.push_back(0);
					break;
			case 4:
					inputs.push_back(0);
					inputs.push_back(0);
					inputs.push_back(0);
					inputs.push_back(0);
					inputs.push_back(1);
					break;
		}
		inputs.push_back((posicion.X-x)/2);
		inputs.push_back((posicion.Y-y)/2);
		inputs.push_back(vida/100);
		//2->1
		//1-<0.5
		//0 ->0
		//-1 -> -0.5
		//-2-> -1
	return inputs;
}
