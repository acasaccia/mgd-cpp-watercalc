/*! 
 *  Stores information about the container as an undirected graph with adjacency lists at each vertex.
 *  Edges have 0 weight for connected nodes, infinite weight for not connected ones.
 *  A special vertex with 0 capacity and 0 height models the outside of the container, all water directed to it disappear.
 *  -
 *  WaterCalc Homework - Advanced cpp programming
 *  Master in Computer Game Development, Verona, Italy
 *  -
 *  \author Andrea Casaccia
 *  \date 14 July 2012
 */

#pragma once

#include <cstddef>
#include <vector>
#include <forward_list>
#include "Vertex.h"

enum AdjacencyMode {
	ADJACENCY4,
	ADJACENCY8
};

enum DisplayMode {
	HEIGHTS,
	CAPACITIES
};

class Graph {
public:
	uint_t mRows;
	uint_t mColumns;
	std::vector<Vertex*> mVertexes;
	Graph(uint_t iRows, uint_t iColumns, std::vector<Vertex*> iVertexes);
	void buildAdjacencyLists(AdjacencyMode iAdjacencyMode);
	void display(DisplayMode iDisplayMode);
private:
	std::forward_list<uint_t>* getNeighboursIndexes(uint_t iIndex, AdjacencyMode iAdjacencyMode);
};
