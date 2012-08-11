/*! 
 *  Stores information about each cell of the container.
 *  Height is the physical height of the cell as parsed from input file.
 *  Capacity is initialized to zero.
 *  Neighbours will be added after the whole file has been parsed and the geometry of the container is known.
 *  -
 *  WaterCalc Homework - Advanced cpp programming
 *  Master in Computer Game Development, Verona, Italy
 *  -
 *  \author Andrea Casaccia
 *  \date 14 July 2012
 */

#pragma once

#include <cstddef>
#include <forward_list>

typedef unsigned int uint;

struct Vertex {
	uint height;	// parsed from input file
	uint capacity;	// initialized to 0
	bool stable;	// flag initialized to false, becomes true when the capacity value of Vertex is the final one
	bool sink;		// I modeled the outside of the container as a special node,
					// with 0 capacity and	0 height.
					// All border vertexes in the container are connected to it.
					// I will refer to it as the "sink". This flag is used to
					// avoid treating the sink as a normal cell when finding the
					// border of a cluster later in the algorithm.
	std::forward_list<Vertex*> neighbours; // pointers to neighbours according to adjacency mode chosen

	Vertex() :
		height( 0 ),
		capacity( 0 ),
		stable( true ),
		sink( true )
	{ neighbours = std::forward_list<Vertex*>(); }

	Vertex(uint iHeight) :
		height( iHeight ),
		capacity( 0 ),
		stable( false ),
		sink( false )
	{ neighbours = std::forward_list<Vertex*>(); }
};