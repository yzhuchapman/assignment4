#include "Registrar.h"

#include <iostream>
#include <string>

using namespace std;

int main(int argc, char ** argv)
{
	Registrar* registrar;
	if(argc == 2)
	{
		registrar = new Registrar(argv[1]);
		registrar->runSimulation();
	}
	return 0;
}