/*! 
 *  Functions that handle the actual solving of watercalc problem.
 *  -
 *  WaterCalc Homework - Advanced cpp programming
 *  Master in Computer Game Development, Verona, Italy
 *  -
 *  \author Andrea Casaccia
 *  \date 14 July 2012
 */

#include "Solver.h"
#include <vector>
#include <iostream>

namespace Solver {

	// Class used to sort an stl container of Vertex* with stable vertexes first
	class StableFirst {
		public:
		bool operator()(Vertex* v1, Vertex* v2)
		{
			return static_cast<int>(v1->stable) > static_cast<int>(v2->stable);
		}
	};

	// Class used to sort an stl container of Vertex* with lowest capacity + height first
	class LessHeightAndCapacity {
		public:
		bool operator()(Vertex* v1, Vertex* v2)
		{
			return v1->height + v1->capacity < v2->height + v2->capacity;
		}
	};

	// Checks if vertexes have same height + capacity.
	bool equalHeightAndCapacity (Vertex* v1, Vertex* v2) {
		return v1->height + v1->capacity == v2->height + v2->capacity;
	}

	void solve(Graph &iGraph) {

		vertexList* vertexesQueue = new vertexList(iGraph.mVertexes.begin(), iGraph.mVertexes.end());

		// After parsing the only node for which we have stable status is the sink. We
		// iterate from it, climbing up the borders of the container and moving through
		// the higher vertexes we find. For each of these vertexes we can state they have
		// 0 capacity and stable status as their content directly goes into the sink.
		// This way we easily restrict search space for the second part of the algorithm.
		while (!vertexesQueue->empty()) {
			vertexesQueue->sort(StableFirst());
			Vertex* current = vertexesQueue->front();
			if (!current->stable) {
				break;
			}
			vertexesQueue->pop_front();
			for ( vertexListIterator neighbourIt = current->neighbours.begin(); neighbourIt != current->neighbours.end(); ++neighbourIt) {
				if ( current->height <= (*neighbourIt)->height ) {
					(*neighbourIt)->capacity = 0;
					(*neighbourIt)->stable = true;
				}
			}
		}

		std::cout << std::endl << "After preprocessing:" << std::endl;
		iGraph.display(CAPACITIES);

		// Processing phase:
		// 1 Sort the unstable vertexes by height plus capacity
		// 2 Select the lowest as current
		// 3 Find the cluster of neighbours with the same height and capacity as current
		//   if they exists (I refer to these vertexes as "plateau").
		// 4 Find the wall of the plateau (the border vertexes)
		// 5 Shortest vertex of the wall determines if selected plateau's capacity has to
		//   be incremented.
		// 6 If shortest wall is stable, mark all plateau as stable (there is no way
		//   its capacity can further increase).
		while (!vertexesQueue->empty()) {
			vertexesQueue->sort(LessHeightAndCapacity());
			Vertex* current = vertexesQueue->front();
			if (current->stable) {
				vertexesQueue->pop_front();
			} else {
				updatePlateauCapacity(current);
			}
		}

		delete vertexesQueue;

		std::cout << std::endl << "Container capacities:" << std::endl;
		iGraph.display(CAPACITIES);

	}

	// Find the plateau of input vertex (the lowest height + capacity is chosen at each step),
	// update its capacity and marks stable if needed.
	// I call "plateau" a cluster of vertexes who have same height and capacity.
	void updatePlateauCapacity(Vertex* iVertex) {
		
		vertexSet* plateau = new vertexSet();
		getPlateau(iVertex, plateau);
		
		vertexSet* wall = new vertexSet();
		getWall(plateau, wall);

		Vertex* shortestWall = NULL;
		shortestWall = getShortestWall(wall);

		updateCapacities(plateau, shortestWall);

		delete plateau;
		delete wall;
	}

	// Find the cluster of neighbours with the same height and capacity as iVertex
	void getPlateau(Vertex* iVertex, vertexSet* oPlateau) {
		vertexSet* alreadyVisited = new vertexSet();
		vertexSet* toVisit = new vertexSet();
		toVisit->insert(iVertex);
		while (!toVisit->empty()) {
			Vertex* current = *(toVisit->begin());
			toVisit->erase(toVisit->begin());
			alreadyVisited->insert(current);
			if (equalHeightAndCapacity(current, iVertex) && !current->stable) {
				oPlateau->insert(current);
				for ( vertexListIterator neighbourIt = current->neighbours.begin(); neighbourIt != current->neighbours.end(); ++neighbourIt) {
					if (alreadyVisited->find(*neighbourIt) == alreadyVisited->end()) {
						toVisit->insert(*neighbourIt);
					}
				}
			}
		}
		delete alreadyVisited;
		delete toVisit;
	}

	// Finds the border (or wall) of the plateau passed in.
	void getWall(vertexSet* iPlateau, vertexSet* oWall) {
		for ( vertexSetIterator plateauIt = iPlateau->begin(); plateauIt != iPlateau->end(); ++plateauIt) {
			for ( vertexListIterator neighbourIt = (*plateauIt)->neighbours.begin(); neighbourIt != (*plateauIt)->neighbours.end(); ++neighbourIt) {
				if (oWall->find(*neighbourIt) == oWall->end()) {
					if (LessHeightAndCapacity()(*plateauIt, *neighbourIt) || (*neighbourIt)->stable) {
						oWall->insert(*neighbourIt);
					}
				}
			}
		}
	}

	// Finds the lowest (considering height and capacity) vertex in a set
	Vertex* getShortestWall(vertexSet* iWall) {
		Vertex* shortestWall = NULL;
		for ( vertexSetIterator wallIt = iWall->begin(); wallIt != iWall->end(); ++wallIt) {
			if ( shortestWall == NULL )
				shortestWall = *wallIt;
			else if (LessHeightAndCapacity()(*wallIt, shortestWall)) {
				shortestWall = *wallIt;
			}
		}
		return shortestWall;
	}

	// Uses shortest wall to determine id we need to update the capacities of input plateau.
	// If shortest wall is stable, marks whole plateau as stable
	void updateCapacities(vertexSet* iPlateau, Vertex* shortestWall) {
		vertexSetIterator plateauIt = iPlateau->begin();
		capacity_type wallHeightAndCapacity = shortestWall->capacity + shortestWall->height;
		capacity_type plateauHeightAndCapacity = (*plateauIt)->height + (*plateauIt)->capacity;
		capacity_type capacityIncrement = wallHeightAndCapacity > plateauHeightAndCapacity ? wallHeightAndCapacity - plateauHeightAndCapacity : 0;
		for ( vertexSetIterator plateauIt = iPlateau->begin(); plateauIt != iPlateau->end(); ++plateauIt) {
			if (capacityIncrement) {
				(*plateauIt)->capacity += capacityIncrement;
			}
			// If the shortest wall is stable, I can mark all plateau as stable
			// (there is no way its capacity can further increase).
			(*plateauIt)->stable = shortestWall->stable;
		}
	}

}