/*! 
 *  Functions that handle the actual solving of watercalc problem.
 *  -
 *  WaterCalc Homework - Advanced cpp programming
 *  Master in Computer Game Development, Verona, Italy
 *  -
 *  \author Andrea Casaccia
 *  \date 14 July 2012
 */

#pragma once

#include <forward_list>
#include <unordered_set>
#include "Vertex.h"
#include "Graph.h"

typedef std::forward_list<Vertex*> vertexList;
typedef std::forward_list<Vertex*>::iterator vertexListIterator;
typedef std::unordered_set<Vertex*> vertexSet;
typedef std::unordered_set<Vertex*>::iterator vertexSetIterator;

namespace Solver {

	/**
	 * Solves WaterCalc problem display results
	 * \see Graph.cpp for display results functions
	 * \see http://code.google.com/p/mgd-cpp-watercalc/ for problem description
	 * \see Readme.txt for a quick algorithm overview
	 * \param the Graph that models input data
	 */
	void solve(Graph &iGraph);

	/**
	 * Find the plateau of input vertex (the lowest height + capacity is chosen at each step),
	 * update its capacity and marks stable if needed.
	 * I call "plateau" a cluster of vertexes who have same height and capacity.
	 * \param Vertex* iVertex pointer to the current lowest capacity + height vertex
	 */
	void updatePlateauCapacity(Vertex* iVertex);

	/**
	 * Finds all neighbours which have same height and capacity as input Vertex.
	 * \param Vertex* iVertex pointer to the current lowest capacity + height vertex
	 * \param vertexSet* oPlateau set of Vertex* the plateau
	 */
	void getPlateau(Vertex* iVertex, vertexSet* oPlateau);

	/**
	 * Finds the border (or wall) of the plateau passed in.
	 * \param vertexSet* iPlateau the set identifiying the input plateau
	 * \param vertexSet* oWall the set of vertexes identifying the plateau surrounding wall
	 */
	void getWall(vertexSet* iPlateau, vertexSet* oWall);

	/**
	 * Finds the lowest (considering height and capacity) vertex in a set.
	 * \param vertexSet* iwall input set
	 * \param Vertex* pointer to the lowest vertex
	 */
	Vertex* getShortestWall(vertexSet* iWall);

	/**
	 * Uses shortest wall to determine id we need to update the capacities of input plateau.
	 * If shortest wall is stable, marks whole plateau as stable.
	 * \param vertexSet* ioPlateau plateau to update
	 * \param Vertex* iShortestWall the lowest border vertex of input plateau
	 */
	void updateCapacities(vertexSet* ioPlateau, Vertex* iShortestWall);

	/**
	 * Checks if vertexes have same height + capacity.
	 * \param Vertex* v1 pointer to the first vertex
	 * \param Vertex* v2 pointer to the second vertex
	 */
	bool equalHeightAndCapacity(Vertex* v1, Vertex* v2);
};