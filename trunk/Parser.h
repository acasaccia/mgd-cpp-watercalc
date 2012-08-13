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

	/**
	 * Takes a filename and try to load it and parse into a Graph data structure, managing
	 * parsing errors.
	 * \see Graph.cpp
	 * \param const std::string &iFilename the file to be parsed
	 * \return Graph* data structure containing parsed data
	 */
	Graph* parse(const std::string &iFilename);

	/**
	 * Takes a filename and try to load it returning an std::ifstream.
	 * Exit with proper messages on errors.
	 * \param const std::string &iFilename the file to be parsed
	 * \param std::ifstream &oParser the stream with file contents
	 */
	void load(const std::string &iFilename, std::ifstream &oParser);

	/**
	 * Parse the first line of the file and returns number of rows and columns.
	 * Exit with proper messages on errors.
	 * \param std::ifstream &iParser input stream
	 * \param std::size_t &oRows number of rows
	 * \param std::size_t &oColumns number of columns
	 */
	void parseHeader(std::ifstream &iParser, std::size_t &oRows, std::size_t &oColumns);

	/**
	 * Parses the rest of the file checking if we got the expected number of cells.
	 * Exit with proper messages on errors.
	 * \param std::ifstream &iParser input stream
	 * \param std::size_t &iRows number of rows
	 * \param std::size_t &iColumns number of columns
	 * \return Graph* pointer to the data structure
	 */
	Graph* parseData(std::ifstream &iParser, const std::size_t iRows, const std::size_t iColumns);

	/**
	 * Displays a message about the expected file format and exits application.
	 */
	void exitWrongInputFile();
};