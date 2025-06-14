#include "Simulation.h"
#include <iostream>
#include <stdexcept>

int main(int argc, char* argv[]){
	try{
		if(argc < 2){
			throw std::invalid_argument("Usage: " + std::string(argv[0]) + " <maze_file>");
		}
		Simulation sim(argv[1]);
		sim.run();
	}catch(const std::exception& e){
		std::cerr << "Error: " << e.what() << std::endl;
		return 1;
	}
	return 0;
}

