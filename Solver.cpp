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

	class StableFirst {
		public:
		bool operator()(Vertex* v1, Vertex* v2)
		{
			return static_cast<int>(v1->stable) > static_cast<int>(v2->stable);
		}
	};

	class LessHeightAndCapacity {
		public:
		bool operator()(Vertex* v1, Vertex* v2)
		{
			return v1->height + v1->capacity < v2->height + v2->capacity;
		}
	};

	bool equalHeightAndCapacity (Vertex* v1, Vertex* v2) {
		return v1->height + v1->capacity == v2->height + v2->capacity;
	}

	void solve(Graph &iGraph) {

		vertexList* vertexesQueue = new vertexList(iGraph.mVertexes.begin(), iGraph.mVertexes.end());

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

	void updatePlateauCapacity(Vertex* iVertex) {
		vertexSet* plateau = new vertexSet();
		walkNeighboursAndAddToPlateau(iVertex, plateau);
		vertexSet* walls = new vertexSet();
		walkPlateauAndGetWalls(plateau, walls);
		Vertex* shortestWall = NULL;
		shortestWall = getShortestWall(walls);
		updateCapacities(plateau, shortestWall);
		delete plateau;
		delete walls;
	}

	// @todo: can I avoid recursion?
	void walkNeighboursAndAddToPlateau(Vertex* iVertex, vertexSet* ioPlateau) {
		ioPlateau->insert(iVertex);
		for ( vertexListIterator neighbourIt = iVertex->neighbours.begin(); neighbourIt != iVertex->neighbours.end(); ++neighbourIt) {
			if (ioPlateau->find(*neighbourIt) == ioPlateau->end()) {
				if (equalHeightAndCapacity(iVertex, *neighbourIt)) {
					walkNeighboursAndAddToPlateau(*neighbourIt, ioPlateau);
				}
			}
		}
	}

	// @todo: can I avoid recursion?
	void walkPlateauAndGetWalls(vertexSet* iPlateau, vertexSet* ioWall) {
		for ( vertexSetIterator plateauIt = iPlateau->begin(); plateauIt != iPlateau->end(); ++plateauIt) {
			for ( vertexListIterator neighbourIt = (*plateauIt)->neighbours.begin(); neighbourIt != (*plateauIt)->neighbours.end(); ++neighbourIt) {
				if (ioWall->find(*neighbourIt) == ioWall->end()) {
					if (LessHeightAndCapacity()(*plateauIt, *neighbourIt) || ((*neighbourIt)->stable)) {
						ioWall->insert(*neighbourIt);
					}
				}
			}
		}
	}

	Vertex* getShortestWall(vertexSet* iWall) {
		Vertex* shortestWall = NULL;
		for ( vertexSetIterator wallIt = iWall->begin(); wallIt != iWall->end(); ++wallIt) {
			if ( shortestWall == NULL )
				shortestWall = *wallIt;
			else if (LessHeightAndCapacity()(*wallIt, shortestWall)) {
				shortestWall = *wallIt;
			}
			// When there are more than one shortestWall candidates it would be better to pick the already stable one
			// however this slows down the algorithm, we are adding an if each iteration to speed up an unusual case
			//else if (EqualsHeightAndCapacity()(*wallIt, shortestWall)) {
			//	if (!shortestWall->stable && (*wallIt)->stable)
			//		shortestWall = *wallIt;
			//}
		}
		return shortestWall;
	}

	void updateCapacities(vertexSet* iPlateau, Vertex* shortestWall) {
		for ( vertexSetIterator plateauIt = iPlateau->begin(); plateauIt != iPlateau->end(); ++plateauIt) {
			if (shortestWall->capacity + shortestWall->height >= (*plateauIt)->height + (*plateauIt)->capacity) {
				(*plateauIt)->capacity += shortestWall->capacity + shortestWall->height - ( (*plateauIt)->height + (*plateauIt)->capacity );
			}
			(*plateauIt)->stable = shortestWall->stable;
		}
	}

}