#include "EspadachinRedes.h"
#include <boost/algorithm/string.hpp>
void EspadachinRedes::cargarPeso(){
	cout<<"cargando pesos"<<endl;
	vector<double> weights;
	std::string cadena,buf;
	vector<std::string> parser;
	ifstream myReadFile;
	myReadFile.open("redEspada.txt",ios::in);
	if (myReadFile.is_open()) {
		getline(myReadFile,cadena);
		stringstream ss(cadena);
		ss>>buf;
		boost::split(parser, buf, boost::is_any_of(","));
		for(std::string & weight : parser){
			weights.push_back(atof(weight.c_str()));
		}
		PutWeights(weights);

		myReadFile.close();
	}
	
}

EspadachinRedes::EspadachinRedes(int x,int y): CUnidadesAprendizaje(x,y){

	vision_range = 2;
	attack_range = 1;
	attack_value = 1;
	setTipo(4);
	cargarPeso();
}
