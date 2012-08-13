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
	std::size_t mRows;
	std::size_t mColumns;
	std::vector<Vertex*> mVertexes;
	Graph(std::size_t iRows, std::size_t iColumns, std::vector<Vertex*> iVertexes);

	/**
	 * Builds list of pointer to neighbour vertexes on each vertex based on the implicit geometry
	 * of the container.
	 * \see Readme.txt for explanations on adjacency mode
	 * \param AdjacencyMode iAdjacencyMode
	 */
	void buildAdjacencyLists(AdjacencyMode iAdjacencyMode);

	/**
	 * Displays graph internal status echoing to std::cout.
	 * \param DisplayMode iDisplayMode which vertex attribute to display
	 */
	void display(DisplayMode iDisplayMode);

private:

	/**
	 * For vertex identified by input index finds a list of neighbours
	 * (referring them with their index as well).
	 * These indexes will be translated to Vertex* later.
	 * \param std::size_t iIndex index of the vertex to process for neighbours
	 * \param AdjacencyMode iAdjacencyMode whether to get 4 or 8 neighbours
	 * \return std::forward_list<std::size_t>* list of neighbours indexes
	 */
	std::forward_list<std::size_t>* getNeighboursIndexes(std::size_t iIndex, AdjacencyMode iAdjacencyMode);
};
