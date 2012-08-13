/*! 
 *  Functions to handle loading of the input file with error checking
 *  -
 *  WaterCalc Homework - Advanced cpp programming
 *  Master in Computer Game Development, Verona, Italy
 *  -
 *  \author Andrea Casaccia
 *  \date 14 July 2012
 */

#include "Parser.h"
#include <iostream>

namespace Parser {

	Graph* parse(const std::string &iFilename) {

		std::ifstream inputFile;
		load(iFilename, inputFile);

		std::size_t rows = 0, columns = 0;
		parseHeader(inputFile, rows, columns);

		Graph* container = parseData(inputFile, rows, columns);
		return container;
	}

	void load(const std::string &iFilename, std::ifstream &oParser) {

		oParser.open(iFilename.c_str());

		if(!oParser.is_open()) {
			std::cout << "Error reading input file:" << std::endl << "Cannot open " << iFilename << std::endl;
			exit(EXIT_FAILURE);
		}
	}

	void parseHeader(std::ifstream &iParser, std::size_t &oRows, std::size_t &oColumns) {

		iParser >> oRows;
		if (iParser.fail()) {
			std::cout << "Error reading input file: " << std::endl;
			exitWrongInputFile();
		}

		iParser >> oColumns;
		if (iParser.fail()) {
			std::cout << "Error reading input file: " << std::endl;
			exitWrongInputFile();
		}

		if (oRows == 0 || oColumns == 0) {
			std::cout << "Error reading input file:" << std::endl;
			std::cout << "Wrong header, need to specify number of rows and columns as positive integers." << std::endl;
			exitWrongInputFile();
		}

		std::cout << "Parsed header: expecting " << oRows << " rows and " << oColumns << " columns." << std::endl;
	}

	Graph* parseData(std::ifstream &iParser, const std::size_t iRows, const std::size_t iColumns) {

		std::vector<Vertex*>* vertexes = new std::vector<Vertex*>();
		vertexes->reserve(iRows * iColumns);

		capacity_type buffer = 0;

		std::size_t currentRow = 0;
		std::size_t currentColumn = 0;
	
		while (iParser >> buffer) {
			vertexes->push_back(new Vertex(buffer));
			currentColumn++;
			currentColumn %= iColumns;
			if (currentColumn == 0) {
				currentRow++;
			}
		}

		if (!iParser.eof()) {
			std::cout << "Error reading input file at row " << currentRow+1 << ", column " << currentColumn + 1 << std::endl;
			exitWrongInputFile();
		}

		if (vertexes->size() != iRows * iColumns ) {
			std::cout << "Error reading input file: expecting " << iRows * iColumns << " elements, but found " << vertexes->size() << std::endl;
			exitWrongInputFile();
		}

		std::cout << "Parsed data without errors."  << std::endl;

		return new Graph(iRows, iColumns, *vertexes);
	}

	void exitWrongInputFile() {
		std::cout << "Expected input file format:" << std::endl;
		std::cout << std::endl;
		std::cout << "rows columns" << std::endl;
		std::cout << "element(0,0)\t...\telement(0,columns)" << std::endl;
		std::cout << "...\t\t...\t..." << std::endl;
		std::cout << "element(rows,0)\t...\telement(rows,columns)" << std::endl;
		exit(EXIT_FAILURE);
	}

}