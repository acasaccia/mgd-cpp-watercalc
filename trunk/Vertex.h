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

typedef unsigned long long capacity_type;
typedef unsigned int uint;

struct Vertex {
	capacity_type height;		// parsed from input file
	capacity_type capacity;	// initialized to 0
	bool stable;		// flag initialized to false, becomes true when the capacity value of Vertex is the final one
	std::forward_list<Vertex*> neighbours; // pointers to neighbours according to adjacency mode chosen

	Vertex() :
		height( 0 ),
		capacity( 0 ),
		stable( true )
	{ neighbours = std::forward_list<Vertex*>(); }

	Vertex(capacity_type iHeight) :
		height( iHeight ),
		capacity( 0 ),
		stable( false )
	{ neighbours = std::forward_list<Vertex*>(); }
};