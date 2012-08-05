/*! 
 *  Application entry point
 *  -
 *  WaterCalc Homework - Advanced cpp programming
 *  Master in Computer Game Development, Verona, Italy
 *  -
 *  \author Andrea Casaccia
 *  \date 14 July 2012
 */

#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include "Arguments.h"
#include "Parser.h"
#include "Graph.h"
#include "Solver.h"

int main(int argc, char **argv) {

	std::clock_t begin = clock();

	std::vector<std::string> args(argv, argv + argc);

	Arguments::check(args);

	if (args[1] == Arguments::HELP)
		Arguments::exitDisplayHelp();
	
	Graph* graph = Parser::parse(args[1]);

	if (args.size() == 3 && args[2] == Arguments::ADJACENCY8)
		graph->buildAdjacencyLists(ADJACENCY8);
	else
		graph->buildAdjacencyLists(ADJACENCY4);

	Solver::solve(*graph);

	clock_t end = clock();
	double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
	std::cout << std::endl << "Done [Elapsed: " << elapsed_secs << "\"]" << std::endl;

	return EXIT_SUCCESS;
}