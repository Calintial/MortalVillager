#include <iostream>
#include <vector>
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>
#include "include/gnuplot_i.hpp"

using namespace std;
using namespace boost;

void leerArchivo();


vector<double> mejor;
vector<double> peor;
vector<double> media;
vector<double> mediana;
vector<int> iteraciones;

int main(int argc, char* argv[])
{

    try
    {
        Gnuplot graf = Gnuplot("lines");

        leerArchivo();
        
        graf.reset_all();
        graf.set_grid();
        graf.set_style("lines").plot_xy(iteraciones,mejor,"Fitness"); 
        while(true)
        {
            leerArchivo();
            graf.reset_plot();
            graf.remove_tmpfiles();
            graf.set_grid();
            graf.set_style("lines");
            graf.plot_xy(iteraciones,mejor,"Mejor fitness"); 
            graf.plot_xy(iteraciones,peor,"Peor fitness"); 
            graf.plot_xy(iteraciones,media,"Media fitness"); 
            graf.plot_xy(iteraciones,mediana,"Mediana fitness"); 
            sleep(10);
        }
    }
    catch (GnuplotException ge)
    {
        cout << ge.what() << endl;
    }


    return 0;
}

void leerArchivo()
{
    mejor.clear();
    peor.clear();
    media.clear();
    mediana.clear();
    iteraciones.clear();
    
    ifstream myReadFile;
    myReadFile.open("../bin/Excel.txt");
    string output;
    vector <string> fields;
    int cont = 1;

    if (myReadFile.is_open()) 
    {
        while (!myReadFile.eof()) 
        {
            myReadFile >> output;
            split( fields, output, is_any_of( "," ) );

            mejor.push_back(boost::lexical_cast<double>(fields.at(0)));
            peor.push_back(boost::lexical_cast<double>(fields.at(1)));
            media.push_back(boost::lexical_cast<double>(fields.at(2)));
            mediana.push_back(boost::lexical_cast<double>(fields.at(3)));
            iteraciones.push_back(cont);

            cont++;
        }
    }
    myReadFile.close();
}