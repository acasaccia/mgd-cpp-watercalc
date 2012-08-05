/*! 
 *  Stores information about each cell of the container.
 *  Height is the physical height of the cell,
 *  Capacity is initialized at infinite and will be calculated as the distance from the outside of the container.
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

typedef std::size_t uint;

struct Vertex {
	uint height;
	uint capacity;
	std::forward_list<Vertex*> neighbours;
	bool stable;
	bool isSink;

	Vertex() :
		height( 0 ),
		capacity( 0 ),
		stable( true ),
		isSink( true )
	{ neighbours = std::forward_list<Vertex*>(); }

	Vertex(uint iHeight) :
		height( iHeight ),
		capacity( 0 ),
		stable( false ),
		isSink( false )
	{ neighbours = std::forward_list<Vertex*>(); }
};