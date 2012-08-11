/*! 
 *  Functions to handle command line args
 *  -
 *  WaterCalc Homework - Advanced cpp programming
 *  Master in Computer Game Development, Verona, Italy
 *  -
 *  \author Andrea Casaccia
 *  \date 14 July 2012
 */

#include "Arguments.h"
#include <iostream>

namespace Arguments {

	void check(std::vector<std::string> &ioArgs) {
		if (ioArgs.size() < 2 || ioArgs.size() > 3) {
			exitWrongArgs();
		}
		if (ioArgs.size() == 3) {
			if (ioArgs[2] != ADJACENCY4 && ioArgs[2] != ADJACENCY8) {
				exitWrongArgs();
			}
		}
	}

	void displayHelp() {
		std::cout << "usage: C:\\>WaterCalc.exe [inputfile] [-adjacency=4|8] " << std::endl;
		std::cout << "-adjacency parameter is optional default is 4-way adjacency." << std::endl;
	}

	void exitWrongArgs() {
		displayHelp();
		exit(EXIT_FAILURE);
	}

	void exitDisplayHelp() {
		displayHelp();
		exit(EXIT_SUCCESS);
	}

}