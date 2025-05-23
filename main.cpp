#include "Simulation.h"
#include <iostream>

int main(int argc, char* argv[]){
	if(argc < 2){
		std::cerr << "Usage: " << argv[0] << " <maze_file>" << std::endl;
		return 1;
	}
	Simulation sim(argv[1]);
	sim.run();
	return 0;
}

