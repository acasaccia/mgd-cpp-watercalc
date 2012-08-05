
#include "Solver.h"
#include "Graph.h"
#include "Vertex.h"
#include <vector>
#include <iostream>

namespace Solver {

	class CompareStability {
		public:
		bool operator()(Vertex* v1, Vertex* v2)
		{
			return static_cast<int>(v1->stable) > static_cast<int>(v2->stable);
		}
	};

	class CompareHeightAndCapacity {
		public:
		bool operator()(Vertex* v1, Vertex* v2)
		{
			return v1->height + v1->capacity < v2->height + v2->capacity;
		}
	};

	class EqualsHeightAndCapacity {
		public:
		bool operator()(Vertex* v1, Vertex* v2)
		{
			return v1->height + v1->capacity == v2->height + v2->capacity;
		}
	};

	void solve(Graph &iGraph) {

		vertexList* vertexesQueue = new vertexList(iGraph.mVertexes.begin(), iGraph.mVertexes.end());

		while (!vertexesQueue->empty()) {

			vertexesQueue->sort(CompareStability());
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
			vertexesQueue->sort(CompareHeightAndCapacity());
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

	void walkNeighboursAndAddToPlateau(Vertex* iVertex, vertexSet* ioPlateau) {
		ioPlateau->insert(iVertex);
		for ( vertexListIterator neighbourIt = iVertex->neighbours.begin(); neighbourIt != iVertex->neighbours.end(); ++neighbourIt) {
			if (ioPlateau->find(*neighbourIt) == ioPlateau->end()) {
				if (EqualsHeightAndCapacity()(iVertex, *neighbourIt)) {
					walkNeighboursAndAddToPlateau(*neighbourIt, ioPlateau);
				}
			}
		}
	}

	void walkPlateauAndGetWalls(vertexSet* iPlateau, vertexSet* ioWall) {
		for ( vertexSetIterator plateauIt = iPlateau->begin(); plateauIt != iPlateau->end(); ++plateauIt) {
			for ( vertexListIterator neighbourIt = (*plateauIt)->neighbours.begin(); neighbourIt != (*plateauIt)->neighbours.end(); ++neighbourIt) {
				if (ioWall->find(*neighbourIt) == ioWall->end()) {
					if (CompareHeightAndCapacity()(*plateauIt, *neighbourIt) || ((*neighbourIt)->stable && !(*neighbourIt)->isSink)) {
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
			else if (CompareHeightAndCapacity()(*wallIt, shortestWall))
				shortestWall = *wallIt;
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