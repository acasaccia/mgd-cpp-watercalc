/*! 
 *  Functions to handle loading of the input file with error checking
 *  -
 *  WaterCalc Homework - Advanced cpp programming
 *  Master in Computer Game Development, Verona, Italy
 *  -
 *  \author Andrea Casaccia
 *  \date 14 July 2012
 */

#pragma once

#include <fstream>
#include <string>
#include "Graph.h"
#include "Vertex.h"

namespace Parser {
	Graph* parse(const std::string &iFilename);
	void load(const std::string &iFilename, std::ifstream &oParser);
	void parseHeader(std::ifstream &iParser, uint &oRows, uint &oColumns);
	Graph* parseData(std::ifstream &iParser, const uint iRows, const uint iColumns);
	void exitWrongInputFile();
};