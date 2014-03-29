 
#include <stdlib.h>
#include <time.h>
#include "utils.h"
#include "CController.h"
#include "resource.h"
#include "CParams.h"





///////////////////////GLOBALS ////////////////////////////////////

char*			szApplicationName = "Smart Sweepers v1.0";
char*			szWindowClassName = "sweeper";


//The controller class for this simulation
CController*	g_pController	 = NULL; 

//create an instance of the parameter class.
CParams   g_Params;



using namespace std;


int main(int argc, char** argv)
{ 
		srand (3);
  		g_pController = new CController();
  		int cont=1000;
  		for(int i=0;i<cont;i++){
  			g_pController->Update();
  		}

  return 0;
}
