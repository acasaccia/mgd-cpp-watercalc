/*! 
 *  Namespaced functions to handle command line args
 *  -
 *  WaterCalc Homework - Advanced cpp programming
 *  Master in Computer Game Development, Verona, Italy
 *  -
 *  \author Andrea Casaccia
 *  \date 14 July 2012
 */

#pragma once

#include <vector>
#include <string>

namespace Arguments {

	static const char* HELP = "--help";
	static const char* ADJACENCY4 = "-adjacency=4";
	static const char* ADJACENCY8 = "-adjacency=8";

	void check(std::vector<std::string> &ioArgs);
	void displayHelp();
	void exitWrongArgs();
	void exitDisplayHelp();
};