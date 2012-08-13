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

#include "Graph.h"
#include <iostream>

Graph::Graph(std::size_t iRows, std::size_t iColumns, std::vector<Vertex*> iVertexes) {
	mRows = iRows;
	mColumns = iColumns;
	mVertexes = iVertexes;
	mVertexes.push_back(new Vertex()); // This vertex represents the outside of the container, we will refer to it as the "sink"
}

void Graph::buildAdjacencyLists(AdjacencyMode iAdjacencyMode) {
	std::forward_list<std::size_t>* neighboursIndexes;
	for (std::size_t c=0; c<=mVertexes.size(); ++c) {
		neighboursIndexes = getNeighboursIndexes(c, iAdjacencyMode);
		for (std::forward_list<std::size_t>::iterator it = neighboursIndexes->begin(); it != neighboursIndexes->end(); ++it) {
			mVertexes[c]->neighbours.push_front(mVertexes[*it]);
		}
		delete neighboursIndexes;
	}
	std::cout << std::endl << "Container heights:" << std::endl;
	display(HEIGHTS);
}

std::forward_list<std::size_t>* Graph::getNeighboursIndexes(std::size_t iIndex, AdjacencyMode iAdjacencyMode) {
	std::forward_list<std::size_t>* neighbours = new std::forward_list<std::size_t>();

	if (iIndex==mRows * mColumns) {
		
		// We are querying for sink's neighbours
		for (std::size_t r=0; r<mRows*mColumns; ++r) {
			if (r<mColumns || r>mColumns*(mRows-1) || r%mColumns == 0 || r%mColumns == mColumns-1)
				neighbours->push_front(r);
		}

	} else if (iIndex<mRows * mColumns) {

		// We are querying for another cell's neighbours
		double tmp = iIndex / mColumns;
		std::size_t r = static_cast<std::size_t>(std::ceil(tmp));
		std::size_t c = iIndex % mColumns;

		if (r>0)			neighbours->push_front(c + (r - 1) * mColumns);
		if (r<mRows - 1)	neighbours->push_front(c + (r + 1) * mColumns);
		if (c>0)			neighbours->push_front(c - 1 + r * mColumns);
		if (c<mColumns - 1)	neighbours->push_front(c + 1 + r * mColumns);

		if ( iAdjacencyMode == ADJACENCY8 ) {
			if (c>0 && r>0)						neighbours->push_front(c - 1 + (r - 1) * mColumns);
			if (c<mColumns - 1 && r<mRows - 1)	neighbours->push_front(c + 1 + (r + 1) * mColumns);
			if (c>0 && r<mRows - 1)				neighbours->push_front(c - 1 + (r + 1) * mColumns);
			if (c<mColumns - 1 && r>0 )			neighbours->push_front(c + 1 + (r - 1) * mColumns);
		}
			
		if (r==0 || r==mRows - 1 || c==0 || c== mColumns - 1) neighbours->push_front(mColumns * mRows);
	}

	return neighbours;
}

void Graph::display(DisplayMode iDisplayMode) {
	for (std::size_t r=0; r<mRows; ++r) {
		for (std::size_t c=0; c<mColumns; ++c) {
			switch (iDisplayMode) {
			case CAPACITIES:
				if ( !mVertexes.at(c+r*mColumns)->stable )
					std::cout << "? ";
				else
					std::cout << mVertexes.at(c+r*mColumns)->capacity << " ";
				break;
			case HEIGHTS:
				std::cout << mVertexes.at(c+r*mColumns)->height << " ";
				break;
			}
		}
		std::cout << std::endl;
	}
}