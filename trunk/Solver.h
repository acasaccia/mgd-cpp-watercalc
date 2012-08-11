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

#include <limits>
#include <cstddef>
#include <set>
#include "Vertex.h"
#include "Graph.h"

typedef std::forward_list<Vertex*> vertexList;
typedef std::forward_list<Vertex*>::iterator vertexListIterator;
typedef std::set<Vertex*> vertexSet;
typedef std::set<Vertex*>::iterator vertexSetIterator;

namespace Solver {
	void solve(Graph &iGraph);
	void updatePlateauCapacity(Vertex* iVertex);
	void walkNeighboursAndAddToPlateau(Vertex* iVertex, vertexSet* ioPlateau);
	void walkPlateauAndGetWalls(vertexSet* iPlateau, vertexSet* ioWall);
	Vertex* getShortestWall(vertexSet* iWall);
	void updateCapacities(vertexSet* iPlateau, Vertex* shortestWall);
	bool equalHeightAndCapacity(Vertex* v1, Vertex* v2);
};