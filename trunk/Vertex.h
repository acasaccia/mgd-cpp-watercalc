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

#include <forward_list>

typedef unsigned long long capacity_type;

struct Vertex {
	capacity_type height;
	capacity_type capacity;
	bool stable; // marks whether this vertex capacity is temporary or final
	std::forward_list<Vertex*> neighbours;
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